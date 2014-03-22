#include "model_point_database.h"
#include "library.h"
#include "view_dataset_table.h"

//++++++++++++++++++++++++++++++++++
model_point_database::model_point_database( library *lib, dataset_descriptor &descriptor, QList<model_point> *points, bool replace )
    :  _ref_library(lib), _replace( replace  ), _num_points(0), _max_distance(-1)
{

    //  If we're replacing? Then that means we're starting fresh and need to
    //  delete any old databases, then create a fresh one.
    //
    if( replace ){

        //
        assert( replace != 0 );

        //
        unsigned int stamp = helpers::timestamp();

        //
        if( !init_database( descriptor ) ){
            helpers::debug_error( "unable to initialize database...", "model_point_database", descriptor.dataset_name() );
            check_sql_error();
            return;
        }

        //
        if( !init_table( descriptor ) ){
            helpers::debug_error( "unable to initialize database table...", "model_point_database", descriptor.dataset_name() );
            check_sql_error();
            return;
        }

        //
        if( !insert_points( *points ) ){
            helpers::debug_error( "unable to insert points...", "model_point_database", descriptor.dataset_name() );
            return;
        }

        //  Label the categorical values.
        //
        label_table( descriptor );

        //
        QString msg = QString("created database: [%1] [seconds: %2]...")
                .arg( descriptor.dataset_name() )
                .arg( helpers::milliseconds_to_seconds( helpers::time_elapsed( stamp ) ) );
        helpers::debug_out( msg );
    }


    //  ...otherwise, we're going to load the pre-existing database for this dataset
    //  and go from there!
    //
    else{
        if( !load_database( descriptor ) )
            helpers::debug_error( "error loading database", "model_point_database", descriptor.dataset_name() );
        else
            helpers::debug_out( QString("loaded database: [%1]...").arg( descriptor.dataset_name() ) );
    }


}
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void model_point_database::erase_existing_database_file( QString path ){

    //
    QFile::remove( path );
}
//++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++
bool model_point_database::load_database( dataset_descriptor &descriptor ){

    //
    QString name = descriptor.dataset_name();

    // Find QSLite driver.
    //
    _db = QSqlDatabase::addDatabase("QSQLITE");

    #ifdef Q_OS_LINUX
    //  NOTE: We have to store database file into user home folder in Linux.
    //
    QString path(QDir::home().path());
    path.append(QDir::separator()).append(name);
    path = QDir::toNativeSeparators(path);

    //
    _db.setDatabaseName(path);
    #else

    //  Create the database in the data folder with the rest of the
    //  dataset.
    //
    QString path( descriptor.path_directory() );
    path.append( name ).append( ".db" );
    QFileInfo db_file( path );
    path = db_file.absoluteFilePath();

    //
    _db.setDatabaseName( path );
    #endif

    //
    if( _db.open() ){

        //
        find_num_points_in_table();

        //
        return true;
    }

    //
    return false;
}

//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
bool model_point_database::init_database( dataset_descriptor &descriptor ){

    //
    QString name = descriptor.dataset_name();

    // Find QSLite driver.
    //
    _db = QSqlDatabase::addDatabase("QSQLITE");

    #ifdef Q_OS_LINUX
    //  NOTE: We have to store database file into user home folder in Linux.
    //
    QString path(QDir::home().path());
    path.append(QDir::separator()).append(name);
    path = QDir::toNativeSeparators(path);

    //
    erase_existing_database_file( path );

    _db.setDatabaseName(path);
    #else

    //  Create the database in the data folder with the rest of the
    //  dataset.
    //
    QString path( descriptor.path_directory() );
    path.append( name ).append( ".db" );

    //
    erase_existing_database_file( path );
    _db.setDatabaseName(path);

    #endif

    // Open databasee
    bool open= _db.open();

    //
    return open;
}
bool model_point_database::init_table( dataset_descriptor &descriptor ){

    // Create table "person".
    //
     bool ret = false;
     if (_db.isOpen())
     {
         QSqlQuery query;
         QString msg = find_table_string( descriptor );
         ret = query.exec( msg );
         //ret = query.exec( "create table dataset (id integer primary key, Education varchar(20), Marital_status varchar(20), Occupation varchar(20), Relationship varchar(20), Race varchar(20), Sex varchar(20), Capital_gain varchar(20), Capital_loss varchar(20), Hours_per_week varchar(20), Native_country varchar(20), Income varchar(20), Age varchar(20), Workclass varchar(20))" );
     }

     //
     return ret;
}

QString model_point_database::find_table_string( dataset_descriptor &descriptor ){

    /*
    "create table dataset "
    "(id integer primary key, "
    "firstname varchar(20), "
    "lastname varchar(30), "
    "age integer)")
      */

    //
    QString query="";


    //  We'll always need these two lines.
    //
    //  The first element needs to be "id" for a successful query.
    //  The "id" will serve as the point index in any lists.
    //  We also know that we'll have position data.
    //
    QString s0 = "create table dataset ";
    QString s1 = "(id integer primary key, x real, y real, ";

    //  The rest could be anything though.
    //  So we will use the descriptor to generate our lines.
    //  We'll use our attributes.
    //  We won't isolate our class, we will simple look it up as another attribute.
    //
    QStringList lines;
    QStringList attributes = descriptor.attributes();
    for( int ii=0; ii<attributes.size(); ii++ )
        lines.push_back( QString("%1 text, ").arg(attributes.at(ii)) );

    //  Add our class options.
    //
    QStringList class_options = descriptor.class_options();
    for( int ii=0; ii<class_options.size()-1; ii++ )
        lines.push_back( QString("%1 text, ").arg(class_options.at(ii)) );

    //  Finish.
    //
    lines.push_back( QString("%1 text)").arg(class_options.back()) );

    //  Compile our lines into a single query!
    //
    query.append( s0 ).append( s1 );
    for( int ii=0; ii<lines.size(); ii++ )
        query.append( lines.at(ii) );


    //
    helpers::debug_out( QString("model_point_database init string: [%1]\n\n").arg(query) );
    return query;
}
//++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++
void init_query_variants( QString* prepare_msg, std::vector<QVariantList>* variants, model_point &point ){

    //
    prepare_msg->clear();
    prepare_msg->append( "insert into dataset values(" );

    //  We have a variant for the index.
    //
    //QString query= QString( "insert into dataset values( %1," ).arg( index );
    QVariantList vl_index;
    variants->push_back( vl_index );
    prepare_msg->append("?,");

    //  We have variants for the xy positions.
    //
    //query.append( QString("%1,").arg( point._position.x() ) );
    //query.append( QString("%1,").arg( point._position.y() ) );
    QVariantList vl_px, vl_py;
    variants->push_back( vl_px );
    variants->push_back( vl_py );
    prepare_msg->append("?,");
    prepare_msg->append("?,");


    //  We have a variant for each of the attribute values of the point.
    //
    for( int ii=0; ii<point._attribute_values.size(); ii++ ){

        //
        //line = QString("'%1',").arg( point._attribute_values.at(ii) );
        QVariantList vl_attr;
        variants->push_back( vl_attr );
        prepare_msg->append("?,");
    }

    //  We have a variant for the class value.
    //
    {
        //QString line = QString("'%1',").arg( point._attribute_class );
        QVariantList vl_class;
        variants->push_back( vl_class );
        prepare_msg->append("?,");
    }

    //  We have a variant for the class probabilities of the point.
    //
    for( int ii=0; ii<point._probability_values.size()-1; ii++ ){

        //
        //line = QString("'%1',").arg( point._probability_values.at(ii) );
        QVariantList vl_prob;
        variants->push_back( vl_prob );
        prepare_msg->append("?,");
    }

    //  We have a variant list for the final class probability.
    //
    {
        //QString line = QString("'%1')").arg( point._probability_values.back() );
        QVariantList vl_class_prob;
        variants->push_back( vl_class_prob );
        prepare_msg->append("?,");
    }

    //  Finish the query.
    //
    *prepare_msg = prepare_msg->left( prepare_msg->length() - 3 );
    prepare_msg->append(")");
}
void fill_query_variants( std::vector<QVariantList>* variants, QList<model_point> &points, int index ){

    //
    const model_point* point = &points.at(index);

    //
    int count=0;

    //  We have a variant for the index.
    //
    //QString query= QString( "insert into dataset values( %1," ).arg( index );
    {
        QString msg = QString("%1").arg( index );
        variants->at(count++) << msg;
    }

    //  We have variants for the xy positions.
    //
    //query.append( QString("%1,").arg( point._position.x() ) );
    //query.append( QString("%1,").arg( point._position.y() ) );
    {
        QString msg = QString("%1").arg( point->_position.x() );
        variants->at(count++) << msg;
    }
    {
        QString msg = QString("%1").arg( point->_position.x() );
        variants->at(count++) << msg;
    }


    //  We have a variant for each of the attribute values of the point.
    //
    for( int ii=0; ii<point->_attribute_values.size(); ii++ ){

        //
        //line = QString("'%1',").arg( point._attribute_values.at(ii) );
        QString msg = QString("%1").arg( point->_attribute_values.at(ii) );
        variants->at(count++) << msg;
    }

    //  We have a variant for the class value.
    //
    {
        //QString line = QString("'%1',").arg( point._attribute_class );
        QString msg = QString("%1").arg( point->_attribute_class );
        variants->at(count++) << msg;
    }

    //  We have a variant for the class probabilities of the point.
    //
    for( int ii=0; ii<point->_probability_values.size()-1; ii++ ){

        //
        //line = QString("'%1',").arg( point._probability_values.at(ii) );
        QString msg = QString("%1").arg( point->_probability_values.at(ii) );
        variants->at(count++) << msg;
    }

    //  We have a variant list for the final class probability.
    //
    {
        //QString line = QString("'%1')").arg( point._probability_values.back() );
        QString msg = QString("%1").arg( point->_probability_values.back());
        variants->at(count++) << msg;
    }

}

//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
bool model_point_database::insert_points( QList<model_point> &points ){

    //  Batch queries into a transation.
    //
    _db.transaction();
    for( int ii=0; ii<points.size(); ii++ ){
        QString msg = point_to_insert_query( ii, points.at(ii) );
        _db.exec(msg);
    }
    _db.commit();
    check_sql_error();

    //
    _num_points = points.size();

    //
    return true;
}

bool model_point_database::insert_point( int index, const model_point &point ){

    //
    bool ret = false;

    //
    if (_db.isOpen()){

        //   http://www.sqlite.org/autoinc.html
        //  NULL = is the keyword for the autoincrement to generate next value
        //
        QSqlQuery query;
        QString msg = point_to_insert_query( index, point );
        ret = query.exec( msg );
    }

    //
    return ret;
}

QString model_point_database::point_to_insert_query( int index, const model_point &point ){

    //
    QString query= QString( "insert into dataset values( %1," ).arg( index );

    //  Position.
    //
    query.append( QString("%1,").arg( point._position.x() ) );
    query.append( QString("%1,").arg( point._position.y() ) );

    //  Get the attribute values of the point.
    //
    for( int ii=0; ii<point._attribute_values.size(); ii++ ){

        //
        QString line="";
        line = QString("'%1',").arg( point._attribute_values.at(ii) );

        //
        query.append( line );
    }

    //  Add the class value.
    //
    {
        QString line = QString("'%1',").arg( point._attribute_class );
        query.append( line );
    }

    //  Get the class probabilities of the point.
    //
    for( int ii=0; ii<point._probability_values.size()-1; ii++ ){

        //
        QString line="";
        line = QString("'%1',").arg( point._probability_values.at(ii) );

        //
        query.append( line );
    }

    //  Finish with the final class probability.
    //
    {
        QString line = QString("'%1')").arg( point._probability_values.back() );
        query.append( line );
    }

    //
    //helpers::debug_out( QString("point insert query: [%1]\n\n").arg(query) );
    return query;
}
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void model_point_database::check_sql_error(){

    //
    QSqlError err = _db.lastError();
    QString err_text = err.text();
    if( err_text.compare("") == 0 )
        return;
    helpers::debug_out( QString("SQL error in [model_point_database]: [msg: %1]").arg(err_text) );
}

//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void model_point_database::find_num_points_in_table(){

    //
    _num_points=0;
    QSqlQuery q = _db.exec("select count(*) from dataset");
    check_sql_error();
    while( q.next() )
        _num_points = q.value(0).toInt();

    //
    helpers::debug_out( QString("dataset points [count:%1]").arg(_num_points) );
}
void model_point_database::find_max_distance(){

}

bool model_point_database::get_point( int index, model_point *point, dataset_descriptor &descriptor, bool normal_distance ){

    //
    QMutexLocker ml( &_mutex );

    //
    if( index >= _num_points )
        return false;

    //  Set used table.
    //
    QSqlTableModel *model = new QSqlTableModel(0,_db);
    model->setTable("dataset");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //  Set where clause.
    //
    model->setFilter(QString("id=%1").arg(index));
    model->select();

    //  Read the result.
    //
    QSqlRecord record = model->record(0);
    if(!record.isEmpty()){
        database_entry_to_point( record, point, descriptor );
        //output_point( *point );

        return true;
    }

    //
    return false;
}


//  Assumes the record object exists.
//
void model_point_database::database_entry_to_point( QSqlRecord& record, model_point *point, dataset_descriptor &descriptor  ){


    /*
    //  Output the record data.
    //
    helpers::debug_out( "-instance record-" );
    for( int ii=0; ii<record.count(); ii++ )
        helpers::debug_out( QString("...%1").arg( record.value( ii ).toString() ) );
    return false;
    */

    //
    int index=1;

    //  Get the position.
    //
    point->_position.setX( record.value(index++).toString().toDouble() );
    point->_position.setY( record.value(index++).toString().toDouble() );


    //  Get the attribute values (classes).
    //
    point->_attribute_values.clear();
    for( int ii=0; ii<descriptor.attributes().size(); ii++ )
        point->_attribute_values.push_back( record.value( index++ ).toString() );


    //  Get the attribute class.
    //
    point->_attribute_class = point->_attribute_values.back();

    //  Get the probability values (class options).
    //
    point->_probability_values.clear();
    for( int ii=0; ii<descriptor.class_options().size(); ii++ )
        point->_probability_values.push_back( record.value( index++ ).toDouble() );

    //  Cache.
    //
    descriptor.cache_point( *point );

    //  Output.
    //
    //output_point( *point );
}

void model_point_database::output_point( model_point &point ){

    //  Positions.
    //
    QString msg = QString("point position [x:%1][y:%2]")
            .arg( point._position.x() )
            .arg( point._position.y() );

    //  Attributes.
    //
    msg.append( ", \nattributes[" );
    msg.append( QString( "%1" ).arg(point._attribute_values.front() ) );
    for( int ii=1; ii<point._attribute_values.size(); ii++ )
        msg.append( QString( ",%1" ).arg(point._attribute_values.at( ii ) ) );
    msg.append( "]," );

    //  Probabilities.
    //
    msg.append( "\nprobabilities[" );
    msg.append( QString( "%1" ).arg(point._probability_values.front() ) );
    for( int ii=1; ii<point._probability_values.size(); ii++ )
        msg.append( QString( ",%1" ).arg(point._probability_values.at( ii )) );
    msg.append( "]" );

    //  Output.
    //
    helpers::debug_out( msg );
}
//++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++
QSqlDatabase* model_point_database::database(){ return &_db; }
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void model_point_database::pick_instance( qreal x, qreal y, qreal r ){

    //
    int results=0;
    int pid=-99;
    float px=-99;
    float py=-99;

    //
    QString query_select = QString("SELECT id, x, y");
    QString query_from = QString("FROM dataset");

    //
    QString query_where_x = QString("x BETWEEN %0 AND %1").arg(x-r).arg(x+r);
    QString query_where_y = QString("y BETWEEN %0 AND %1").arg(y-r).arg(y+r);
    QString query_where = QString("WHERE %0 AND %1").arg(query_where_x).arg(query_where_y);
    //QString query_where = QString("WHERE %0").arg(query_where_x);

    //
    QString query_string = QString("%0 %1 %2").arg(query_select).arg(query_from).arg(query_where);

    //
    helpers::debug_out( QString("query string: %0").arg(query_string) );

    //
    //
    QSqlQuery query = _db.exec( query_string );
    helpers::debug_out( "query error?: " + query.lastError().text() );
    while (query.next()){

        //
        results++;

        //
        pid = query.value(0).toInt();
        px = query.value(1).toFloat();
        py = query.value(2).toFloat();

        //
        helpers::debug_out( QString("pick result id[%0] xy(%1,%2)").arg(pid).arg(px).arg(py) );
    }

    //  Highlight the row in the table.
    //
    if( pid > -1 ){
        _ref_library->_ref_view_dataset_table->show();
        _ref_library->_ref_view_dataset_table->select_row( pid );
    }

    //
    helpers::debug_out( QString("pick results[%0] id[%1] xy(%2,%3)").arg(results).arg(pid).arg(px).arg(py) );
}

//++++++++++++++++++++++++++++++++++

int model_point_database::num_points(){ return _num_points; }


//++++++++++++++++++++++++++++++++++
void model_point_database::label_table( dataset_descriptor &descriptor ){

    //
    helpers::debug_out("...labeling categorical values.");

    //
    QSqlTableModel model(qApp,_db);

    //  Fill our model with our dataset.
    //  Show all of it since it loads lazily and will only show a part by itself.
    //
    model.setTable( "dataset" );
    model.setEditStrategy( QSqlTableModel::OnManualSubmit );
    model.select();
    while( model.canFetchMore() )
        model.fetchMore();

    //
    model.database().transaction();
    label_model( &model, descriptor );

    //
    if( model.submitAll() )
        model.database().commit();
    else
        helpers::debug_out("error labeling database categories...");
}
void model_point_database::label_model( QSqlTableModel *model, dataset_descriptor &descriptor ){

    //  How many columns will we label?
    //  One of the attributes are the instance class (so don't count it);
    //
    int attr = descriptor.attributes().count();

    //  Start at 3 since (0=id, 1=px, 2=py).
    //
    for( int col=3; col<attr; col++ )
        label_column_categories( model, descriptor, col );
}
void model_point_database::label_column_categories( QSqlTableModel *model, dataset_descriptor &descriptor, int col ){

    //
    QString col_name = model->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString();

    //  Change the value in each row of our column.
    //
    int size_ = model->rowCount();
    for( int row_=0; row_<size_; row_++ ){

        //
        int val = model->record(row_).value(col).toInt();
        QModelIndex index=model->index( row_, col );

        //
        QString new_val="";
        if( get_label( descriptor, val, col_name, new_val ) )
            model->setData( index, new_val, Qt::EditRole );
    }

}
bool model_point_database::get_label( dataset_descriptor &descriptor, int val, QString col_name, QString& new_val ){

    //  The column says which catagory we are targeting.
    //
    QStringList* labels = descriptor.cached_attribute_options( col_name );
    if( !labels )
        return false;

    //  The value says which element we should convert it to.
    //
    new_val = labels->at( val );

    //
    return true;
}
//++++++++++++++++++++++++++++++++++

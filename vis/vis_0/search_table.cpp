#include "search_table.h"
#include "dataset_db.h"
#include "library.h"

//
search_table::search_table( library* lib, QString filter )
    :   _ref_library( lib ), _filter(filter)
{
    //  Create our model with the active database.
    //  Using set and select applies the data to it.
    //
    _table_model = new QSqlTableModel( qApp, *(_ref_library->_active_database->database()) );
    _table_model->setTable( "dataset" );
    _table_model->setFilter( filter );
    _table_model->select();
    while( _table_model->canFetchMore() )
        _table_model->fetchMore();

    /*
    //  Create our view using our model.
    //
    _table_view = new QTableView;
    _table_view->setEditTriggers( QAbstractItemView::NoEditTriggers );
    //_table_view->setSelectionBehavior( QAbstractItemView::SelectRows );
    _table_view->setModel( _table_model );
    _table_view->show();
    */
}

void search_table::apply_filter(){

    _table_model->setFilter( _filter );
    _table_model->select();
    while( _table_model->canFetchMore() )
        _table_model->fetchMore();
}

bool search_table::get_point( int index, model_point *point ){

    //
    QMutexLocker ml( &_mutex );

    /*
    //
    int num_points = _ref_library->_active_database->num_points();
    dataset_descriptor* descriptor = _ref_library->_active_database->descriptor();

    //
    if( index >= num_points )
        return false;

    //  Set used table.
    //
    QSqlTableModel *model = new QSqlTableModel(0,_db);
    model->setTable("dataset");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    */

    //  Set where clause.
    //  Modify our existing filter to include the index we need.
    //
    QString new_filter = QString("%1 and id = %2").arg(_filter).arg(index);
    _table_model->setFilter(new_filter);
    _table_model->select();

    //  Read the result.
    //
    dataset_descriptor* descriptor = _ref_library->_active_database->descriptor();
    QSqlRecord record = _table_model->record(0);
    if(!record.isEmpty()){
        database_entry_to_point( record, point, *descriptor );
        return true;
    }

    //
    return false;
}

void search_table::database_entry_to_point( QSqlRecord& record, model_point *point, dataset_descriptor &descriptor  ){

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

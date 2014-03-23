#include "view_dataset_table.h"
#include "dataset_db.h"

view_dataset_table::view_dataset_table(QWidget *parent) :
    QWidget(parent), _table_model( 0 ), _ref_db(0)
{
    //
    resize( 800, 600 );

    //
    _hbox = new QHBoxLayout;
    setLayout( _hbox );

    //
    restart_table( 0 );

    //
    setWindowTitle( "Individual Instance Table" );
    setWindowIcon(QIcon(QDir::currentPath() + "/../vis_0/data/MAPLE_logo_transparent.gif"));
}



//
void view_dataset_table::restart_table( dataset_db *db  ){

    //
    _ref_db = db;

    /*
    //
    if( _table_model )
        delete _table_model;
    */

    //
    _hbox->removeWidget( _table_view );

    //
    if( !db ){
        //
        _table_model = new QSqlTableModel( this );

        //
        _table_view = new QTableView;
        _table_view->setEditTriggers( QAbstractItemView::NoEditTriggers );
        _table_view->setSelectionBehavior( QAbstractItemView::SelectRows );
        _table_view->setModel( _table_model );
        _table_view->show();

        //
        _hbox->addWidget( _table_view );
    }

    //
    else{
        //
        _table_model = new QSqlTableModel( this, *(db->database())  );

        //  Fill our model with our dataset.
        //  Show all of it since it loads lazily and will only show a part by itself.
        //
        _table_model->setTable( "dataset" );
        _table_model->setEditStrategy( QSqlTableModel::OnManualSubmit );
        _table_model->select();
        while( _table_model->canFetchMore() )
            _table_model->fetchMore();

        //
        _table_view = new QTableView;
        _table_view->setEditTriggers( QAbstractItemView::NoEditTriggers );
        _table_view->setSelectionBehavior( QAbstractItemView::SelectRows );
        _table_view->setModel( _table_model );
        _table_view->show();

        //
        _hbox->addWidget( _table_view );
    }
}

//
void view_dataset_table::select_row( int row ){

    //
    QModelIndex index = _table_model->index(row,0);

    //
    _table_view->setCurrentIndex( index );
}


//
void view_dataset_table::label_model(){

    //  How many columns will we label?
    //  One of the attributes are the instance class (so don't count it);
    //
    int attr = _ref_db->descriptor()->attributes().count();

    //  Start at 3 since (0=id, 1=px, 2=py).
    //
    for( int col=3; col<attr; col++ )
        label_column_categories( col );
}

void view_dataset_table::label_column_categories( int col ){

    //
    QString col_name = _table_model->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString();

    //  Change the value in each row of our column.
    //
    int size_ = _table_model->rowCount();
    for( int row_=0; row_<size_; row_++ ){

        //
        int val = _table_model->record(row_).value(col).toInt();
        QModelIndex index=_table_model->index( row_, col );

        //
        QString new_val="";
        if( get_label( val, col_name, new_val ) )
            _table_model->setData( index, new_val, Qt::EditRole );
    }

}
bool view_dataset_table::get_label( int val, QString col_name, QString& new_val ){

    //
    if( !_ref_db )
        return false;

    //  The column says which catagory we are targeting.
    //
    QStringList* labels = _ref_db->descriptor()->cached_attribute_options( col_name );
    if( !labels )
        return false;

    //  The value says which element we should convert it to.
    //
    new_val = labels->at( val );

    //
    return true;
}


//
void view_dataset_table::clear(){

    //
    _table_view->setModel(0);
}

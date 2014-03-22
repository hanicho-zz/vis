#include "dataset_db.h"
#include "library.h"

//++++++++++++++++++++++++++++++++++
dataset_db::dataset_db( library *lib, QString path_obsrv, QString path_color, QString path_info, QList<model_point> *points, bool replace )
    :   _ref_library(lib), _descriptor( path_obsrv, path_color, path_info ), _model_db( lib, _descriptor, points, replace ), _open( true )
{}

dataset_db::~dataset_db(){}
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
//
QString dataset_db::name(){ return _descriptor.dataset_name(); }

QSqlDatabase* dataset_db::database(){ return _model_db.database(); }

//
bool dataset_db::get_point( int index, model_point *point, bool normal_distance  ){ return _model_db.get_point( index, point, _descriptor, normal_distance ); }
int dataset_db::num_points(){ return _model_db.num_points(); }
dataset_descriptor *dataset_db::descriptor(){ return &_descriptor; }

//++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++
bool dataset_db::is_open(){ return _open; }
void dataset_db::open(){

    //
    if( _open )
        return;

    //
    _open = _model_db.database()->open();
}
void dataset_db::close(){

    //
    if( !_open )
        return;

    //
    _open=false;

    //
    //_model_db.database()->close();
}
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void dataset_db::activate(){

    //
    _model_db.load_database( _descriptor );
}
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void dataset_db::test_pick_point( qreal x, qreal y, qreal r ){

    //
    _model_db.pick_instance( x, y, r );
}
//++++++++++++++++++++++++++++++++++

#include "visualizer.h"
#include "library.h"

//+++++++++++++++++++++++++
visualizer::visualizer( library* lib )
    :   _ref_library(lib), _gl( lib ), _factory(lib)
{
}
visualizer::~visualizer(){

    //
    clear_databases();
}
//+++++++++++++++++++++++++


//+++++++++++++++++++++++++
void visualizer::add_database( interrogation &i ){

    //
    for( int ii=0; ii < i._pairs.size(); ii++){

        //  Create the visual unit.
        //
        visual_unit *vis = new visual_unit();
        dataset_db* db = i._pairs.at(ii)._dataset;
        db->activate();
        _factory.create_piecharts( *db, _gl );
        _factory.get_unit(vis);

        //
        _list_db_vis.push_back( new dataset_db_vis(db,vis,&_gl) );
    }
}
void visualizer::add_database( tour &t ){}
void visualizer::add_database( dataset_db *db ){

    //  Create the visual unit.
    //
    visual_unit *vis = new visual_unit();
    db->activate();
    _factory.create_piecharts( *db, _gl );
    _factory.get_unit(vis);

    //
    _list_db_vis.push_back( new dataset_db_vis(db,vis,&_gl) );
}
void visualizer::clear_databases(){

    //
    clear_active();

    //  Delete our visualizations.
    //
    for(int ii=0; ii<_list_db_vis.size(); ii++)
        delete _list_db_vis.at(ii)->_vis;

    //


    //  Clear our list of visualizations.
    //
    _list_db_vis.clear();
}
//+++++++++++++++++++++++++

void visualizer::remake_active_vis(){

    //
    _factory.create_search_piecharts( _gl );

    //
    visual_unit *vis = new visual_unit();
    _factory.get_unit(vis);
    _gl.set_visual_unit( &vis->_info );
}

//+++++++++++++++++++++++++
void visualizer::set_active_vis( dataset_db *db ){

    //
    for( int ii=0; ii<_list_db_vis.size(); ii++ ){

        //
        QString name = _list_db_vis.at(ii)->_db->name();

        //
        if( name.compare(db->name()) == 0 )
            activate( _list_db_vis.at(ii)->_vis );
    }
}

//
void visualizer::activate( visual_unit *vis ){

    //
    _gl.set_visual_unit( &vis->_info );
}

//
void visualizer::clear_active(){

    //
    _gl.set_visual_unit( 0 );
}
//+++++++++++++++++++++++++



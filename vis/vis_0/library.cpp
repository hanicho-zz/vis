#include "library.h"

//
#include "dataset_db.h"
#include "view_dataset_table.h"
#include "view_legend.h"
#include "question.h"
#include "tour.h"
#include "interrogation.h"
#include "model_player.h"
#include "view_player.h"
#include "visualizer.h"

//++++++++++++++++++++++++++++++++++++
library::library()
    :   _active_database( 0 ), _ref_view_dataset_table( 0 ), _ref_view_legend( 0 ), _ref_visualizer(0)
{
}
//++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++
library::~library(){

    //  Cleanup our databases.
    //
    for( int ii=0; ii<_list_dataset_databases.size(); ii++ ){

        //
        _list_dataset_databases.at( ii )->close();

        //
        //delete _list_dataset_databases.at( ii );
    }
    _list_dataset_databases.clear();
}
//++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++
void library::add_database( dataset_db *db ){

    //  Add the database to our list if it's new to us.
    //
    if( !contains_database( db ) )
        _list_dataset_databases.push_back( db );

}
void library::set_active_database( int index ){

    //
    if( index < 0 || index >= _list_dataset_databases.size() )
        return;

    //
    _active_database = _list_dataset_databases.at( index );

    //
    if( _ref_view_dataset_table )
        _ref_view_dataset_table->restart_table( _active_database );

    //
    fill_legend( _active_database );
}
void library::set_active_database( dataset_db *db ){

    //
    if( !db )
        return;

    //
    _active_database=db;

    //
    _active_database->activate();

    //
    helpers::debug_out( QString("...active database[%1]").arg(db->name() ) );

    //  Add the database to our list if it's new to us.
    //
    if( !contains_database( db ) )
        _list_dataset_databases.push_back( db );

    //
    if( _ref_view_dataset_table )
        _ref_view_dataset_table->restart_table( _active_database );

    //
    fill_legend( db );

    //  Let the visualizer know there has been a change.
    //
    _ref_visualizer->set_active_vis( db );
}
//++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++
bool library::contains_database( dataset_db *db ){

    //  Look for equal names.
    //
    for( int ii=0; ii<_list_dataset_databases.size(); ii++ )
        if( _list_dataset_databases.at( ii )->name().compare( db->name() ) )
            return true;

    //
    return false;
}

//++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++
void library::fill_legend( dataset_db *db ){

    //
    if( !_ref_view_legend )
        return;

    //
    _ref_view_legend->clear_elements();

    //
    std::vector< std::pair<QString,QColor> > *ref_list = db->descriptor()->list_class_option_to_color();
    std::vector< std::pair<QString,QColor> >::iterator it;
    for( it=ref_list->begin(); it!=ref_list->end(); it++ )
        _ref_view_legend->push_element( it->first, it->second );

}
//++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++
void library::apply_model_interrogation( interrogation* i ){


    //  Build our visualizations.
    //
    _ref_visualizer->add_database( *i );

    //  Create and launch the model.
    //
    model_player *model = new model_player( this );
    model->play_interrogation( i );
    _ref_view_player->run_model_interrogation( model );
}

void library::apply_model_tour( tour* t ){

    //  Build our visualizations.
    //
    _ref_visualizer->add_database( *t );

    //
    model_player *model = new model_player( this );
    model->play_tour( t );

    //
    _ref_view_player->run_model_tour( model );
}

//++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++
void library::pick_instance( float x, float y, float r ){

    //
    if( !_active_database )
        return;

    //
    _active_database->test_pick_point( x, y, r );
}

//+++++++++++++++++++++++++

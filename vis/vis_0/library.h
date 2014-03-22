#ifndef LIBRARY_H
#define LIBRARY_H

//
#include "common.h"

//
class dataset_db;
class view_dataset_table;
class view_legend;
class question;
class tour;
class interrogation;
class view_player;
class visualizer;
class search_result;
class view_search;
class search_table;

//
class library
{
public:
    library();
    ~library();

    //
    void add_database( dataset_db *db );
    void set_active_database( int index );
    void set_active_database( dataset_db *db );

    //
    void apply_model_interrogation( interrogation* i );
    void apply_model_tour( tour* t );

    //
    void pick_instance( float x, float y, float r );

    //
    std::vector< dataset_db* > _list_dataset_databases;
    dataset_db *_active_database;

    //
    std::vector< search_result* > _search_results;

    //
    view_dataset_table *_ref_view_dataset_table;
    view_legend *_ref_view_legend;
    view_player *_ref_view_player;
    visualizer *_ref_visualizer;
    view_search* _ref_view_search;
    search_table* _active_search_table;

private:

    //
    bool contains_database( dataset_db *db );

    //
    void fill_legend( dataset_db *db );
};

#endif // LIBRARY_H

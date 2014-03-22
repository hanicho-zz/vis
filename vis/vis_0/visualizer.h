#ifndef VISUALIZER_H
#define VISUALIZER_H

//
#include "common.h"
#include "gl_unit.h"
#include "visual_unit_factory.h"
#include "dataset_db_vis.h"
#include "interrogation.h"
#include "tour.h"

//
class library;

//  Displays a single visual_unit.
//  Supports "index peeling" of the unit.
//  Supports instance selection of the unit.
//  Supports lasso selection of the unit.
//  Supports index specification of the unit (display a set glyphs at specified indices).
//
class visualizer
{
public:
    visualizer( library* lib );
    ~visualizer();

    //
    void add_database( interrogation &i );
    void add_database( tour &t );
    void add_database( dataset_db *db );
    void clear_databases();

    //
    void set_active_vis( dataset_db *db );

    //
    void remake_active_vis( );

    //
    void clear_active();

    //
    gl_unit _gl;

    //
    visual_unit_factory _factory;
private:

    //
    void activate( visual_unit *vis );

    //
    library* _ref_library;

    //
    std::vector< dataset_db_vis* > _list_db_vis;
};

#endif // VISUALIZER_H

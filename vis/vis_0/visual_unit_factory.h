#ifndef VISUAL_UNIT_FACTORY_H
#define VISUAL_UNIT_FACTORY_H

//
#include "common.h"
#include "dataset_db.h"
#include "visual_unit.h"

//
class library;

//  Makes visual_units.
//  Can make units full of pie glyphs (and eventually, speckle glyphs).
//
class visual_unit_factory : public QObject
{
    Q_OBJECT
public:
    visual_unit_factory( library* lib );

    //  Create a visual unit with pie glyphs.
    //
    void create_piecharts( dataset_db &db, QGLFunctions qglf );

    //
    void create_search_piecharts( QGLFunctions qglf );

    //  Get's the last created visual unit.
    //
    void get_unit( visual_unit *unit );
public slots:
    void errorString(QString err);
private:

    //
    void generate_geometry( dataset_db &db, QGLFunctions qglf );
    void generate_geometry_search( QGLFunctions qglf );
    void generate_geometry_parallel( dataset_db &db, QGLFunctions qglf );

    //  Add a piechart to our visual unit.
    //
    void push_piechart( qreal cx, qreal cy, std::vector<double> &slice_percents, QVector3D true_color, std::vector<QVector3D> &silce_colors, qreal radius=0.05, int steps=30   );

    void push_fake_piechart();

    //
    visual_unit* _active_visual_unit;

    //
    library* _ref_library;
};

#endif // VISUAL_UNIT_FACTORY_H

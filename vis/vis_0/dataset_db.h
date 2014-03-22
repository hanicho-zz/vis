#ifndef DATASET_DB_H
#define DATASET_DB_H

//
#include "model_point_database.h"

//
class library;

//  A wraper for a SQLite database of a dataset, and a dataset descriptor.
//
class dataset_db
{
public:
    dataset_db( library *lib, QString path_obsrv, QString path_color, QString path_info, QList<model_point> *points, bool replace );
    ~dataset_db();

    //
    bool is_open();
    void open();
    void close();

    //
    void activate();

    //
    //
    QString name();
    QSqlDatabase* database();
    dataset_descriptor *descriptor();
    int num_points();

    //
    bool get_point( int index, model_point *point, bool normal_distance   );

    //
    void test_pick_point( qreal x, qreal y, qreal r );
private:

    //
    library *_ref_library;

    //
    dataset_descriptor _descriptor;

    //
    model_point_database _model_db;

    //
    bool _open;

};

#endif // DATASET_DB_H

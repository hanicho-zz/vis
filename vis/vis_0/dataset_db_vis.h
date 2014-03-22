#ifndef DATASET_DB_VIS_H
#define DATASET_DB_VIS_H

//
class dataset_db;
class visual_unit;
class gl_unit;

//  Wraps up a dataset and it's visual unit.
//
class dataset_db_vis
{
public:
    dataset_db_vis( dataset_db* db, visual_unit *vis, gl_unit *gl  );
    ~dataset_db_vis();

    //
    gl_unit* _gl;

    //
    dataset_db *_db;
    visual_unit *_vis;
};

#endif // DATASET_DB_VIS_H

#ifndef MODEL_POINT_DATABASE_H
#define MODEL_POINT_DATABASE_H


//
#include "common.h"
#include "model_point.h"
#include "dataset_descriptor.h"

//
class library;

//  Wraps up a SQLite database filled with model_point elements.
//
//  A point set can have a ton of attributes to it (columns of data),
//  Here is a minimum description of an element in the database...
//  :   [+] coord-x
//      [+] coord-y
//      [+] class_name
//  There will then be probability values for other class values of the point's class-type.
//      [+] class 0 prob
//      [+] class 1 prob
//      [+] class ... prob
//      [+] class n prob
//  The remaining columns of an element will look like...
//      [+] attribte value 0
//      [+] attribte value 1
//      [+] attribte value ...
//      [+] attribte value n
//
//  All values are strings to account for how they could be anything.
//
//  The table will also have a description object that notes the type of each attribute
//  value, the number of possible class-types, etc, etc, all the meta details the system
//  can use to properly handle types.
//
class model_point_database
{
public:
    model_point_database( library *lib, dataset_descriptor &descriptor, QList<model_point> *points, bool replace );


    //
    bool get_point( int index, model_point *point, dataset_descriptor &descriptor, bool normal_distance  );
    int num_points();

    //
    bool load_database( dataset_descriptor &descriptor );

    //
    QSqlDatabase* database();

    //
    void pick_instance( qreal x, qreal y, qreal r );
private:

    //
    void erase_existing_database_file( QString path );

    //
    void find_num_points_in_table();
    void find_max_distance();

    //
    bool init_database( dataset_descriptor &descriptor );
    bool init_table( dataset_descriptor &descriptor );
    QString find_table_string( dataset_descriptor &descriptor );

    //
    bool insert_points( QList<model_point> &points );
    bool insert_point( int index, const model_point &point );
    QString point_to_insert_query( int index, const model_point &point );

    //
    void output_point( model_point &point );
    void database_entry_to_point( QSqlRecord& record, model_point *point, dataset_descriptor &descriptor   );

    //
    void check_sql_error();    

    //++++++++++++++++++++++++++++++++++
    void label_table( dataset_descriptor &descriptor );
    void label_model( QSqlTableModel *model, dataset_descriptor &descriptor );
    void label_column_categories( QSqlTableModel *model, dataset_descriptor &descriptor, int col );
    bool get_label( dataset_descriptor &descriptor, int val, QString col_name, QString& new_val );
    //++++++++++++++++++++++++++++++++++


    //
    library *_ref_library;

    //
    QSqlDatabase _db;

    //
    int _num_points;
    float _max_distance;
    float _max_x, _max_y;

    //
    bool _replace;

    //
    QMutex _mutex;
};

#endif // MODEL_POINT_DATABASE_H

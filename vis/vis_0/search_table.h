#ifndef SEARCH_TABLE_H
#define SEARCH_TABLE_H

//
#include "common.h"
#include "dataset_descriptor.h"
#include "dataset_descriptor.h"
#include "model_point_database.h"

//
class library;
class model_point;

//
class search_table
{
public:
    search_table( library *lib, QString filter );
    bool get_point( int index, model_point *point );
    void apply_filter();

    //
    library *_ref_library;

    //  If we don't select the model or reset the view we should be able to start from
    //  a QSqlTableModel of our database and remove all rows of data to put in our analysis results.
    //
    QSqlTableModel *_table_model;
    QTableView *_table_view;

    QString _filter;
private:

    void database_entry_to_point( QSqlRecord& record, model_point *point, dataset_descriptor &descriptor  );

    //
    QMutex _mutex;
};

#endif // SEARCH_TABLE_H

#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

//
#include "common.h"
#include "search_table.h"

//
class library;

//
class search_result
{
public:
    search_result( library *lib, std::string filter );


    //
    void set_filter( QString filter );

    //
    library *_ref_library;

    //
    QString _filter;

    //
    search_table _table;

    //
    QString _name;

};

#endif // SEARCH_RESULT_H

#include "search_result.h"
#include "library.h"
#include "dataset_db.h"

static int uid_counter=0;

//+++++++++++++++++++++++++
search_result::search_result( library *lib,  std::string filter  )
    : _ref_library( lib ), _filter( filter.c_str() ), _table(lib, _filter), _name( QString("result %1").arg(uid_counter++))
{}
//+++++++++++++++++++++++++


//+++++++++++++++++++++++++
void search_result::set_filter( QString filter ){

    //
    _filter = filter;

    //
    _table._table_model->setFilter( _filter );
}
//+++++++++++++++++++++++++

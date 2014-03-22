#include "dataset_db_vis.h"
#include "visual_unit.h"
#include "gl_unit.h"

dataset_db_vis::dataset_db_vis( dataset_db* db, visual_unit *vis, gl_unit *gl  )
    :_db(db), _vis(vis), _gl(gl)
{
}

//
dataset_db_vis::~dataset_db_vis(){

    //
    if( _db )
        delete _db;

    //
    if( _vis ){
        //_gl->glDeleteBuffers(2,_vis->_info._vbo_ids);
        delete _vis;
    }
}

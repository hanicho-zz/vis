#ifndef MODEL_COMPILE_H
#define MODEL_COMPILE_H

//
#include "common.h"

//
class library;

//  Compiles datasets into databases.
//  Helps the view_compile class.
//
class model_compile
{
public:
    model_compile( library *lib );

    //
    bool compile( QString base, QString *err );

private:

    //
    library *_ref_library;
};

#endif // MODEL_COMPILE_H

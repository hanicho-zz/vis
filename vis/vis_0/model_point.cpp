#include "model_point.h"

model_point::model_point()
{}

//
qreal model_point::class_value(){

    //
    if( _attribute_values.empty() )
        return 0;

    //
    return _attribute_values.back().toDouble();
}

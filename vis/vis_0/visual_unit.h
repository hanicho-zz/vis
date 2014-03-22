#ifndef VISUAL_UNIT_H
#define VISUAL_UNIT_H

//
#include "common.h"

//
class visual_unit
{
public:
    visual_unit();
    visual_unit( const visual_unit &other );
    ~visual_unit();

    //
    void copy( visual_unit &other );

    //
    visual_unit_gl_info _info;
};

#endif // VISUAL_UNIT_H

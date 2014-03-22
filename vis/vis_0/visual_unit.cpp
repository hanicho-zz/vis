#include "visual_unit.h"

//
visual_unit::visual_unit()
{
    //
    _info._draw_amount=0;
    _info._index_count=0;
    _info._verts_in_single_chart=0;
    _info._ready_to_draw=false;

    //
    _info._vbo_ids[VBO_ELEMENT_VERTEX]=0;
    _info._vbo_ids[VBO_ELEMENT_INDICES]=0;
}

//
visual_unit::visual_unit( const visual_unit &other )
{
    //
    _info._draw_amount=other._info._draw_amount;
    _info._index_count=other._info._index_count;
    _info._verts_in_single_chart=other._info._verts_in_single_chart;
    _info._ready_to_draw=false;

    //
    _info._vbo_ids[VBO_ELEMENT_VERTEX] = other._info._vbo_ids[VBO_ELEMENT_VERTEX];
    _info._vbo_ids[VBO_ELEMENT_INDICES] = other._info._vbo_ids[VBO_ELEMENT_INDICES];

    //  QT uses a thing called "implicit sharing" so we can take a shallow copy and it should be fine.
    //
    _info._vertices = other._info._vertices;
    _info._indices = other._info._indices;
}

visual_unit::~visual_unit(){}

void visual_unit::copy( visual_unit &other ){

    //
    _info._draw_amount=other._info._draw_amount;
    _info._index_count=other._info._index_count;
    _info._verts_in_single_chart=other._info._verts_in_single_chart;
    _info._ready_to_draw=false;

    //
    _info._vbo_ids[VBO_ELEMENT_VERTEX] = other._info._vbo_ids[VBO_ELEMENT_VERTEX];
    _info._vbo_ids[VBO_ELEMENT_INDICES] = other._info._vbo_ids[VBO_ELEMENT_INDICES];

    //  QT uses a thing called "implicit sharing" so we can take a shallow copy and it should be fine.
    //
    _info._vertices = other._info._vertices;
    _info._indices = other._info._indices;
}

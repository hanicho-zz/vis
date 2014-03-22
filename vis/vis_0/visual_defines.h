#ifndef VISUAL_DEFINES_H
#define VISUAL_DEFINES_H

//
#include "common_includes.h"

//  The unit of data that we pass to the device for rendering.
//
typedef struct Vertex
{
    QVector4D XYZW;
    QVector4D RGBA;

    Vertex()
        : XYZW(0,0,0,0), RGBA(0,0,0,0)
    {}
    Vertex(qreal vx,qreal vy,qreal vz,qreal vw, qreal r, qreal g, qreal b,qreal a)
        : XYZW(vx,vy,vz,vw), RGBA(r,g,b,a)
    {}
} Vertex;

//  The _vbo_ids[] indices.
//
#define VBO_ELEMENT_VERTEX      0
#define VBO_ELEMENT_INDICES     1

//
typedef struct visual_unit_gl_info{
    GLuint _vbo_ids[2];
    QVector<Vertex> _vertices;
    QVector<GLushort> _indices;
    GLuint _draw_amount;
    GLuint _index_count;
    GLuint _num_charts;
    int _verts_in_single_chart;
    bool _ready_to_draw;
}visual_unit_gl_info;

//
typedef struct gl_unit_info{
    QMatrix4x4 _projection;
    QGLShaderProgram _qprogram;
    bool _ready_to_init, _did_init;
}gl_unit_info;

#endif // VISUAL_DEFINES_H

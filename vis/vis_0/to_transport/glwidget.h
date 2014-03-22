#ifndef GLWIDGET_H
#define GLWIDGET_H

//
#include <QGLWidget>
#include <QGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QGLShaderProgram>

//
#include <QSlider>

//  Data.
//
//++++++++++++++++
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

#define VBO_ELEMENT_VERTEX      0
#define VBO_ELEMENT_INDICES     1

typedef struct gl_info{
    QMatrix4x4 _projection;
    QGLShaderProgram _qprogram;
    GLuint _vbo_ids[2];
    QVector<Vertex> _vertices;
    QVector<GLushort> _indices;
    GLuint _draw_amount;
    GLuint _index_count;
    int _verts_in_single_chart;
    bool _ready_to_draw;
}gl_info;
//++++++++++++++++


//
class glwidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    glwidget( QWidget  *parent = 0 );
    ~glwidget();

    //
    void set_slider( QSlider *slide );
public slots:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void set_peel_percentage(int value);
private:
    void setup_window();

    void check_error(int location);

    void create_shaders();
    void create_geometry();
    void push_piechart( qreal cx, qreal cy );
    void push_piechart( qreal cx, qreal cy, QList<qreal> &slice_percents );

    void draw_geometry();




    gl_info _info;

    QSlider *_slider;
};

#endif // GLWIDGET_H

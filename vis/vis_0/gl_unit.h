#ifndef GL_UNIT_H
#define GL_UNIT_H

//
#include "common.h"

//
class library;

//
class gl_unit : public QGLWidget, public QGLFunctions
{
    Q_OBJECT
public:
    gl_unit( library *lib, QWidget  *parent = 0 );
    ~gl_unit();

public slots:

    //
    void set_visual_unit( visual_unit_gl_info* info );

    //
    void initializeGL();

    //  Draw.
    //
    void resizeGL(int w, int h);
    void paintGL();

    //  Input.
    //
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:

    //
    void setup_window();

    //
    void delayed_init();
    void create_shaders();

    //
    void draw_geometry();

    //
    library *_ref_library;

    //
    gl_unit_info _gl_info;

    //
    visual_unit_gl_info* _visual_unit_info;
};

#endif // GL_UNIT_H

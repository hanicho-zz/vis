#include "gl_unit.h"
#include "library.h"


//
//++++++++++++++++++++++
gl_unit::gl_unit( library *lib, QWidget *parent)
    : QGLWidget(parent), _visual_unit_info(0), _ref_library(lib)
{
    //
    setMouseTracking(true);

    //
    _gl_info._ready_to_init=true;
    _gl_info._did_init=false;
}
//++++++++++++++++++++++

//  Destruct.
//
//++++++++++++++++++++++
gl_unit::~gl_unit()
{}
//++++++++++++++++++++++

//  Init.
//
//++++++++++++++++++++++
void gl_unit::delayed_init(){

    //
    if( !_gl_info._ready_to_init || _gl_info._did_init )
        return;

    //
    _gl_info._did_init=true;

    //
    qglClearColor(Qt::black);
    create_shaders();

    // Enable depth buffer.
    //
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling.
    //
    glEnable(GL_CULL_FACE);

}
//++++++++++++++++++++++

//  Opengl Callbacks.
//
//++++++++++++++++++++++
void gl_unit::initializeGL() {

    //
    initializeGLFunctions();

    //
    _gl_info._ready_to_init=true;

}

void gl_unit::resizeGL(int w, int h) {

    //
    //
    glViewport(0, 0, w, h);

    // Calculate aspect ratio.
    //
    //qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees.
    //
    //const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection.
    //
    _gl_info._projection.setToIdentity();

    // Set perspective projection.
    //
    //_info._projection.perspective(fov, aspect, zNear, zFar);
    qreal left_=-1.94;
    qreal right_=1;
    qreal bottom_=-1.4;
    qreal top_=1.4;
    qreal near_ = 1;
    qreal far_ = 7;
    _gl_info._projection.ortho( left_,right_,bottom_,top_, near_, far_ );
}

void gl_unit::paintGL() {

    //
    delayed_init();

    //
    if( !_visual_unit_info || !_gl_info._did_init )
        return;

    // Clear color and depth buffer.
    //
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation.
    //
    QMatrix4x4 matrix;
    matrix.translate( 0,0, -5.0);

    // Set modelview-projection matrix.
    //
    _gl_info._qprogram.setUniformValue("mvp_matrix", _gl_info._projection * matrix);

    //  Draw.
    //
    draw_geometry();
}

void gl_unit::mousePressEvent(QMouseEvent *event) {

    //
    qreal mx = event->x();
    qreal my = event->y();

    //  Normalize the coordinate so it doesn't matter if it's stretched.
    //
    mx = mx / this->width();
    my = ( this->height()- my ) / this->height();

    //  Fit the coordinates to our projection.
    //
    mx = (mx * 2.94) - 1.94;
    my = (my * 2.8) - 1.4;

    //
    _ref_library->pick_instance( mx, my, 0.015 );
}
void gl_unit::mouseMoveEvent(QMouseEvent *event) {
    //printf("%d, %d\n", event->x(), event->y());
}

void gl_unit::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    default:
        event->ignore();
        break;
    }
}
//++++++++++++++++++++++

//  Shaders.
//
//++++++++++++++++++++++

//  Loads default shaders from hard code.
//  This promotes not tampering with the shader code.
//  If the need for flexibility arises then I will load in file shaders instead.
//
void gl_unit::create_shaders(){

    //
    const GLchar* VertexShader =
    {
        "#ifdef GL_ES\n"\
        "precision mediump int;\n"\
        "precision mediump float;\n"\
        "#endif\n"\
        "uniform mat4 mvp_matrix;\n"\

        "attribute vec4 a_position;\n"\
        "attribute vec4 a_color;\n"\
        "varying vec4 v_color;\n"\

        "void main(void)\n"\
        "{\n"\
        "   gl_Position = mvp_matrix * a_position;\n"\
        "   v_color = a_color;\n"\
        "}\n"
    };
    const GLchar* FragmentShader =
    {
        "#ifdef GL_ES\n"\
        "precision mediump int;\n"\
        "precision mediump float;\n"\
        "#endif\n"\
        "varying vec4 v_color;\n"\

        "void main(void)\n"\
        "{\n"\
        " gl_FragColor = v_color;\n"\
        "}\n"
    };

    // Override system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compile vertex shader
    if (!_gl_info._qprogram.addShaderFromSourceCode(QGLShader::Vertex, VertexShader))
        close();

    // Compile fragment shader
    if (!_gl_info._qprogram.addShaderFromSourceCode(QGLShader::Fragment, FragmentShader))
        close();

    // Link shader pipeline
    if (!_gl_info._qprogram.link())
        close();

    // Bind shader pipeline for use
    if (!_gl_info._qprogram.bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");

}
//++++++++++++++++++++++

//  Geometry.
//
//++++++++++++++++++++++
void gl_unit::draw_geometry(){

    //  Without geometry, don't draw.
    //
    if( _visual_unit_info == 0 )
        return;

    //  Tell OpenGL which VBOs to use.
    //
    glBindBuffer(GL_ARRAY_BUFFER, _visual_unit_info->_vbo_ids[VBO_ELEMENT_VERTEX]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _visual_unit_info->_vbo_ids[VBO_ELEMENT_INDICES]);

    //
    helpers::check_error_gl(10);

    //  Offset for position.
    //
    quintptr offset = 0;

    //  Tell the OpenGL programmable pipeline how to locate vertex position data.
    //
    int vertexLocation = _gl_info._qprogram.attributeLocation("a_position");
    _gl_info._qprogram.enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offset);
    helpers::check_error_gl(11);

    //  Offset for texture coordinate.
    //
    offset += sizeof(QVector4D);

    //  Tell the OpenGL programmable pipeline how to locate vertex color data.
    //
    int colorLocation = _gl_info._qprogram.attributeLocation("a_color");
    _gl_info._qprogram.enableAttributeArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offset);
    helpers::check_error_gl(12);

    //  Draw cube geometry using indices from VBO.
    //
    glDrawArrays( GL_TRIANGLES, 0, _visual_unit_info->_draw_amount );
    //glDrawArrays( GL_TRIANGLES, 0, _visual_unit_info->_vertices.size() );
    helpers::check_error_gl(13);
}
void gl_unit::set_visual_unit( visual_unit_gl_info* info ){

    //
    _visual_unit_info=info;

    //
    updateGL();
}

//++++++++++++++++++++++

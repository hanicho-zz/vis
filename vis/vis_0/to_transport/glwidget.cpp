#include "glwidget.h"
#include <QtGui/QMouseEvent>
#include <qDebug>


//  Peel Slider.
//
//++++++++++++++++++++++
glwidget::glwidget( QWidget *parent)
    : QGLWidget(parent), _slider(0)
{
    //
    setMouseTracking(true);

    //
    _info._draw_amount=0;
    _info._index_count=0;
    _info._verts_in_single_chart=0;
    _info._ready_to_draw=false;
}
//++++++++++++++++++++++

//  Peel Slider.
//
//++++++++++++++++++++++
glwidget::~glwidget(){

    //
    glDeleteBuffers(2,_info._vbo_ids);
}
//++++++++++++++++++++++

//  Slider.
//
//++++++++++++++++++++++
void glwidget::set_slider( QSlider *slide ){

    //
    _slider = slide;
}
//++++++++++++++++++++++

//  Opengl Callbacks.
//
//++++++++++++++++++++++
void glwidget::initializeGL() {

    //
    initializeGLFunctions();
    qglClearColor(Qt::black);
    create_shaders();
    create_geometry();

    // Enable depth buffer.
    //
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling.
    //
    glEnable(GL_CULL_FACE);
}

void glwidget::resizeGL(int w, int h) {

    //
    //
    glViewport(0, 0, w, h);

    // Calculate aspect ratio.
    //
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees.
    //
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection.
    //
    _info._projection.setToIdentity();

    // Set perspective projection.
    //
    //_info._projection.perspective(fov, aspect, zNear, zFar);
    _info._projection.ortho( -0.1, 2, -0.1, 2, 3, 7 );
}

void glwidget::paintGL() {

    //
    if( !_info._ready_to_draw )
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
    _info._qprogram.setUniformValue("mvp_matrix", _info._projection * matrix);

    //  Draw.
    //
    draw_geometry();
}

void glwidget::mousePressEvent(QMouseEvent *event) {

}
void glwidget::mouseMoveEvent(QMouseEvent *event) {
    //printf("%d, %d\n", event->x(), event->y());
}

void glwidget::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}
//++++++++++++++++++++++

//  Shaders.
//
//++++++++++++++++++++++
void glwidget::create_shaders(){

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
    if (!_info._qprogram.addShaderFromSourceCode(QGLShader::Vertex, VertexShader))
        close();

    // Compile fragment shader
    if (!_info._qprogram.addShaderFromSourceCode(QGLShader::Fragment, FragmentShader))
        close();

    // Link shader pipeline
    if (!_info._qprogram.link())
        close();

    // Bind shader pipeline for use
    if (!_info._qprogram.bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");

}
//++++++++++++++++++++++

//  Geometry.
//
//++++++++++++++++++++++
void glwidget::create_geometry(){

    //
    glGenBuffers(2,_info._vbo_ids);

    /*
    //  Generate our vertices.
    //  (triangles).
    //
    QVector3D tstart(-1.8,1.8,0);
    qreal tstep=0.2;
    qreal toffset=0.05;
    int index=0;
    for(int r=0; r<19; r++){
        for(int c=0; c<19; c++){

            //  Vertex.
            //
            qreal cx = tstart.x() + tstep*c; qreal cy = tstart.y() + tstep*-r;
            _info._vertices.push_back( Vertex(cx-toffset,cy-toffset,0,1,     1.0f,0.0f,0.0f,1.0f) );
            _info._vertices.push_back( Vertex(cx+toffset,cy-toffset,0,1,     0.0f,1.0f,0.0f,1.0f) );
            _info._vertices.push_back( Vertex(cx,        cy+toffset,0,1,     0.0f,0.0f,1.0f,1.0f) );

            //  Glue.
            //
            _info._vertices.push_back( Vertex(0,0,0,1,    0,0,0,0) );
            _info._vertices.push_back( Vertex(0,0,0,1,    0,0,0,0) );
            _info._vertices.push_back( Vertex(0,0,0,1,    0,0,0,0) );

            //  Index.
            //
            _info._indices.push_back(index++);  _info._indices.push_back(index++);  _info._indices.push_back(index++);
            _info._indices.push_back(index++);  _info._indices.push_back(index++);  _info._indices.push_back(index++);
        }
    }
    _info._index_count=index;
    */


    //  Generate vertices.
    //  (piecharts).
    //
    QList<qreal> slice_percentages;
    slice_percentages.push_back(0.5);
    slice_percentages.push_back(0.2);
    slice_percentages.push_back(0.1);
    slice_percentages.push_back(0.1);
    slice_percentages.push_back(0.1);
    QVector2D tstart(1.9,1.9);
    qreal rand_0_1=0;
    int num_charts=200;
    for(int r=0; r<num_charts; r++){

        //  Random center.
        //
        rand_0_1 = qreal( qrand() / (RAND_MAX + 1.0) );
        qreal cx = tstart.x() * rand_0_1;
        rand_0_1 = qreal( qrand() / (RAND_MAX + 1.0) );
        qreal cy = tstart.y() * rand_0_1;

        //
        push_piechart( cx, cy, slice_percentages);
    }

    //
    _slider->setRange( 0, num_charts*_info._verts_in_single_chart );
    _slider->setSingleStep( _info._verts_in_single_chart );
    _slider->setPageStep( _info._verts_in_single_chart );
    _slider->setTickInterval( 5*_info._verts_in_single_chart );

    //
    check_error(20);

    //  Vertices.
    //
    glBindBuffer(GL_ARRAY_BUFFER, _info._vbo_ids[VBO_ELEMENT_VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, _info._vertices.count() * sizeof(Vertex), &_info._vertices[0], GL_STATIC_DRAW);

    //  Indices.
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _info._vbo_ids[VBO_ELEMENT_INDICES]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _info._indices.count() * sizeof(GLushort), &_info._indices[0], GL_STATIC_DRAW);

    //
    check_error(21);

    //  How many vertices.
    //
    qDebug() << QString("num vertices [val:%1]")
                .arg(_info._vertices.count());

    //  How many megabytes is our vbo.
    //
    int nBufferSize = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &nBufferSize);
    int originalVertexArraySize = ( nBufferSize / sizeof(Vertex) );
    qDebug() << QString("vbo size [size:%1mb]")
                .arg( (qreal)originalVertexArraySize / (qreal)1000000.0 );

    //
    _info._ready_to_draw=true;
    updateGL();
}


void glwidget::draw_geometry(){

    // Tell OpenGL which VBOs to use.
    //
    glBindBuffer(GL_ARRAY_BUFFER, _info._vbo_ids[VBO_ELEMENT_VERTEX]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _info._vbo_ids[VBO_ELEMENT_INDICES]);

    check_error(10);

    // Offset for position.
    //
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data.
    //
    int vertexLocation = _info._qprogram.attributeLocation("a_position");
    _info._qprogram.enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offset);
    check_error(11);

    // Offset for texture coordinate.
    //
    offset += sizeof(QVector4D);

    // Tell OpenGL programmable pipeline how to locate vertex color data.
    //
    int colorLocation = _info._qprogram.attributeLocation("a_color");
    _info._qprogram.enableAttributeArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offset);
    check_error(12);

    // Draw cube geometry using indices from VBO.
    //
    glDrawArrays( GL_TRIANGLES, 0, _info._draw_amount );
    check_error(13);
}
//++++++++++++++++++++++

//  Error.
//
//++++++++++++++++++++++
void glwidget::check_error( int location){
    //  Error output.
    //
    GLenum ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        qDebug() << QString( "ERROR [location: %1]: [error value: %2]\n" )
                    .arg(location)
                    .arg( ErrorCheckValue );
        //
        //exit(-1);
    }
}

void glwidget::set_peel_percentage(int value){

    //  Clamp the steps size to [_info._verts_in_single_chart].
    //
    int div = value / _info._verts_in_single_chart;
    _info._draw_amount = div*_info._verts_in_single_chart;
    //qDebug() << QString("draw amount [verts:%1]").arg(_info._draw_amount);

    //  Let the paintGL function know that it's code's values have updated
    //  and to reflect that.
    //
    updateGL();

    /*
    //  Print Debug.
    //
    qreal percent=0;
    if( _info._draw_amount != 0 )
        percent = (qreal)_info._draw_amount / (qreal)_info._vertices.count();
    qDebug() << QString("[peel:%1]")
                .arg( (int)(percent*100) );
    */
}
//++++++++++++++++++++++

//  Pie Charts.
//
//++++++++++++++++++++++
void glwidget::push_piechart( qreal cx, qreal cy ){

    //  Create the back of the piechart.
    //
    {
        QVector3D back_color(1,1,1);
        qreal r=0.4;
        int num=20;
        qreal step = 360.0/num;
        qreal s,c;
        for(int ii=0; ii<num; ii++){

            //  Rotate around the center by a radius.
            //
            qreal t=step*ii;
            t *= (3.14159265359 / 180.0);
            s = sin(t);
            c = cos(t);
            qreal x=c*(cx+r)-s*(cy+r);
            qreal y=s*(cx+r)+c*(cy+r);

            //  Create the vertex/index.
            //
            //_info._vertices.push_back( Vertex( x,y,0,1, back_color.x(),back_color.y(),back_color.z(),1) );
            //_info._indices.push_back( _info._index_count++ );
        }
    }

    //  Create the slices.
    //
    int slices=3;
    {
        //  Create the back of the piechart.
        //
        QVector3D slice_colors[] = {
            QVector3D(1,0,0),
            QVector3D(0,1,0),
            QVector3D(0,0,1)
        };
        qreal r=0.05;
        int num=20;
        qreal step = 360.0/num;
        qreal s,c;
        int slice_step=num/slices;
        int slice_count=0;
        int slice=0;
        for(int ii=0; ii<num; ii++){

            //
            if( slice_count >= slice_step ){
                slice_count=0;
                slice++;
                if( slice >= slices )
                    slice=0;
            }
            slice_count++;

            //  Rotate around the center by a radius.
            //
            qreal t=step*ii;
            t *= (3.14159265359 / 180.0);
            s = sin(t);
            c = cos(t);
            qreal x_here=cx + (c*r-s*r);
            qreal y_here=cy + (s*r+c*r);
            //  Rotate around the center by a radius.
            //
            t=step*(ii+1);
            t *= (3.14159265359 / 180.0);
            s = sin(t);
            c = cos(t);
            qreal x_next=cx + (c*r-s*r);
            qreal y_next=cy + (s*r+c*r);



            //  Create the triangle.
            //
            _info._vertices.push_back( Vertex( cx,cy,0,1, slice_colors[slice].x(),slice_colors[slice].y(),slice_colors[slice].z(),1) );
            _info._vertices.push_back( Vertex( x_here,y_here,0,1, slice_colors[slice].x(),slice_colors[slice].y(),slice_colors[slice].z(),1) );
            _info._vertices.push_back( Vertex( x_next,y_next,0,1, slice_colors[slice].x(),slice_colors[slice].y(),slice_colors[slice].z(),1) );
            _info._indices.push_back( _info._index_count++ );
            _info._indices.push_back( _info._index_count++ );
            _info._indices.push_back( _info._index_count++ );

        }
    }


    //  Glue.
    //
    _info._vertices.push_back( Vertex( 0,0,0,1, 0,0,0,1) );
    _info._vertices.push_back( Vertex( 0,0,0,1, 0,0,0,1) );
    _info._vertices.push_back( Vertex( 0,0,0,1, 0,0,0,1) );
    _info._indices.push_back( _info._index_count++ );
    _info._indices.push_back( _info._index_count++ );
    _info._indices.push_back( _info._index_count++ );

    //  Find the number of vertices in a single pie chart.
    //
    if( _info._verts_in_single_chart == 0 ){
        _info._verts_in_single_chart=_info._vertices.count();
        qDebug() << QString("Vertices in single chart [count:%1]")
                    .arg(_info._verts_in_single_chart);
    }
}

void glwidget::push_piechart( qreal cx, qreal cy, QList<qreal> &slice_percents ){

    //  Preconditions:
    //  (1) - slice_percents adds up to 360.

    //  Create the slices.
    //
    {
        //  Create the back of the piechart.
        //
        QVector3D slice_colors[] = {
            QVector3D(1,0,0),
            QVector3D(0,1,0),
            QVector3D(0,0,1),
            QVector3D(1,1,0),
            QVector3D(0,1,1),
            QVector3D(1,0,1),
            QVector3D(1,1,1)
        };
        qreal r=0.05;
        int num=30;
        qreal s,c;
        qreal current_degree=0;
        int color_index=0;
        int steps_per_slice = num / slice_percents.count();
        //
        for( int slice=0; slice<slice_percents.count(); slice++ ){

            //  Find how many degrees we will cover in each step for THIS slice.
            //  It depends on the slice's percentage o 360 and how many steps the slice gets.
            //
            //qDebug() << QString("slice percent [p:%1]").arg(slice_percents.at(slice));
            qreal single_step_degrees = (slice_percents.at(slice)*360.0) / steps_per_slice;

            //  We draw the slice in trianglular steps.
            //
            for( int step=0; step<steps_per_slice; step++ ){


                //  Rotate around the center by a radius.
                //  (This point.)
                //  Take our step and add in our current total degree so that we
                //      keep our progress around the circle.
                //
                qreal t=single_step_degrees*step;
                t = (t+current_degree) * (3.14159265359 / 180.0);
                s = sin(t);     c = cos(t);
                qreal x_here=cx + (c*r-s*r);
                qreal y_here=cy + (s*r+c*r);

                //  Rotate around the center by a radius.
                //  (Next point.)
                //
                t=single_step_degrees*(step+1);
                t = (t+current_degree)*(3.14159265359 / 180.0);
                s = sin(t);     c = cos(t);
                qreal x_next=cx + (c*r-s*r);
                qreal y_next=cy + (s*r+c*r);

                //  Create the triangle.
                //
                qreal col_r=slice_colors[slice].x();
                qreal col_g=slice_colors[slice].y();
                qreal col_b=slice_colors[slice].z();
                _info._vertices.push_back( Vertex( cx,cy,0,1,           col_r,col_g,col_b,1) );
                _info._vertices.push_back( Vertex( x_here,y_here,0,1,   col_r,col_g,col_b,1) );
                _info._vertices.push_back( Vertex( x_next,y_next,0,1,   col_r,col_g,col_b,1) );
                _info._indices.push_back( _info._index_count++ );
                _info._indices.push_back( _info._index_count++ );
                _info._indices.push_back( _info._index_count++ );
            }


            //  Sum up our total degrees covered.
            //
            current_degree += slice_percents.at(slice)*360.0;
            //qDebug() << QString("current degree [deg:%1]").arg(current_degree);


            //  Cycle the slice colors.
            //
            color_index++;
            if( color_index > 6 )
                color_index=0;
        }


    }

    //  Find the number of vertices in a single pie chart.
    //
    if( _info._verts_in_single_chart == 0 ){
        _info._verts_in_single_chart=_info._vertices.count();
        qDebug() << QString("Vertices in single chart [count:%1]")
                    .arg(_info._verts_in_single_chart);
    }
}
//++++++++++++++++++++++

#include "visual_unit_factory.h"
#include "buffer_worker.h"
#include "library.h"
#include "search_table.h"

visual_unit_factory::visual_unit_factory( library* lib )
    :   _active_visual_unit(0), _ref_library(lib)
{
}

//
void visual_unit_factory::create_piecharts( dataset_db &db, QGLFunctions qglf ){

    //
    if( _active_visual_unit )
        delete _active_visual_unit;

    //
    _active_visual_unit = new visual_unit();

    //
    generate_geometry( db, qglf );
    //generate_geometry_parallel( db, qglf );
}
//
void visual_unit_factory::create_search_piecharts( QGLFunctions qglf ){

    //
    if( _active_visual_unit )
        delete _active_visual_unit;

    //
    _active_visual_unit = new visual_unit();

    //
    generate_geometry_search( qglf );
}

//
void visual_unit_factory::get_unit( visual_unit *unit ){

    //
    if( !_active_visual_unit )
        return;

    //
    unit->copy( *_active_visual_unit );
}

//  Geometry.
//
//++++++++++++++++++++++
void visual_unit_factory::generate_geometry( dataset_db &db, QGLFunctions qglf ){

    //
    helpers::debug_out( QString("creating geometry for dataset: [%1]...").arg( db.name()) );

    //  Create the buffers.
    //
    qglf.glGenBuffers(2,_active_visual_unit->_info._vbo_ids);

    //  Get our list of colors.
    //
    std::vector<QVector3D> colors = db.descriptor()->list_color();
    QVector3D true_color;

    //  Go through each point in the database.
    //
    unsigned int stamp = helpers::timestamp();
    bool result=true;
    model_point point;
    int num_points = db.num_points();
    //int num_points = 10;
    for( int ii=0; ii<num_points; ii++ ){

        //  Get the next point.
        //
        result = db.get_point( ii, &point, true );

        //  End if we didn't get a point.
        //
        if( !result )
            break;

        //  Find the true color.
        //
        true_color = db.descriptor()->class_option_to_color( point._attribute_class );

        //  Create a piechart for the point.
        //
        push_piechart( point._position.x(), point._position.y(), point._probability_values, true_color, colors, 0.015 );
    }

    float elapsed = helpers::milliseconds_to_seconds( helpers::time_elapsed(stamp) );
    helpers::debug_out(QString("glyphs finished: [seconds: %1]").arg(elapsed));

    //  Empty dataset?
    //
    if( num_points == 0 )
        push_fake_piechart();

    //
    helpers::debug_out( QString("Created glyphs [num: %1]").arg( db.num_points() ) );

    //
    helpers::check_error_gl(20);

    //  Vertices.
    //
    qglf.glBindBuffer(GL_ARRAY_BUFFER, _active_visual_unit->_info._vbo_ids[VBO_ELEMENT_VERTEX]);
    qglf.glBufferData(GL_ARRAY_BUFFER, _active_visual_unit->_info._vertices.count() * sizeof(Vertex), &_active_visual_unit->_info._vertices[0], GL_STATIC_DRAW);

    //  Indices.
    //
    qglf.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _active_visual_unit->_info._vbo_ids[VBO_ELEMENT_INDICES]);
    qglf.glBufferData(GL_ELEMENT_ARRAY_BUFFER, _active_visual_unit->_info._indices.count() * sizeof(GLushort), &_active_visual_unit->_info._indices[0], GL_STATIC_DRAW);

    //
    helpers::check_error_gl(21);

    //  How many vertices.
    //
    helpers::debug_out( QString("...num vertices [val:%1]")
                        .arg(_active_visual_unit->_info._vertices.count()) );
    _active_visual_unit->_info._draw_amount = _active_visual_unit->_info._vertices.count();

    //  How many charts?
    //
    _active_visual_unit->_info._num_charts = _active_visual_unit->_info._vertices.count() / _active_visual_unit->_info._verts_in_single_chart;

    //  How many megabytes is our vbo.
    //
    int nBufferSize = 0;
    qglf.glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &nBufferSize);
    int originalVertexArraySize = ( nBufferSize / sizeof(Vertex) );
    helpers::debug_out( QString("...vbo size [size:%1mb]")
                        .arg( (qreal)originalVertexArraySize / (qreal)1000000.0 ) );

    //
    _active_visual_unit->_info._ready_to_draw=true;
}


void visual_unit_factory::generate_geometry_search( QGLFunctions qglf ){

    //
    helpers::debug_out( QString("creating geometry for search ")  );

    //  Create the buffers.
    //
    qglf.glGenBuffers(2,_active_visual_unit->_info._vbo_ids);

    //
    dataset_db* db = _ref_library->_active_database;

    //  Get our list of colors.
    //
    std::vector<QVector3D> colors = db->descriptor()->list_color();
    QVector3D true_color;

    //  Go through each point in the database.
    //
    unsigned int stamp = helpers::timestamp();
    bool result=true;
    model_point point;
    int num_points = db->num_points();
    //int num_points = 10;
    for( int ii=0; ii<num_points; ii++ ){

        //  Get the next point.
        //
        //result = db.get_point( ii, &point, true );
        _ref_library->_active_search_table->get_point( ii, &point );

        //  End if we didn't get a point.
        //
        if( !result )
            break;

        //  Find the true color.
        //
        true_color = db->descriptor()->class_option_to_color( point._attribute_class );

        //  Create a piechart for the point.
        //
        push_piechart( point._position.x(), point._position.y(), point._probability_values, true_color, colors, 0.015 );
    }

    float elapsed = helpers::milliseconds_to_seconds( helpers::time_elapsed(stamp) );
    helpers::debug_out(QString("glyphs finished: [seconds: %1]").arg(elapsed));

    //  Empty dataset?
    //
    if( num_points == 0 )
        push_fake_piechart();

    //
    helpers::debug_out( QString("Created glyphs [num: %1]").arg( num_points ) );

    //
    helpers::check_error_gl(20);

    //  Vertices.
    //
    qglf.glBindBuffer(GL_ARRAY_BUFFER, _active_visual_unit->_info._vbo_ids[VBO_ELEMENT_VERTEX]);
    qglf.glBufferData(GL_ARRAY_BUFFER, _active_visual_unit->_info._vertices.count() * sizeof(Vertex), &_active_visual_unit->_info._vertices[0], GL_STATIC_DRAW);

    //  Indices.
    //
    qglf.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _active_visual_unit->_info._vbo_ids[VBO_ELEMENT_INDICES]);
    qglf.glBufferData(GL_ELEMENT_ARRAY_BUFFER, _active_visual_unit->_info._indices.count() * sizeof(GLushort), &_active_visual_unit->_info._indices[0], GL_STATIC_DRAW);

    //
    helpers::check_error_gl(21);

    //  How many vertices.
    //
    helpers::debug_out( QString("...num vertices [val:%1]")
                        .arg(_active_visual_unit->_info._vertices.count()) );
    _active_visual_unit->_info._draw_amount = _active_visual_unit->_info._vertices.count();

    //  How many charts?
    //
    _active_visual_unit->_info._num_charts = _active_visual_unit->_info._vertices.count() / _active_visual_unit->_info._verts_in_single_chart;

    //  How many megabytes is our vbo.
    //
    int nBufferSize = 0;
    qglf.glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &nBufferSize);
    int originalVertexArraySize = ( nBufferSize / sizeof(Vertex) );
    helpers::debug_out( QString("...vbo size [size:%1mb]")
                        .arg( (qreal)originalVertexArraySize / (qreal)1000000.0 ) );

    //
    _active_visual_unit->_info._ready_to_draw=true;
}



void visual_unit_factory::errorString(QString err){
    helpers::debug_out( QString("parallel worker error: [err: %1]").arg(err) );
}

void visual_unit_factory::generate_geometry_parallel( dataset_db &db, QGLFunctions qglf ){

    //
    helpers::debug_out( QString("creating geometry for dataset: [%1]...").arg( db.name()) );

    //  Create the buffers.
    //
    qglf.glGenBuffers(2,_active_visual_unit->_info._vbo_ids);

    //  How many threads will we use?
    //
    int ideal = QThread::idealThreadCount();

    //  Go through each point in the database.
    //
    std::vector<Vertex> _vertices;
    std::vector<GLshort> _indices;
    int num_points = db.num_points();
    if( num_points > 0 ){

        int points_per_thread = num_points / ideal;

        //  Create the workers.
        //
        std::vector<buffer_worker*> workers;
        std::vector<QThread*> threads;
        for( int ii=0; ii<ideal; ii++ )
            workers.push_back( new buffer_worker( points_per_thread, points_per_thread*ii, &db ) );

        //  Thread our workers.
        //
        for( int ii=0; ii<workers.size(); ii++ ){
            buffer_worker *worker = workers.at(ii);
            QThread* thread = new QThread;
            worker->moveToThread(thread);
            connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
            connect(thread, SIGNAL(started()), worker, SLOT(process()));
            connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
            //connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            thread->start();
            threads.push_back(thread);
        }

        //  Wait for all workers to finish.
        //  Break when all of our workers are marked finished.
        //
        unsigned int stamp = helpers::timestamp();
        bool done=false;
        while( !done ){
            done=true;
            for( int ii=0; ii<workers.size(); ii++ ){
                if( !workers.at(ii)->_finished )
                    done=false;
            }
        }
        float elapsed = helpers::milliseconds_to_seconds( helpers::time_elapsed(stamp) );
        helpers::debug_out(QString("threads finished: [seconds: %1]").arg(elapsed));

        //  Concat all of the fragments.
        //

        //  Find our amounts for reserving.
        //
        int fragments_verts_count = 0;
        int fragments_index_count = 0;
        for( int ii=0; ii<workers.size(); ii++ ){
            buffer_worker *worker = workers.at(ii);
            fragments_verts_count += worker->_fragment_vertices.size();
            fragments_index_count += worker->_fragment_indices.size();
        }
        _vertices.reserve( fragments_verts_count );
        _indices.reserve( fragments_index_count );

        //  Insert all fragments.
        //
        for( int ii=0; ii<workers.size(); ii++ ){
            buffer_worker *worker = workers.at(ii);
            _vertices.insert( _vertices.end(), worker->_fragment_vertices.begin(), worker->_fragment_vertices.end() );
            _indices.insert( _indices.end(), worker->_fragment_indices.begin(), worker->_fragment_indices.end() );
        }

    }

    //
    else
        push_fake_piechart();

    //
    helpers::debug_out( QString("Created glyphs [num: %1]").arg( num_points ) );

    //
    helpers::check_error_gl(20);

    //  Vertices.
    //
    qglf.glBindBuffer(GL_ARRAY_BUFFER, _active_visual_unit->_info._vbo_ids[VBO_ELEMENT_VERTEX]);
    qglf.glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    //  Indices.
    //
    qglf.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _active_visual_unit->_info._vbo_ids[VBO_ELEMENT_INDICES]);
    qglf.glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLushort), &_indices[0], GL_STATIC_DRAW);

    //
    helpers::check_error_gl(21);

    //  How many vertices.
    //
    helpers::debug_out( QString("...num vertices [val:%1]")
                        .arg(_vertices.size()) );
    _active_visual_unit->_info._draw_amount = _vertices.size();

    //  How many charts?
    //
    //_active_visual_unit->_info._num_charts = _vertices.count() / _active_visual_unit->_info._verts_in_single_chart;

    //  How many megabytes is our vbo.
    //
    int nBufferSize = 0;
    qglf.glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &nBufferSize);
    int originalVertexArraySize = ( nBufferSize / sizeof(Vertex) );
    helpers::debug_out( QString("...vbo size [size:%1mb]")
                        .arg( (qreal)originalVertexArraySize / (qreal)1000000.0 ) );

    //
    _active_visual_unit->_info._ready_to_draw=true;
}


//++++++++++++++++++++++


//  Pie Charts.
//
//++++++++++++++++++++++

void visual_unit_factory::push_piechart( qreal cx, qreal cy, std::vector<double> &slice_percents, QVector3D true_color, std::vector<QVector3D> &silce_colors, qreal radius, int steps ){

    //  Preconditions:
    //  (1) - slice_percents adds up to 1.

    {

        //
        qreal r=radius;
        qreal s,c;
        qreal current_degree=0;
        int color_index=0;
        qreal toRadians = 3.14159265359 / 180.0;


        //  Create the slices.
        //
        {
            current_degree=0;
            for( int slice=0; slice<slice_percents.size(); slice++ ){


                //  Find how many steps this slice will take.
                //  Each slice has a number of steps dependant on their glyph percantage.
                //
                int slice_steps = steps * slice_percents.at(slice);

                //  Find how many degrees we will cover in each step for THIS slice.
                //  It depends on the slice's percentage of 360 and how many steps the slice gets.
                //
                //qDebug() << QString("slice percent [p:%1]").arg(slice_percents.at(slice));
                qreal single_step_degrees = (slice_percents.at(slice)*360.0) / slice_steps;


                //  We draw the slice in trianglular steps.
                //
                for( int step=0; step<slice_steps; step++ ){


                    //  Rotate around the center by a radius.
                    //  (This point.)
                    //  Take our step and add in our current total degree so that we
                    //      keep our progress around the circle.
                    //
                    qreal t=single_step_degrees*step;
                    t = (t+current_degree) * toRadians;
                    s = sin(t);     c = cos(t);
                    qreal x_here=cx + (c*r-s*r);
                    qreal y_here=cy + (s*r+c*r);

                    //  Rotate around the center by a radius.
                    //  (Next point.)
                    //
                    t=single_step_degrees*(step+1);
                    t = (t+current_degree)*toRadians;
                    s = sin(t);     c = cos(t);
                    qreal x_next=cx + (c*r-s*r);
                    qreal y_next=cy + (s*r+c*r);

                    //  Create the triangle.
                    //
                    qreal col_r=silce_colors[slice].x();
                    qreal col_g=silce_colors[slice].y();
                    qreal col_b=silce_colors[slice].z();
                    _active_visual_unit->_info._vertices.push_back( Vertex( cx,cy,0,1,           col_r,col_g,col_b,1) );
                    _active_visual_unit->_info._vertices.push_back( Vertex( x_here,y_here,0,1,   col_r,col_g,col_b,1) );
                    _active_visual_unit->_info._vertices.push_back( Vertex( x_next,y_next,0,1,   col_r,col_g,col_b,1) );
                    _active_visual_unit->_info._indices.push_back( _active_visual_unit->_info._index_count++ );
                    _active_visual_unit->_info._indices.push_back( _active_visual_unit->_info._index_count++ );
                    _active_visual_unit->_info._indices.push_back( _active_visual_unit->_info._index_count++ );
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

        //  Draw a black rim to differenciate between the slices and the true class rim.
        //
        {
            //
            qreal degrees_per_step = 360.0 / steps;

            //  Make the black rim 10% larger than the radius.
            //
            qreal r_rim = r +  r * 0.1;

            //
            current_degree=0;

            //
            for( int step=0; step<steps; step++ ){


                //  Rotate around the center by a radius.
                //  (This point.)
                //  Take our step and add in our current total degree so that we
                //      keep our progress around the circle.
                //
                qreal t=degrees_per_step*step;
                t = (t+current_degree) * toRadians;
                s = sin(t);     c = cos(t);
                qreal x_here=cx + (c*r_rim-s*r_rim);
                qreal y_here=cy + (s*r_rim+c*r_rim);

                //  Rotate around the center by a radius.
                //  (Next point.)
                //
                t=degrees_per_step*(step+1);
                t = (t+current_degree)*toRadians;
                s = sin(t);     c = cos(t);
                qreal x_next=cx + (c*r_rim-s*r_rim);
                qreal y_next=cy + (s*r_rim+c*r_rim);

                //  Create the triangle.
                //
                qreal col_r=0;
                qreal col_g=0;
                qreal col_b=0;
                _active_visual_unit->_info._vertices.push_back( Vertex( cx,cy,0,1,           col_r,col_g,col_b,1) );
                _active_visual_unit->_info._vertices.push_back( Vertex( x_here,y_here,0,1,   col_r,col_g,col_b,1) );
                _active_visual_unit->_info._vertices.push_back( Vertex( x_next,y_next,0,1,   col_r,col_g,col_b,1) );
                _active_visual_unit->_info._indices.push_back( _active_visual_unit->_info._index_count++ );
                _active_visual_unit->_info._indices.push_back( _active_visual_unit->_info._index_count++ );
                _active_visual_unit->_info._indices.push_back( _active_visual_unit->_info._index_count++ );

                //
                //current_degree + degrees_per_step;
            }
        }

        //  Draw the rim of the piechart as larger, single color circle, behind the other slices.
        //
        {
            //
            qreal degrees_per_step = 360.0 / steps;

            //  Make the true class rim 60% larger than the radius.
            //
            qreal r_rim = r +  r * 0.6;

            //
            current_degree=0;

            //
            for( int step=0; step<steps; step++ ){


                //  Rotate around the center by a radius.
                //  (This point.)
                //  Take our step and add in our current total degree so that we
                //      keep our progress around the circle.
                //
                qreal t=degrees_per_step*step;
                t = (t+current_degree) * toRadians;
                s = sin(t);     c = cos(t);
                qreal x_here=cx + (c*r_rim-s*r_rim);
                qreal y_here=cy + (s*r_rim+c*r_rim);

                //  Rotate around the center by a radius.
                //  (Next point.)
                //
                t=degrees_per_step*(step+1);
                t = (t+current_degree)*toRadians;
                s = sin(t);     c = cos(t);
                qreal x_next=cx + (c*r_rim-s*r_rim);
                qreal y_next=cy + (s*r_rim+c*r_rim);

                //  Create the triangle.
                //
                qreal col_r=true_color.x();
                qreal col_g=true_color.y();
                qreal col_b=true_color.z();
                _active_visual_unit->_info._vertices.push_back( Vertex( cx,cy,0,1,           col_r,col_g,col_b,1) );
                _active_visual_unit->_info._vertices.push_back( Vertex( x_here,y_here,0,1,   col_r,col_g,col_b,1) );
                _active_visual_unit->_info._vertices.push_back( Vertex( x_next,y_next,0,1,   col_r,col_g,col_b,1) );
                _active_visual_unit->_info._indices.push_back( _active_visual_unit->_info._index_count++ );
                _active_visual_unit->_info._indices.push_back( _active_visual_unit->_info._index_count++ );
                _active_visual_unit->_info._indices.push_back( _active_visual_unit->_info._index_count++ );

                //
                //current_degree += degrees_per_step;
            }
        }


    }

    //  Find the number of vertices in a single pie chart.
    //
    if( _active_visual_unit->_info._verts_in_single_chart == 0 ){
        _active_visual_unit->_info._verts_in_single_chart=_active_visual_unit->_info._vertices.count();
        helpers::debug_out( QString("...Vertices in single chart [count:%1]")
                            .arg(_active_visual_unit->_info._verts_in_single_chart) );
    }
}


void visual_unit_factory::push_fake_piechart(){

    //
    std::vector<double> percents;
    percents.push_back( 1 );

    //
    std::vector<QVector3D> colors;
    colors.push_back( QVector3D(1,1,1) );

    //
    push_piechart( -100, -100, percents, QVector3D(1,1,1), colors );
}

//++++++++++++++++++++++

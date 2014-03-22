#include "buffer_worker.h"

buffer_worker::buffer_worker( int index_length, int index_start, dataset_db* db  )
    :   _index_length(index_length), _finished(false), _db(db), _index_count(0), _index_start(index_start)
{
    helpers::debug_out( QString("buffer worker [length:%1]").arg(_index_length) );
}

buffer_worker::~buffer_worker(){}

void buffer_worker::process(){

    //  Get our list of colors.
    //
    std::vector<QVector3D> colors = _db->descriptor()->list_color();
    QVector3D true_color;

    //  Create the pie glyphs.
    //
    bool result=true;
    model_point point;
    for( int ii=0; ii<_index_length; ii++ ){

        //  Get the next point.
        //
        result = _db->get_point( ii+_index_start, &point, true );

        //  End if we didn't get a point.
        //
        if( !result )
            break;

        //  Find the true color.
        //
        true_color = _db->descriptor()->class_option_to_color( point._attribute_class );


        //  Create a piechart for the point.
        //
        create_pies( point._position.x(), point._position.y(), point._probability_values, true_color, colors, 0.015, 30 );
    }


    //  Done.
    //
    _finished=true;
    emit finished();
}

void buffer_worker::create_pies( qreal cx, qreal cy, std::vector<double> &slice_percents, QVector3D true_color, std::vector<QVector3D> &slice_colors, qreal radius, int steps ){

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
                    qreal col_r=slice_colors[slice].x();
                    qreal col_g=slice_colors[slice].y();
                    qreal col_b=slice_colors[slice].z();
                    _fragment_vertices.push_back( Vertex( cx,cy,0,1,           col_r,col_g,col_b,1) );
                    _fragment_vertices.push_back( Vertex( x_here,y_here,0,1,   col_r,col_g,col_b,1) );
                    _fragment_vertices.push_back( Vertex( x_next,y_next,0,1,   col_r,col_g,col_b,1) );
                    _fragment_indices.push_back( _index_count++ );
                    _fragment_indices.push_back( _index_count++ );
                    _fragment_indices.push_back( _index_count++ );
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
                _fragment_vertices.push_back( Vertex( cx,cy,0,1,           col_r,col_g,col_b,1) );
                _fragment_vertices.push_back( Vertex( x_here,y_here,0,1,   col_r,col_g,col_b,1) );
                _fragment_vertices.push_back( Vertex( x_next,y_next,0,1,   col_r,col_g,col_b,1) );
                _fragment_indices.push_back( _index_count++ );
                _fragment_indices.push_back( _index_count++ );
                _fragment_indices.push_back( _index_count++ );

                //
                //current_degree += degrees_per_step;
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
                _fragment_vertices.push_back( Vertex( cx,cy,0,1,           col_r,col_g,col_b,1) );
                _fragment_vertices.push_back( Vertex( x_here,y_here,0,1,   col_r,col_g,col_b,1) );
                _fragment_vertices.push_back( Vertex( x_next,y_next,0,1,   col_r,col_g,col_b,1) );
                _fragment_indices.push_back( _index_count++ );
                _fragment_indices.push_back( _index_count++ );
                _fragment_indices.push_back( _index_count++ );

                //
                //current_degree += degrees_per_step;
            }
        }


    }
}


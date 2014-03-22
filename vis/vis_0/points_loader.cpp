#include "points_loader.h"
#include "resampler.h"

//  Construct.
//
//++++++++++++++++++++++++++++++++++++
points_loader::points_loader( QString path_obsrv, QString path_points, QString path_model, QString path_train )
    :   _path_model( path_model ), _path_train( path_train ), _path_obsrv( path_obsrv ), _reader_obsrv( path_obsrv ), _reader_points( path_points ), _reader_model( path_model ), _reader_train( path_train )
{}
//++++++++++++++++++++++++++++++++++++


//  Run.
//
//++++++++++++++++++++++++++++++++++++
void points_loader::run(){

    //
    load_attributes_and_classes();

    //
    load_points();

    /*
    //  Resample.
    //
    QString path_request = find_request_path();
    QString path_response = find_response_path();
    resampler r( _path_model, _path_train, path_request, path_response );
    r.go( _path_obsrv, _temp_points );
    */

    //  Generate database.
    //

}

//  Get the points as a database object.
//
void points_loader::get_database(){

}

//++++++++++++++++++++++++++++++++++++

//  Error.
//
//++++++++++++++++++++++++++++++++++++
bool points_loader::check_badpath(){

    //
    return ( _reader_obsrv._bad_path || _reader_points._bad_path || _reader_model._bad_path || _reader_train._bad_path );
}
//++++++++++++++++++++++++++++++++++++


//
//++++++++++++++++++++++++++++++++++++
QString points_loader::find_request_path(){

    //
    QString s( _path_model );
    s.replace( ".model", ".request" );

    //
    return s;
}
QString points_loader::find_response_path(){

    //
    QString s( _path_model );
    s.replace( ".model", ".response" );

    //
    return s;
}
//++++++++++++++++++++++++++++++++++++

//  GET.
//
//++++++++++++++++++++++++++++++++++++
QStringList points_loader::attributes(){ return _temp_attributes; }
QStringList points_loader::classes(){  return _temp_attributes; }
//++++++++++++++++++++++++++++++++++++

//  Load.
//
//++++++++++++++++++++++++++++++++++++
void points_loader::load_attributes_and_classes(){

    //  This is what an .obsrv file looks like:
    //
    //  [0] Attribute_0, attb_1, ..., attb_n
    //  [1] attb_n_possible_value_0, attb_n_val_1, ...., attb_n_val_n
    //  [2] value_0, value_1, ...., attribute_n_possible_value
    //  [3] value_0, value_1, ...., attribute_n_possible_value
    //  [4] value_0, value_1, ...., attribute_n_possible_value
    //  [5] etc etc...
    //  FILE-END.
    //
    //  The first row are attribute types.
    //  The second row are classes. These are also possible types of the final attribute type in the first row.
    //  The remaining rows are numerical and string values for a point's classes, with the point's class at the end of the row.
    //

    //
    if( check_badpath() )
        return;

    //  The attributes are the first line of the .obsrv file.
    //
    _reader_obsrv.goto_next_line();
    helpers::debug_out( _reader_obsrv.line() );
    QStringList attributes = _reader_obsrv.line_tokens();

    //  The classes are the second line of the .obsrv file.
    //
    _reader_obsrv.goto_next_line();
    helpers::debug_out( _reader_obsrv.line() );
    QStringList classes = _reader_obsrv.line_tokens();

    //  Store.
    //
    for( int ii=0; ii<attributes.size(); ii++ )
        _temp_attributes.push_back( attributes.at(ii) );
    for( int ii=0; ii<classes.size(); ii++ )
        _temp_classes.push_back( classes.at(ii) );
}
void points_loader::load_points(){

    //
    if( check_badpath() )
        return;

    //  Read line by line of the obsrv and points files.
    //
    while( _reader_obsrv.goto_next_line() && _reader_points.goto_next_line() )
        create_point( _reader_obsrv.line_tokens(), _reader_points.line_tokens() );
    create_point( _reader_obsrv.line_tokens(), _reader_points.line_tokens() );


}
//++++++++++++++++++++++++++++++++++++


//  Points.
//
//++++++++++++++++++++++++++++++++++++
//
QList<model_point> points_loader::points(){ return _temp_points; }
void points_loader::create_point( QStringList obsrv_tokens, QStringList points_tokens ){


    //  Create the point.
    //
    model_point point;

    //  Get the point's class.
    //
    //  The database won't accept '-'.
    //
    {
        QString s = obsrv_tokens.back();
        s.replace( "-", "_" );
        point._attribute_class = s;
    }

    //  Get the point's class values.
    //
    //  The database won't accept '-'.
    //
    for( int ii=0; ii<obsrv_tokens.size() - 1; ii++ )
    {
        QString s = obsrv_tokens.at(ii);
        s.replace( "-", "_" );
        point._attribute_values.push_back( s );
    }

    //  Get the point's x,y coordinates.
    //
    QString x = points_tokens.front();
    QString y = points_tokens.back();
    point._position.setX( x.toFloat() );
    point._position.setY( y.toFloat() );

    //  Get the point's probability values.
    //

    //  Save.
    //
    _temp_points.push_back( point );
}

//++++++++++++++++++++++++++++++++++++

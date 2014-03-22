#include "resampler.h"
#include "csv_reader.h"

resampler::resampler(  QString model_path, QString training_path, QString request_path, QString response_path )
    :   _model_path( model_path ), _training_path( training_path ), _request_path( request_path ), _response_path( response_path )
{}

//
//++++++++++++++++++++++++++++++++++
void resampler::process_points( QList<model_point> *point_list )
{}
QList<model_point> resampler::processed_points(){ return _processed_point_list; }
//++++++++++++++++++++++++++++++++++



//
//++++++++++++++++++++++++++++++++++

void resampler::test_cmd(){

    //  Output our request file.
    //
    write_request( "../vis_0/data/adult.new_workclass_AM4.obsrv" );

    //  Run the Resampler Jar on the request.
    //
    QString base_path_java("../vis_0/java/");
    QString base_path_data("../vis_0/data/");
    QString path_model("adult.new_workclass_AM4.model");
    QString path_train("adult.new_workclass_AM4.train");
    QString path_request("adult.new_workclass_AM4.request");
    QString path_response("adult.new_workclass_AM4.response");
    QString path = QString("java -jar %1%3 %2%4 %2%5 %2%6 %2%7")
            .arg( base_path_java )
            .arg( base_path_data )
            .arg("resampler.jar")
            .arg(path_model)
            .arg(path_train)
            .arg(path_request)
            .arg(path_response);
    helpers::debug_out( QString( "test_cmd: %1" ).arg(path) );
    char* msg = helpers::qstring_to_char_array( path );
    system( msg );

    //  Working example.
    //
    //system( "java -jar ../vis_0/java/resampler.jar ../vis_0/data/adult.new_workclass_AM4.model ../vis_0/data/adult.new_workclass_AM4.train ../vis_0/data/adult.new_workclass_AM4.request ../vis_0/data/adult.new_workclass_AM4.response" );

    //  Read the request.
    //
    //read_response( );
}

//++++++++++++++++++++++++++++++++++


//
//
//++++++++++++++++++++++++++++++++++
QString resampler::create_request( QString path_observe )
{

    //  Load the observe file.
    //
    csv_reader obsrv_reader( path_observe );

    //  Create our contents string.
    //
    QString request_contents="";

    //  Add our dataset locations.
    //
    request_contents.append( _model_path + "\n" );
    request_contents.append( _training_path + "\n" );
    request_contents.append( _response_path + "\n" );

    //  Grab all lines except for the first two.
    //
    obsrv_reader.goto_next_line();
    obsrv_reader.goto_next_line();
    while( obsrv_reader.goto_next_line() )
        request_contents.append( obsrv_reader.line() + "\n" );
    request_contents.append( obsrv_reader.line() + "\n" );

    //
    return request_contents;

}
void resampler::write_request( QString path_observe )
{

    //  Get file contents.
    //
    QString contents = create_request( path_observe );


    //  Write out.
    //
    QFile file(_request_path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << contents;

}
void resampler::read_response( QList<model_point> &point_list )
{

    //  Open the file.
    //
    QFile file( _response_path );
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    //  Read each line.
    //
    int index=0;
    while(!in.atEnd()) {
        QString line = in.readLine();

        //  We shouldn't get more lines than points...
        //
        assert( index < point_list.size() );

        //  Collect the completed point.
        //
        _processed_point_list.push_back( response_line_to_point( line, index, point_list ) );
        index++;
    }
}
model_point resampler::response_line_to_point( QString line, int index, QList<model_point> &point_list ){

    //  Get the point. (lol)
    //
    model_point point = point_list.at(index);

    //  Fill out it's probabilities.
    //
    QStringList probabilities = line.split(',');
    for( int ii=0; ii<probabilities.size(); ii++ )
        point._probability_values.push_back( probabilities.at(ii).toDouble() );

    //  Return it.
    //
    return point;

}
//++++++++++++++++++++++++++++++++++




//++++++++++++++++++++++++++++++++++
void resampler::run_command()
{
    //  Run the Resampler Jar on the request.
    //

    //  Prepare.
    QString path_request( _request_path );
    QString path = QString("java -jar %1 %2")
            .arg("../vis_0/java/resampler.jar")
            .arg(path_request);
    helpers::debug_out( QString( "run_command: %1" ).arg(path) );

    //  Go!
    //  This will run an operation and then wait for it to complete.
    //  We'll also record the time the command takes to complete...
    //
    unsigned int stamp_then = helpers::timestamp();
    system( path.toStdString().c_str() );
    unsigned int ms_ = helpers::time_elapsed( stamp_then );
    helpers::debug_out( QString("qt resampler time [%1 seconds]\n\n").arg( helpers::milliseconds_to_seconds(ms_)) );
}
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void resampler::apply_points_mapping( QList<model_point> &point_list, QString mapping_path ){


    //  Open the file.
    //
    QFile file( mapping_path );
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    //  Read each line.
    //
    int index=0;
    while(!in.atEnd()) {
        QString line = in.readLine();

        //  We shouldn't get more lines than points...
        //
        assert( index < point_list.size() );

        //  Collect the completed point.
        //
        _processed_point_list.push_back( response_line_to_point( line, index, point_list ) );
        index++;
    }
}
QVector2D resampler::mapping_line_to_coordinates( QString line ){

    //  Find the mapping coordinates.
    //
    QStringList coordinates = line.split(',');

    //  Return it.
    //
    return QVector2D( coordinates.at(0).toFloat(), coordinates.at(1).toFloat() );
}

//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void resampler::go(  QString obsrv_path, QList<model_point> &point_list ){

    //  Go.
    //
    write_request( obsrv_path );
    run_command();
    read_response( point_list );

}
//++++++++++++++++++++++++++++++++++

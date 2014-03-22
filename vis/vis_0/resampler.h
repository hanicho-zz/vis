#ifndef RESAMPLER_H
#define RESAMPLER_H

//
#include "common.h"
#include "model_point.h"

//
class resampler
{
public:
    resampler( QString model_path, QString training_path, QString request_path, QString response_path );

    //
    void process_points( QList<model_point> *point_list );
    QList<model_point> processed_points();

    //
    void go(  QString obsrv_path, QList<model_point> &points_loaderpoint_list );

    void test_cmd();

private:

    //  The request file is the observe file without the top 2 lines
    //  about attributes and classes.
    //
    QString create_request( QString path_observe );
    void write_request( QString contents );
    void read_response(  QList<model_point> &point_list );

    //  Apply points coordinate mappings.
    //  For instance, make a dataset use a PCA mapping...
    //
    void apply_points_mapping( QList<model_point> &point_list, QString mapping_path );
    QVector2D mapping_line_to_coordinates( QString line );

    //  Use a line from the response file to populate our point's probability values.
    //
    model_point response_line_to_point( QString line, int index, QList<model_point> &point_list );

    //
    void run_command();

    //
    QList<model_point> _processed_point_list;

    //
    QString _model_path, _training_path, _request_path, _response_path;
};

#endif // RESAMPLER_H

#ifndef POINTS_LOADER_H
#define POINTS_LOADER_H

//
#include "csv_reader.h"
#include "model_point.h"

//
class points_loader
{
public:
    points_loader( QString path_obsrv, QString path_points, QString path_model, QString path_train );

    //
    void run();
    void get_database();

    //
    QList<model_point> points();

    //
    QStringList attributes();
    QStringList classes();

    //
    QString _path_model, _path_train, _path_obsrv;

    //
    csv_reader _reader_obsrv, _reader_points, _reader_model, _reader_train;


private:

    //
    bool check_badpath();

    //
    QString find_request_path();
    QString find_response_path();

    //
    void load_attributes_and_classes();
    void load_points();

    //
    void create_point( QStringList obsrv_tokens, QStringList points_tokens );

    //
    QStringList _temp_attributes;
    QStringList _temp_classes;
    QList<model_point> _temp_points;
};

#endif // POINTS_LOADER_H

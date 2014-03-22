#ifndef POINTS_LOADER_H
#define POINTS_LOADER_H

//
#include "csv_reader.h"

//
class points_loader
{
public:
    points_loader( QString path_obsrv, QString path_points, QString path_model, QString path_train );

    //
    csv_reader _reader_obsrv, _reader_points, _reader_model, _reader_train;
};

#endif // POINTS_LOADER_H

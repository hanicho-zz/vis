#include "points_loader.h"

points_loader::points_loader( QString path_obsrv, QString path_points, QString path_model, QString path_train )
    :   _reader_obsrv( path_obsrv ), _reader_points( path_points ), _reader_model( path_model ), _reader_train( path_train )
{}

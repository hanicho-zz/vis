#ifndef TOUR_H
#define TOUR_H

//
#include "common.h"
#include "question.h"

//
class dataset_db;

//
class tour
{
public:
    tour();
    tour( tour *copy );

    //  References to datasets located in the libary.
    //
    std::vector< dataset_db* > _datasets;
};

#endif // TOUR_H


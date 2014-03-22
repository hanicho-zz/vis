#ifndef TOUR_FACTORY_H
#define TOUR_FACTORY_H

//
#include "common.h"
#include "interrogation.h"
#include "library.h"
#include "dataset_db.h"
#include "tour.h"

//
class tour_factory
{
public:
    tour_factory( library* );
    ~tour_factory();

    //
    void load_file( QString path );

    //
    tour* get_tour();

private:

    //
    void push_dataset( QString path_data, QString path_info );

    //
    library* _ref_library;

    //
    tour *_cached_tour;

};

#endif // TOUR_FACTORY_H


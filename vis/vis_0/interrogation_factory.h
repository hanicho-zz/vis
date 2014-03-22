#ifndef INTERROGATION_FACTORY_H
#define INTERROGATION_FACTORY_H

//
#include "common.h"
#include "library.h"
#include "dataset_db.h"

//
class interrogation;

//  Creates interrogation objects.
//
class interrogation_factory
{
public:
    interrogation_factory( library* );
    ~interrogation_factory();

    //
    void load_file(QString path);

    //
    interrogation* get_interrogation();

private:

    //
    void push_dataset( QString path_data, QString path_info );
    void push_question( QString msg );
    void push_option( QString msg );

    //
    void create_interrogation();

    //
    void start_question();
    void submit_question();

    //
    library* _ref_library;

    //  The current dataset we have loaded.
    //
    dataset_db* _cached_dataset;

    //  The current interrogation we're building.
    //
    interrogation *_cached_interrogation;

    //  The current question we're building.
    //
    QString _cached_question;
    QStringList _cached_options;
};

#endif // INTERROGATION_FACTORY_H

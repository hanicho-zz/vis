#ifndef TEST_BED_H
#define TEST_BED_H

//
#include <QDebug>

//
class dataset_db;
class library;

//
class test_bed
{
public:
    test_bed();

    void go( library* ref_lib );
private:

    //
    void test_csv_reader();

    //
    void test_points_loader();

    //
    void test_resampler();

    //
    void test_database( library *ref_lib );
    void check_database_points( dataset_db& db );

    //
    bool test_interogation_factory( library* ref_lib );
    bool test_interrogation( library* ref_lib );
};

#endif // TEST_BED_H

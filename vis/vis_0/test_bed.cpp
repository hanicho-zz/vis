#include "test_bed.h"


//
#include "csv_reader.h"
#include "points_loader.h"
#include "resampler.h"
#include "dataset_db.h"
#include "library.h"
#include "interrogation.h"
#include "interrogation_factory.h"

//
test_bed::test_bed()
{}

//++++++++++++++++++++++
void test_bed::go( library* ref_lib )
{

    //test_csv_reader();
    //test_points_loader();
    //test_resampler();
    //test_database( ref_lib );
    //test_interogation_factory( ref_lib );
    //test_interrogation( ref_lib );
}
//++++++++++++++++++++++


//++++++++++++++++++++++
void test_bed::test_csv_reader()
{


    csv_reader adult("../vis_0/data/adult.new_workclass_AM4.obsrv");
    while( adult.goto_next_line() )
        qDebug() << adult.line();
    qDebug() << adult.line();

}
//++++++++++++++++++++++


//++++++++++++++++++++++
void test_bed::test_points_loader(){

    //
    points_loader loader(
                "../vis_0/data/adult.new_workclass_AM4.obsrv",
                "../vis_0/data/adult.new_workclass_AM4.obsrv",
                "../vis_0/data/adult.new_workclass_AM4.obsrv",
                "../vis_0/data/adult.new_workclass_AM4.obsrv");
    loader.run();
}


void test_bed::test_resampler(){

    //
    points_loader loader(
                "../vis_0/data/adult.new_workclass_AM4.obsrv",
                "../vis_0/data/adult.new_workclass_AM4.pca",
                "../vis_0/data/adult.new_workclass_AM4.model",
                "../vis_0/data/adult.new_workclass_AM4.train");
    loader.run();

    //
    QList<model_point> points = loader.points();

    //
    resampler r( "../vis_0/data/adult.new_workclass_AM4.model", "../vis_0/data/adult.new_workclass_AM4.train", "../vis_0/data/adult.new_workclass_AM4.request", "../vis_0/data/adult.new_workclass_AM4.response" );
    r.go( "../vis_0/data/adult.new_workclass_AM4.obsrv", points );

    helpers::debug_out("stopper...");
}
//++++++++++++++++++++++

//++++++++++++++++++++++
void test_bed::test_database( library *ref_lib ){

    //
    QString path_obsrv("../vis_0/data/adult.new_workclass_AM4.obsrv");
    QString path_color("../vis_0/data/adult.new_workclass_AM4.colors");
    QString path_points("../vis_0/data/adult.new_workclass_AM4.pca");
    QString path_model("../vis_0/data/adult.new_workclass_AM4.model");
    QString path_train("../vis_0/data/adult.new_workclass_AM4.train");
    QString path_request("../vis_0/data/adult.new_workclass_AM4.request");
    QString path_response("../vis_0/data/adult.new_workclass_AM4.response");
    bool replace = false;

    //
    if( replace ){

        //  Load points.
        //
        points_loader loader(
                    path_obsrv,
                    path_points,
                    path_model,
                    path_train);
        loader.run();

        //  Resample points.
        //
        QList<model_point> raw_points = loader.points();
        resampler r( path_model, path_train, path_request, path_response );
        r.go( path_obsrv, raw_points );

        //  Create the dataset database.
        //
        QList<model_point> processed_points = r.processed_points();
       // dataset_db *dsdb = new dataset_db( path_obsrv, path_color, &processed_points, true );

        //  Add the database to the library.
        //
       // if( ref_lib ){
       //     ref_lib->_list_dataset_databases.push_back( dsdb );
        //}
    }

    //
    else{

        //  Create the dataset database.
        //
        //dataset_db *dsdb = new dataset_db( path_obsrv, path_color, 0, false );

        //  Add the database to the library.
        //
        //if( ref_lib )
            //ref_lib->set_active_database( dsdb );

    }
}
void test_bed::check_database_points( dataset_db& db ){

    //
    {
        model_point point;
        db.get_point( 0, &point, false );
    }
    {
        model_point point;
        db.get_point( 1, &point, false );
    }
    {
        model_point point;
        db.get_point( 2, &point, false );
    }
    {
        model_point point;
        db.get_point( 0, &point, false );
    }
}
//++++++++++++++++++++++


//++++++++++++++++++++++
bool test_bed::test_interogation_factory( library* ref_lib ){

    //
    interrogation_factory fac( ref_lib );
    fac.load_file( "../vis_0/data/test_0.int" );

    //
    return true;
}
bool test_bed::test_interrogation( library* ref_lib ){

    //
    interrogation_factory fac( ref_lib );
    fac.load_file( "../vis_0/data/test_0.int" );


    //
    return true;
}

//++++++++++++++++++++++

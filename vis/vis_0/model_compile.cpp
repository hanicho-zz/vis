#include "model_compile.h"

//
#include "library.h"
#include "csv_reader.h"
#include "points_loader.h"
#include "resampler.h"
#include "dataset_db.h"

//++++++++++++++++++++++++++++++++++++
model_compile::model_compile( library *lib )
    :   _ref_library( lib )
{}
//++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++
bool model_compile::compile( QString base, QString *err ){

    //  Note a few things happening here.
    //
    //  [1] We build the file endings from the base that is provided.
    //  [2] We ALWAYS rebuild the dataset here.

    //  Paths.
    //
    QString path_obsrv = QString("%1.%2").arg(base).arg("obsrv");
    QString path_color = QString("%1.%2").arg(base).arg("colors");
    QString path_points = QString("%1.%2").arg(base).arg("pca");
    QString path_model = QString("%1.%2").arg(base).arg("model");
    QString path_train = QString("%1.%2").arg(base).arg("train");
    QString path_request = QString("%1.%2").arg(base).arg("request");
    QString path_response = QString("%1.%2").arg(base).arg("response");
    QString path_info = QString("../vis_0/data/adult.info");

    //  If any of the files doesn't exist, return!
    {
        //
        bool result=true;

        //
        if( !QFile( path_obsrv).exists() ){
            err->append("obsrv file not found...\n");
            result=false;
        }
        if( !QFile( path_color).exists() ){
            err->append("colors file not found...\n");
            result=false;
        }
        if( !QFile( path_points).exists() ){
            err->append("points file not found...\n");
            result=false;
        }
        if( !QFile( path_model).exists() ){
            err->append("model file not found...\n");
            result=false;
        }
        if( !QFile( path_train).exists() ){
            err->append("train file not found...\n");
            result=false;
        }
        if( !QFile( path_info).exists() ){
            err->append("info file not found...\n");
            result=false;
        }

        //
        if( !result )
            return false;
    }

    //  Time begin.
    //
    unsigned int t0 = helpers::timestamp();

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
    dataset_db *dsdb = new dataset_db( _ref_library, path_obsrv, path_color, path_info, &processed_points, true );

    //  Add the database to the library.
    //
    if( _ref_library )
        _ref_library->add_database( dsdb );

    //  Time elapsed.
    //
    float seconds = helpers::milliseconds_to_seconds( helpers::time_elapsed(t0) );
    helpers::debug_out( QString("Compiling dataset [%1] took [%2 seconds]...").arg(base).arg(seconds) );

    //
    return true;
}
//++++++++++++++++++++++++++++++++++++

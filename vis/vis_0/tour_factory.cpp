#include "tour_factory.h"

//
#include "csv_reader.h"
#include "tour.h"

//+++++++++++++++++++++++++
tour_factory::tour_factory( library* lib )
    :   _ref_library( lib ), _cached_tour(0)
{}
tour_factory::~tour_factory()
{}
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
tour* tour_factory::get_tour(){ return _cached_tour; }
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
void tour_factory::load_file( QString path ){

    //
    _cached_tour = new tour();

    //
    csv_reader reader( path );

    //  Parse our file content.
    //
    QString("Tour...");
    while( reader.goto_next_line() ){

        //
        QStringList tokens = reader.line_tokens();

        //  Comments.
        //
        if( tokens.at(0).compare("--") == 0 )
            return;

        //  Datasets.
        //
        if( tokens.at(0).compare("#d") == 0 ){

            //
            QString path_data = tokens.at(1);
            reader.goto_next_line();
            QString path_info = tokens.at(1);

            //
            push_dataset( path_data, path_info );
        }
    }
}

//+++++++++++++++++++++++++



//+++++++++++++++++++++++++
void tour_factory::push_dataset( QString path_data, QString path_info ){

    //
    helpers::debug_out( QString("...dataset: [%1]").arg(path_data) );

    //  Note a few things happening here.
    //
    //  [1] We build the file endings from the base that is provided.
    //  [2] We never rebuild the dataset here. That can only be done in the compiling tool.
    //
    QString path_obsrv = QString("%1.%2").arg(path_data).arg("obsrv");
    QString path_color = QString("%1.%2").arg(path_data).arg("colors");

    //  Create the dataset database.
    //
    dataset_db *dsdb = new dataset_db( _ref_library, path_obsrv, path_color, path_info, 0, false );

    //  Add the database to the library.
    //
    if( _ref_library )
        _ref_library->add_database( dsdb );

    //
    _cached_tour->_datasets.push_back( dsdb );

}
//+++++++++++++++++++++++++

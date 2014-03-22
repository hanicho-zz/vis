#include "interrogation_factory.h"

//
#include "csv_reader.h"
#include "question.h"
#include "interrogation.h"


//+++++++++++++++++++++++++
interrogation_factory::interrogation_factory( library* lib )
    :_cached_interrogation( 0 ), _ref_library( lib ), _cached_dataset( 0 )
{}

interrogation_factory::~interrogation_factory(){

    //  The owner of the interrogation becomes responsible for deleting it.
    //  Doing so here causes issues.
    //
}
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
interrogation* interrogation_factory::get_interrogation(){ return _cached_interrogation; }
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
void interrogation_factory::load_file( QString path ){

    //
    csv_reader reader( path );

    //
    create_interrogation();

    //
    QString path_info="";

    //  Parse our file content.
    //
    while( reader.goto_next_line() ){

        //
        QStringList tokens = reader.line_tokens();

        //  Comments.
        //
        if( tokens.at(0).compare("--") == 0 )
            return;

        //  Info.
        //
        if( tokens.at(0).compare("#i") == 0 ){

            path_info = tokens.at(1);
        }

        //  Datasets.
        //
        if( tokens.at(0).compare("#d") == 0 ){

            //
            submit_question();

            //
            QString path_data = tokens.at(1);

            //
            push_dataset( path_data, path_info );
        }

        //  Questions.
        //
        else if( tokens.at(0).compare("#q") == 0 ){
            submit_question();
            start_question();
            push_question( tokens.at(1) );
        }

        //  Question options.
        //
        else if( tokens.at(0).compare("#qo") == 0 )
            push_option( tokens.at(1) );

    }

    //  Submit any outstanding questions.
    //
    submit_question();

    //  Let's see what we loaded.
    //
    QString("Interrgation...");
    for( int ii=0; ii<_cached_interrogation->_pairs.size(); ii++ ){

        //
        dataset_questions_pair* pair = &_cached_interrogation->_pairs.at(ii);

        //
        QString dataset = pair->_dataset->name();
        std::vector< question > *questions = &pair->_questions;

        //  The dataset.
        //
        helpers::debug_out( QString("dataset [%1]").arg(dataset) );

        //  Questions / Options.
        //
        for( int ii=0; ii<questions->size(); ii++ ){

            //  The question.
            //
            question* tmp = &questions->at(ii);
            helpers::debug_out( QString("Q: %1").arg(tmp->get_question()) );

            //  The options.
            //
            for( int jj=0; jj<tmp->get_options().size(); jj++ )
                helpers::debug_out( QString("\t%1").arg( tmp->get_options().at(jj) ) );
        }
    }
}
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
void interrogation_factory::create_interrogation(){

    //
    _cached_interrogation = new interrogation();
}
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
void interrogation_factory::start_question(){

    //
    _cached_question.clear();

    //
    _cached_options.clear();
}
void interrogation_factory::submit_question()
{

    //  With no question options we can't have a question.
    //
    if( _cached_options.empty() || !_cached_dataset )
        return;

    //  Add the question to our interrogation.
    //
    _cached_interrogation->push_question( _cached_dataset, question( _cached_question, _cached_options ) );

    //
    _cached_options.clear();
}
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
void interrogation_factory::push_dataset( QString path_data, QString path_info ){

    //  Note a few things happening here.
    //
    //  [1] We build the file endings from the base that is provided.
    //  [2] We never rebuild the dataset here. That can only be done in the compiling tool.
    //
    QString path_no_end = path_data.left( path_data.length() - 3 );
    QString path_obsrv = QString("%1.%2").arg(path_no_end).arg("obsrv");
    QString path_color = QString("%1.%2").arg(path_no_end).arg("colors");

    //  Create the dataset database.
    //
    dataset_db *dsdb = new dataset_db( _ref_library, path_obsrv, path_color, path_info, 0, false );

    //  Add the database to the library.
    //
    if( _ref_library )
        _ref_library->add_database( dsdb );

    //  Cache it.
    //
    _cached_dataset = dsdb;
    dataset_questions_pair pair;
    pair._dataset=dsdb;
    _cached_interrogation->_pairs.push_back( pair );

}
void interrogation_factory::push_question( QString msg ){

    //
    _cached_question.clear();

    //
    _cached_question.append(msg);
}
void interrogation_factory::push_option( QString msg ){ _cached_options.push_back( msg ); }
//+++++++++++++++++++++++++

#include "model_player.h"

//
#include "library.h"
#include "interrogation.h"
#include "tour.h"
#include "dataset_db.h"
#include "question.h"

//++++++++++++++++++++++++++++++++++++
model_player::model_player( library* lib )
    :   _playing(false), _ref_library(lib), _current_dataset(0), _current_question(0),
      _interrogation(0), _tour(0), _current_pair(0), _done(false)
{

    //
    _completion = new question( "Finished!", QStringList() );
}
model_player::~model_player(){

    //
    if( _interrogation )
        delete _interrogation;
    _interrogation=0;

    //
    if( _tour )
        delete _tour;
    _tour=0;

    //
    delete _completion;
}

//++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++
void model_player::play_interrogation( interrogation *info ){

    //
    if( _interrogation )
        delete _interrogation;

    //
    _interrogation = info;
    _interrogation->start();

    //
    _mode = e_interrogate;

    //
    _playing=true;

}
void model_player::play_tour( tour *info ){

    //
    if( _tour )
        delete _tour;

    //
    _tour = info;

    //
    _mode = e_tour;

    //
    _playing=true;
}
//++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++
void model_player::step(){

    //
    if( !_playing )
        return;

    //
    if( _mode == e_interrogate )
        step_interrogation();
    else
        step_tour();
}
void model_player::step_interrogation(){

    //  If we have no current dataset, get the next pair.
    //
    if( !_current_dataset ){
        _current_pair = _interrogation->pop_pair();

        //  If the pair is null, we're done.
        //
        if( !_current_pair ){
            present_complete();
            return;
        }

        //  Let's get the dataset.
        //
        _current_dataset = _current_pair->_dataset;
    }

    //  Get the next question.
    //

    //  If we are out of questions we should step to the next dataset.
    //
    _current_question = _current_pair->pop_question();
    if( !_current_question ){
        _current_dataset=0;
        step_interrogation();
        return;
    }

    /*
    //  If we're out of steps, show completion and return.
    //
    if( !check_steps() ){

        //
        present_complete();

        //
        return;
    }

    //
    if( _mode != e_interrogate )
        return;

    //
    int count=0;
    for( int ii=0; ii< _interrogation->_pairs.size(); ii++ ){

        //
        dataset_questions_pair *pair = &_interrogation->_pairs.at(ii);

        //
        QString name = pair->_dataset->name();


        for( int jj=0; jj< pair->_questions.size(); jj++ ){
            if( count == _progress ){

                //  This is our question.
                //
                _current_question = &pair->_questions.at(jj);

                //  This is our dataset.
                //
                _current_dataset = pair->_dataset;

                //
                return;
            }
            count++;
        }
    }
    */
}
void model_player::step_tour(){

    //
    if( _mode != e_tour )
        return;
}
//++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++
void model_player::present_complete(){

    //
    _current_question=_completion;

    //
    _done=true;
}
//++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++
dataset_db* model_player::get_dataset(){ return _current_dataset; }
question* model_player::get_question(){ return _current_question; }
//++++++++++++++++++++++++++++++++++++

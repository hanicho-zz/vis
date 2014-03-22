#include "interrogation.h"
#include "dataset_db.h"

//+++++++++++++++++++++++++
interrogation::interrogation()
    : _progress(0)
{}
interrogation::interrogation( interrogation* copy )
    :   _pairs( copy->_pairs ), _progress(0)
{}
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
void interrogation::start(){

    //
    for( int ii=0; ii<_pairs.size(); ii++ )
        _pairs.at(ii).start();
}

//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
void interrogation::push_question( dataset_db* dataset, question q ){

    //  Do we have this dataset already?
    //
    int found=-1;
    for(int ii=0; ii<_pairs.size(); ii++)
        if( dataset->name().compare( _pairs.at(ii)._dataset->name() ) == 0 )
            found = ii;

    //  If we already have a pair for this dataset, add the question to it.
    //
    if( found > -1 )
        _pairs.at(found)._questions.push_back( q );

    //  Else, start a new pair.
    //
    else{
        dataset_questions_pair pair;
        pair._dataset=dataset;
        pair._questions.push_back(q);
        _pairs.push_back(pair);
    }
}
//+++++++++++++++++++++++++
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
dataset_questions_pair* interrogation::pop_pair(){

    //  Let's return a pair and make note of the progress.
    //  Return null if we don't have any pairs left.
    //

    //
    if( _progress >= _pairs.size() )
        return 0;

    //
    return &_pairs.at(_progress++);
}
//+++++++++++++++++++++++++

#ifndef INTERROGATION_H
#define INTERROGATION_H

//
#include "common.h"
#include "question.h"

//
class dataset_db;

//
struct dataset_questions_pair{

    //
    dataset_db* _dataset;

    //
    std::vector<question> _questions;

    //
    int _progress;

    //
    void start(){ _progress=0; }

    //
    question* pop_question(){

        //
        if( _progress >= _questions.size() )
            return 0;

        //
        return &_questions.at( _progress++ );
    }
};

//  This object encapsulates everything we need to display a
//  series of datasets, and ask questions as we do so.
//
class interrogation
{
public:
    interrogation();
    interrogation( interrogation* copy );

    //
    dataset_questions_pair* pop_pair();

    //
    void start();

    //
    void push_question( dataset_db* dataset, question q );

    //  Questions to ask at each dataset we display.
    //  Each element here should be displayed upon progressing
    //  the interrogation a step.
    //

    //  An ordered list of our datasets/questions.
    //
    std::vector<dataset_questions_pair> _pairs;

    int _progress;
};

#endif // INTERROGATION_H

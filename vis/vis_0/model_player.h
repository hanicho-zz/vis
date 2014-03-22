#ifndef MODEL_PLAYER_H
#define MODEL_PLAYER_H

//
class library;
class tour;
class dataset_db;
class question;

//
#include "interrogation.h"


//
enum play_mode{
    e_interrogate,
    e_tour
};

//
class model_player
{
public:
    model_player( library* lib );
    ~model_player();

    //
    void play_interrogation( interrogation *info );
    void play_tour( tour *info );

    //
    dataset_db* get_dataset();
    question* get_question();

    //
    void step();

    //
    bool _done;

private:

    //
    void step_interrogation();
    void step_tour();

    //
    void present_complete();

    //
    library *_ref_library;

    //
    enum play_mode _mode;

    //
    interrogation *_interrogation;
    tour *_tour;

    //
    dataset_db *_current_dataset;
    question* _current_question;
    dataset_questions_pair *_current_pair;

    //
    bool _playing;

    //  We can show this when we are finished with questions.
    //
    question* _completion;

};

#endif // MODEL_PLAYER_H

#include "view_player.h"
#include "question.h"
#include "library.h"

//+++++++++++++++++++++++++
view_player::view_player(library *lib, QWidget *parent) :
    QWidget(parent), _ref_library(lib), _ref_model_player(0)
{

    //
    init_view();
}
//+++++++++++++++++++++++++


//+++++++++++++++++++++++++
void view_player::init_view(){

    //
    _grid = new QGridLayout;
    setLayout( _grid );

    //  Size/Position.
    //
    int total_width=4;
    int text_height=4;
    int question_height = 2;
    int button_height=1;

    //  Create the first hbox.
    //
    {

        //  Make.
        //
        QHBoxLayout *box = new QHBoxLayout;

        //  Create the text browser.
        //
        _text_browser = new QTextBrowser();
        box->addWidget( _text_browser );

        //  Store.
        //
        _list_hbox.push_back( box );

        //
        _grid->addLayout( box, 0,0, text_height,total_width );
    }

    //  We'll have a ton of buttons that aren't active.
    //  That way we can on/off them as we need to support more/less options.
    //
    for( int ii=1; ii<10; ii++ ){

        //  Make.
        //
        QHBoxLayout *box = new QHBoxLayout;

        //  Add a checkbox.
        //
        QCheckBox* check = new QCheckBox;
        _list_check.push_back( check );
        box->addWidget( check );

        //  Add a label
        //
        QLabel* label = new QLabel("option-option-option-option-option");
        _list_label.push_back( label );
        box->addWidget( label );

        //  Store.
        //
        _list_hbox.push_back( box );

        //  Add to the grid.
        //
        _grid->addLayout( box, (text_height*ii),0, question_height,total_width );
    }

    //  Add buttons for progression.
    //
    {

        //  Make.
        //
        QHBoxLayout *box = new QHBoxLayout;

        //
        QPushButton* btn_forward = new QPushButton("Next");
        connect( btn_forward, SIGNAL(clicked()), this, SLOT(progress_next()) );
        box->addWidget( btn_forward );

        //  Store.
        //
        _list_hbox.push_back( box );

        //
        _grid->addLayout( box, (text_height*_list_hbox.size()),0, button_height,total_width );
    }
    hide_all_options();
    //
    _text_browser->setText("This is the player. Questions durring the interrogation will go right here. ");
}

void view_player::hide_all_options(){

    //
    QLabel *label=0;
    QCheckBox *check=0;
    for( int ii=0; ii<_list_label.size(); ii++ ){

        //
        label=_list_label.at(ii);
        check=_list_check.at(ii);

        //
        label->hide();
        check->hide();
    }
}
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
void view_player::progress_next(){

    //
    if( !_ref_model_player || _ref_model_player->_done )
        return;

    //
    helpers::debug_out("player next...");

    //
    _ref_model_player->step();

    //  Apply the question and options.
    //
    question* q = _ref_model_player->get_question();
    if( q )
        set_question( q );

    //  Apply the dataset.
    //
    _ref_library->set_active_database( _ref_model_player->get_dataset() );
}
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
void view_player::run_model_interrogation( model_player* model ){

    //
    _ref_model_player=model;

    //
    progress_next();
}
void view_player::run_model_tour( model_player* model ){

    //
    _ref_model_player=model;

    //
    progress_next();
}
//+++++++++++++++++++++++++

//+++++++++++++++++++++++++
void view_player::set_question(question *q){

    //  Set the main text.
    //
    _text_browser->setText( q->get_question() );

    //
    hide_all_options();

    //  Set the options.
    //
    for( int ii=0; ii<q->get_options().size(); ii++ ){

        //
        QLabel *label = _list_label.at(ii);
        label->setText( q->get_options().at(ii) );
        label->show();

        //
        QCheckBox *check = _list_check.at(ii);
        check->show();
    }
}
//+++++++++++++++++++++++++

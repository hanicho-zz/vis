#include "question.h"

//+++++++++++++++++++++++++

question::question( QString the_question, QStringList options )
    :   _question( the_question ), _options( options )
{}
question::question( question* copy ){

    //
    _question = QString( copy->_question );

    //
    _options = QStringList( copy->_options );
}

//+++++++++++++++++++++++++


//+++++++++++++++++++++++++
QString question::get_question(){ return _question; }
QStringList question::get_options(){ return _options; }
//+++++++++++++++++++++++++



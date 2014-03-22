#ifndef QUESTION_H
#define QUESTION_H

//
#include "common.h"

//  An immutable object holding question info.
//
class question
{
public:
    question( QString the_question, QStringList options );
    question( question* copy );

    //
    QString get_question();
    QStringList get_options();


private:

    //
    QString _question;
    QStringList _options;
};

#endif // QUESTION_H

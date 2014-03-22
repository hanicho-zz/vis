#ifndef HELPERS_H
#define HELPERS_H


//
#include "common_includes.h"

//
namespace helpers{

    //  Output:
    //
    //++++++++++++++++++
    static void debug_out( QString msg ){

        //
        qDebug() << msg;
    }

    //
    static void debug_error( QString msg, QString who, QString what ){

        //
        qDebug() << QString("ERROR[%1]: %2 [%3]")
                    .arg(who)
                    .arg(msg)
                    .arg(what);
    }
    //+++++++++++++++++++

    //  GL.
    //
    //++++++++++++++++
    static void check_error_gl( int location){

        //  Error output.
        //
        GLenum ErrorCheckValue = glGetError();
        if (ErrorCheckValue != GL_NO_ERROR)
        {
            qDebug() << QString( "ERROR [location: %1]: [error value: %2]\n" )
                        .arg(location)
                        .arg( ErrorCheckValue );
            //
            //exit(-1);
        }
    }
    //++++++++++++++++

    //  String.
    //
    //++++++++++++++++
    static char* qstring_to_char_array( QString s ){

        //
        QByteArray ba = s.toLocal8Bit();
        return ba.data();
    }

    //++++++++++++++++


    //  Time.
    //
    //++++++++++++++++

    //  Get the current timestamp in milliseconds.
    //
    static unsigned int timestamp(){ return QDateTime::currentMSecsSinceEpoch(); }

    //  Get the elapsed time since a previous time stamp.
    //
    static unsigned int time_elapsed( unsigned int stamp_then ){ return QDateTime::currentMSecsSinceEpoch() - stamp_then; }

    static float milliseconds_to_seconds( unsigned int ms ){ return static_cast<float>(ms) / 1000.0f; }
    //++++++++++++++++

}

#endif // HELPERS_H

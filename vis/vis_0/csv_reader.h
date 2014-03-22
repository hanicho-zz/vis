#ifndef CSV_READER_H
#define CSV_READER_H

//
#include "common.h"

//  Comma.Seperated.Value Reader.
//
class csv_reader
{
public:
    csv_reader( QString path );
    ~csv_reader();


    //
    QString line();
    QStringList line_tokens();

    //  Returns [True] if there are more lines left.
    //  [False] otherwise.
    //
    bool goto_next_line();

    //
    QString _path;
    std::string _line;

    //
    std::ifstream _instream;

    //
    bool _bad_path;
};

#endif // CSV_READER_H

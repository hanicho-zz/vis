#include "csv_reader.h"



//
csv_reader::csv_reader( QString path )
    : _path( path ), _instream( path.toStdString().c_str() ), _bad_path(false)
{

    //  Does the file exist?!
    //
    QFile Fout(path);

    if(!Fout.exists()){
        _bad_path=true;
        helpers::debug_error( "path does not exist...", "csv reader", path );
    }
}

//

csv_reader::~csv_reader()
{
    //
    _instream.close();
}


//
QString csv_reader::line(){ return QString(_line.c_str()); }
QStringList csv_reader::line_tokens(){

    //
    return QString(_line.c_str()).split( ',' );
}
bool csv_reader::goto_next_line()
{

    //  If 0, the stream has reached it's end.
    //
    return ( std::getline( _instream, _line ) != 0 );
}

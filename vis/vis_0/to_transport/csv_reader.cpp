#include "csv_reader.h"



//
csv_reader::csv_reader( QString path )
    : _path( path )
{}

//

csv_reader::~csv_reader()
{
    //
    if( _instream ){
        _instream->close();
        delete _instream;
        _instream=0;
    }
}


//
QString csv_reader::line(){ return QString(_line.c_str()); }
QStringList csv_reader::line_tokens(){

    //
    return QString(_line.c_str()).split( ',' );
}
bool csv_reader::goto_next_line()
{
    //
    if( !_instream )
        return false;

    //  If 0, the stream has reached it's end.
    //
    return ( std::getline( (*_instream), _line ) != 0 );
}

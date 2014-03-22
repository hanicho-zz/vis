#include "dataset_descriptor.h"
#include "csv_reader.h"

//++++++++++++++++++++++++++++++++++
dataset_descriptor::dataset_descriptor( QString path_obsrv, QString path_colors, QString path_info )
{
    //
    find_path_directory( path_obsrv );
    find_dataset_name( path_obsrv );

    //  Find our attributes and class options.
    //
    file_to_info( path_obsrv, path_colors, path_info );
}
//++++++++++++++++++++++++++++++++++

//
//++++++++++++++++++++++++++++++++++
QString dataset_descriptor::class_type(){ return _class_type; }
QStringList dataset_descriptor::class_options(){ return _class_options; }
database_element_type dataset_descriptor::value_type_to_data_type( QString value_type ) { return _map_value_type_to_data_type[ value_type ]; }
QVector3D dataset_descriptor::class_option_to_color( QString option ){

    //
    QColor color = _map_class_to_color[option];

    //
    return QVector3D( color.redF(), color.greenF(), color.blueF() );
}
QString dataset_descriptor::path_directory(){ return _path_directory; }
QString dataset_descriptor::dataset_name(){ return _dataset_name; }
QStringList dataset_descriptor::attributes(){ return _list_sorted_attribute_types; }
std::map<QString,QColor>* dataset_descriptor::map_class_option_to_color(){ return &_map_class_to_color; }
std::vector< std::pair<QString,QColor> >* dataset_descriptor::list_class_option_to_color(){ return &_list_class_to_color; }
std::vector< QVector3D > dataset_descriptor::list_color(){

    //
    std::vector<QVector3D> colors;
    QColor color;

    //
    for( int ii=0; ii<_list_class_to_color.size(); ii++ ){

        //
        color = _list_class_to_color.at(ii).second;

        //
        colors.push_back( QVector3D(color.redF(),color.greenF(),color.blueF()) );
    }

    //
    return colors;
}
QStringList* dataset_descriptor::cached_attribute_options( QString attribute ){

    //  Not found?
    //
    if( _map_attribute_options.find( attribute ) == _map_attribute_options.end() )
        return 0;

    //  Found.
    //
    return &_map_attribute_options[attribute];
}
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void dataset_descriptor::file_to_info( QString path_obsrv, QString path_colors, QString path_info ){

    //
    csv_reader reader( path_obsrv );

    //  Find attributes.
    //  Note that the character '-' is illegal. Use '_' instead.
    //
    reader.goto_next_line();
    QStringList atts = reader.line_tokens();
    for( int ii=0; ii<atts.size(); ii++ ){
        QString str = atts.at( ii );
        str.replace( "-", "_" );
        _list_sorted_attribute_types.push_back( str );
    }

    //  Find class options.
    //  Note that the character '-' is illegal. Use '_' instead.
    //
    reader.goto_next_line();
    QStringList classes = reader.line_tokens();
    for( int ii=0; ii<classes.size(); ii++ ){
        QString str = classes.at( ii );
        str.replace( "-", "_" );
        _class_options.push_back( str );
    }

    //  Find the class type.
    //
    _class_type = _list_sorted_attribute_types.back();

    //  Find class option colors.
    //
    csv_reader color_reader( path_colors );
    while( color_reader.goto_next_line() )
        cache_class_option_color( color_reader.line_tokens() );

    //  Find the dataset's attribute info.
    //
    cache_info( path_info );
}

void dataset_descriptor::find_path_directory( QString path_obsrv ){

    //
    QStringList tokens = path_obsrv.split('/');

    //
    QString path = "";
    for( int ii=0; ii< tokens.size()-1; ii++ )
        path.append( tokens.at(ii) + "/" );

    //
    _path_directory = path;
}

void dataset_descriptor::find_dataset_name( QString path_obsrv ){

    //
    QStringList tokens = path_obsrv.split('/');

    //
    QString name = tokens.back();
    name = name.remove( ".obsrv" );

    //
    _dataset_name = name;
}

//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void dataset_descriptor::cache_point( model_point &point ){

    //
    if( !_class_options.contains( point._attribute_class ) )
        cache_class_option( point );

    //  We should have as many sorted attribute types as the point has attribute values...
    //
    assert( point._attribute_values.size() == _list_sorted_attribute_types.size() );

    //
    //for( int ii=0; ii<point._attribute_values.size(); ii++ )
        //cache_attribute_type( ii, point._attribute_values.at(ii) );
}
//
void dataset_descriptor::cache_class_option( model_point &point ){

    //
    _class_options.push_back( point._attribute_class );
}
void dataset_descriptor::cache_attribute_type( int index, QString value ){

    //  The attribute type.
    //
    QString atype = _list_sorted_attribute_types.at( index );

    //  Detect the data type of the value.
    //
    bool OK;
    enum database_element_type dtype;

    //  Int?
    //
    value.toInt(&OK);
    if( OK )
        dtype = E_INT;

    //  Double?
    //
    value.toDouble(&OK);
    if( OK )
        dtype = E_DOUBLE;

    //  Default to being a string.
    //
    dtype = E_STRING;

    //  Record the findings.
    //
    _map_value_type_to_data_type[ atype ] = dtype;
}
void dataset_descriptor::cache_class_option_color( QStringList options_colors ){

    //
    assert( options_colors.size() == 4 );

    //
    QString option = options_colors.at(0);
    option.replace("-","_");

    //
    int r = options_colors.at(1).toInt();
    int g = options_colors.at(2).toInt();
    int b = options_colors.at(3).toInt();

    //
    _map_class_to_color[ option ] = QColor(r,g,b);

    //
    _list_class_to_color.push_back( std::pair<QString,QColor>( option, QColor(r,g,b) ) );
}

void dataset_descriptor::cache_info( QString path_info ){

    //
    if( path_info.compare("") == 0 )
        return;

    //
    QFile inputFile( path_info );
    if( !inputFile.exists() )
        return;

    //
    QString attr_name = "";
    QString attr_type= "";

    //
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while ( !in.atEnd() )
       {
           //
           QStringList tokens = in.readLine().split(' ');

           //
           QString tag = (QString)tokens.first();

           //   Get the attribute name.
           //
           if( tag.compare( "#a" ) == 0 ){

               //
               attr_name = (QString)tokens.at(1);
           }

           //   Get the attribute type.
           //
           else if( tag.compare( "#t" ) == 0 ){

               //
               attr_type = (QString)tokens.at(1);

               //
               if( attr_type.compare("numeric") == 0 )
                _map_value_type_to_data_type[ attr_name ] = E_INT;
               else if( attr_type.compare("category") == 0 )
                _map_value_type_to_data_type[ attr_name ] = E_STRING;
               else if( attr_type.compare("category_binned") == 0 )
                _map_value_type_to_data_type[ attr_name ] = E_STRING;
           }

           //   Get the attribute value.
           //
           else if( tag.compare( "#v" ) == 0 ){

               //
               QString label = (QString)tokens.at(1);
               QString value = (QString)tokens.at(2);

               //   Note categorical label-value relationships.
               //
               if( attr_type.compare( "category" ) == 0 )
                   _map_attribute_value_to_label[ attr_name ][ value ] = label;

               //   Also, note the available attribute values.
               //
               if( !_map_attribute_options[attr_name].contains(label) )
                   _map_attribute_options[attr_name].push_back( label );
           }
       }
    }

    //
    inputFile.close();
}

//++++++++++++++++++++++++++++++++++

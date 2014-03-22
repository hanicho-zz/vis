#ifndef DATASET_DESCRIPTOR_H
#define DATASET_DESCRIPTOR_H

//
#include "common.h"
#include "model_point.h"

//  What datatype is a certain element in our database?
//
enum database_element_type{
    E_INT,
    E_DOUBLE,
    E_STRING
};


//  Datasets can be absolutely hairy balls of nonsense!
//  This struct aims to package all the meta info of a dataset
//  to clarify things for typecasting and enumerating.
//
class dataset_descriptor
{
public:
    dataset_descriptor( QString path_obsrv, QString path_colors, QString path_info );

    //  Get.
    //
    QString class_type();
    QStringList class_options();
    QStringList attributes();
    database_element_type value_type_to_data_type( QString value_type );
    QVector3D class_option_to_color( QString option );
    QString path_directory();
    QString dataset_name();
    std::map<QString,QColor>* map_class_option_to_color();
    std::vector< std::pair<QString,QColor> >* list_class_option_to_color();
    std::vector< QVector3D > list_color();
    QStringList* cached_attribute_options( QString attribute );
    //  Cache.
    //  We don't initially know anything about the dataset.
    //  And we aren't going to crawl the dataset first to build this record.
    //  So we will dynamically cache any new meta-data we observe as we add points.
    //
    //  Calling this function is how you populate the descriptor with the dataset's meta-data.
    //
    void cache_point( model_point &point );

private:

    //
    void file_to_info( QString path_obsrv, QString path_colors, QString path_info );
    void find_path_directory( QString path_obsrv );
    void find_dataset_name( QString path_obsrv );

    //
    void cache_class_option( model_point &point );
    void cache_attribute_type( int index, QString value );
    void cache_class_option_color( QStringList options_colors );
    void cache_info( QString path_info );

    //
    QString _path_directory;
    QString _dataset_name;

    //  How can we classify this dataset's class type?
    //
    QString _class_type;

    //  What are the possible values of this dataset's class type?
    //
    QStringList _class_options;

    //
    std::map< QString, QStringList> _map_attribute_options;

    //  Starting up a map of attribute type information is tricky because
    //  the points only contain values. As in, the only thing relating those values
    //  to an attribute they represent is their order next to each other!
    //  This is very sloppy and can easily lead to messy designs if you don't yoke it into submission...
    //
    //  So! We begin by recording that attribute order. We then have a means of identifying what the values
    //  we cache later are supposed to stand for (this string represents a country, or that double reps an average rate of snowfall, etc).
    //
    QStringList _list_sorted_attribute_types;

    //  Relates database value types (age? country? occupation?) to
    //  data types( int? double? string? ).
    //
    std::map<QString,enum database_element_type> _map_value_type_to_data_type;

    //  Each class option has a color associated with it.
    //  Has no order.
    //
    std::map<QString,QColor> _map_class_to_color;

    //  Each class option has a color associated with it.
    //  Has order.
    //
    std::vector< std::pair<QString,QColor> > _list_class_to_color;

    //  A complete mapping of our attributes' labels and values.
    //  Great for categories.
    //  [map: attribute_name [map: value, label]].
    //
    std::map< QString, std::map< QString, QString > > _map_attribute_value_to_label;
};


#endif // DATASET_DESCRIPTOR_H

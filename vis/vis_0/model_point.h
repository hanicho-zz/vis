#ifndef MODEL_POINT_H
#define MODEL_POINT_H

//
#include "common.h"

//  The data for a point object.
//
//  This object should contain data that also exists within a
//  database element. This point is really just a temporary,
//  loose handle to that database element's information.
//
class model_point
{
public:
    model_point();

    //
    qreal class_value();

    //
    QVector2D _position;

    //
    QString _attribute_class;

    //
    std::vector<double> _probability_values;

    //
    QStringList _attribute_values;
};

#endif // MODEL_POINT_H

#ifndef MODEL_POINT_H
#define MODEL_POINT_H

//
#include <QVector2D>
#include <vector>

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
    QVector2D _position;

    //
    std::vector<double> _probabilities;
};

#endif // MODEL_POINT_H

#ifndef BUFFER_WORKER_H
#define BUFFER_WORKER_H

//
#include "common.h"
#include "visual_defines.h"
#include "dataset_db.h"

//  Parallelize visual buffer construction!
//  Thanks to Maya Posch.
//  http://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/
//
class buffer_worker : public QObject
{
    Q_OBJECT
public:
    buffer_worker( int index_length, int index_start, dataset_db *db );
    ~buffer_worker();

    void set_pie_specs( qreal cx, qreal cy, std::vector<double> &slice_percents, QVector3D true_color, std::vector<QVector3D> &silce_colors, qreal radius, int steps );

    std::vector<Vertex> _fragment_vertices;
    std::vector<GLshort> _fragment_indices;
    bool _finished;
public slots:
    void process();
signals:
    void finished();
    void error(QString err);
private:


    void create_pies( qreal cx, qreal cy, std::vector<double> &slice_percents, QVector3D true_color, std::vector<QVector3D> &silce_colors, qreal radius, int steps );

    int _index_count;
    int _index_start;
    int _index_length;

    //
    dataset_db* _db;
};

#endif // BUFFER_WORKER_H

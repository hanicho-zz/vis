#ifndef TOOLBOX_PEEL_H
#define TOOLBOX_PEEL_H

//
#include "common.h"
//
class gl_unit;

//
class toolbox_peel : public QWidget
{
    Q_OBJECT
public:
    explicit toolbox_peel(gl_unit *gl, QWidget *parent = 0);
    
    //
    QSlider *_peel_slider;
signals:
    
public slots:

private:

    //
    void init_layout();

    //
    void init_peel_slider(gl_unit *gl);
    
};

#endif // TOOLBOX_PEEL_H

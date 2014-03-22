#include "toolbox_peel.h"

//
#include "glwidget.h"

//  Construct.
//
//++++++++++++++++++++++
toolbox_peel::toolbox_peel(glwidget *glw, QWidget *parent) :
    QWidget(parent)
{
    //
    init_peel_slider(glw);

    //
    init_layout();
}
//++++++++++++++++++++++

//  Layout.
//
//++++++++++++++++++++++
void toolbox_peel::init_layout(){

    //
    QVBoxLayout *vbox = new QVBoxLayout(this);

    //
    {
        QHBoxLayout *hbox = new QHBoxLayout();
        vbox->addLayout(hbox);
        hbox->addWidget( _peel_slider );
    }
}

//++++++++++++++++++++++

//  Peel Slider.
//
//++++++++++++++++++++++
void toolbox_peel::init_peel_slider(glwidget *glw){

    //
    _peel_slider = new QSlider(Qt::Horizontal);
    _peel_slider->setRange(0, 100);
    _peel_slider->setSingleStep(1);
    _peel_slider->setPageStep(1);
    _peel_slider->setTickInterval(5);
    _peel_slider->setTickPosition(QSlider::TicksRight);


    //
    connect(_peel_slider, SIGNAL(valueChanged(int)), glw, SLOT(set_peel_percentage(int)));
}
//++++++++++++++++++++++

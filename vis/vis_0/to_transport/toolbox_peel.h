#ifndef TOOLBOX_PEEL_H
#define TOOLBOX_PEEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>

//
class glwidget;

//
class toolbox_peel : public QWidget
{
    Q_OBJECT
public:
    explicit toolbox_peel(glwidget *glw, QWidget *parent = 0);
    
    //
    QSlider *_peel_slider;
signals:
    
public slots:

private:

    //
    void init_layout();

    //
    void init_peel_slider(glwidget *glw);
    
};

#endif // TOOLBOX_PEEL_H

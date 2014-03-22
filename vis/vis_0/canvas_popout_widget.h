#ifndef CANVAS_POPOUT_WIDGET_H
#define CANVAS_POPOUT_WIDGET_H

//
#include "common.h"

//
class main_window;

//
class canvas_popout_widget : public QWidget
{
    Q_OBJECT
public:
    explicit canvas_popout_widget( main_window *main_window, QWidget *parent = 0);
    
    main_window *_ref_main_window;
signals:
    
public slots:

protected:
     void closeEvent(QCloseEvent *event);
    
};

#endif // CANVAS_POPOUT_WIDGET_H

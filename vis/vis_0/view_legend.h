#ifndef VIEW_LEGEND_H
#define VIEW_LEGEND_H

//
#include "common.h"


//
class view_legend : public QWidget
{
    Q_OBJECT
public:
    explicit view_legend(QWidget *parent = 0);

    //
    void clear_elements();
    void push_element( QString name, QColor color );

signals:
    
public slots:

private:
    //
    QVBoxLayout *_vbox_maj, *_vbox_min;

    QWidget *_container;
    
};

#endif // VIEW_LEGEND_H

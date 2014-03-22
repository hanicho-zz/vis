#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

//
#include <QMainWindow>

//
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>

//
class glwidget;
class toolbox_peel;
class canvas_popout_widget;

//
class main_window : public QMainWindow
{
    Q_OBJECT
    
public:
    main_window(QWidget *parent = 0);
    ~main_window();

    //
    void end_popout();

    //
    glwidget *_glwidget;
    toolbox_peel *_toolbox_peel;
    canvas_popout_widget *_window_canvas_popout;

public slots:
    void func_popout();
    void func_lasso();
    void func_zoom();
    void func_table();
    void func_peel();

protected:
     void closeEvent(QCloseEvent *event);
private:

    //
    void dbg_msg(QString msg);

    //
    void init_menu_file();

    //
    void init_toolbar();
    void uncheck_toolbar();
    QAction *act_popout;
    QAction *act_lasso;
    QAction *act_table;
    QAction *act_zoom;
    QAction *act_peel;

    //
    QWidget *_container_major;
    QWidget *_container_questionaire;
    QWidget *_container_toolbox;
    QWidget *_container_canvas;
    QVBoxLayout *_layout_canvas_vbox;
    QVBoxLayout *_layout_popout_vbox;

    //
    void init_containers();
    void init_questionaire();
    void init_toolbox();
    void init_canvas();

    //
    void init_glwidget();

    //
    void init_popout();
    void launch_popout();
};

#endif // MAIN_WINDOW_H

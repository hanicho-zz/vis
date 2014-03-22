#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


//
#include "common.h"
#include "library.h"

//
class glwidget;
class toolbox_peel;
class canvas_popout_widget;
class view_dataset_table;
class view_legend;
class view_compile;
class view_player;
class visualizer;
class view_search;

//
class main_window : public QMainWindow
{
    Q_OBJECT
    
public:
    main_window(QWidget *parent = 0);
    ~main_window();

    //
    void end_popout();

    //  Library.
    //
    library _library;

    //  Views and windows.
    //
    toolbox_peel *_toolbox_peel;
    canvas_popout_widget *_window_canvas_popout;
    view_dataset_table * _view_dataset;
    view_legend *_view_legend;
    view_compile *_view_compile;
    view_player *_view_player;
    visualizer *_visualizer;
    view_search *_view_search;

public slots:
    void func_popout();
    void func_lasso();
    void func_zoom();
    void func_table();
    void func_peel();
    void func_legend();
    void func_compile();
    void func_tour();
    void func_interrogation();
    void func_search();

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
    QAction *act_legend;
    QAction *act_compile;
    QAction *act_tour;
    QAction *act_interrogation;
    QAction *act_search;

    //
    QWidget *_container_major;
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

    //  Popout view.
    //
    void init_popout();
    void launch_popout();

    //  Legend view.
    //
    void init_view_legend();
    void launch_legend();
    void end_legend();

    //  Dataset table view.
    //
    void init_table_view();
    void launch_table_view();
    void end_table_view();

    //  Compile view.
    //
    void init_compile_view();
    void launch_compile_view();
    void end_compile_view();

    //  Player view.
    //
    void init_player_view();
    void launch_search_view();

    //  Search view.
    //
    void init_search_view();
    void end_search_view();
};

#endif // MAIN_WINDOW_H

#include "main_window.h"

//
#include "glwidget.h"
#include "toolbox_peel.h"
#include "canvas_popout_widget.h"

//
#include "test_bed.h"

//  Construct.
//
//++++++++++++++++++++++
main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
{

    //
    resize(1000, 800);

    //
    init_menu_file();
    init_toolbar();

    //
    init_containers();

    //
    init_popout();

    //
    test_bed test();
}
//++++++++++++++++++++++


//  Destruct.
//
//++++++++++++++++++++++
main_window::~main_window()
{
    
}
//++++++++++++++++++++++

//  Close.
//
//++++++++++++++++++++++
void main_window::closeEvent(QCloseEvent *event) {

    //
    end_popout();
}
//++++++++++++++++++++++

//  Debug.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::dbg_msg(QString msg){
    qDebug() << msg;
}

//+++++++++++++++++++++++++++++++++++++++++

//  Filemenu and actions.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_menu_file(){

    //
    QMenu *menu_file;
    menu_file = menuBar()->addMenu("&File");

    //  file >> quit.
    //
    menu_file->addSeparator();
    QAction *quit = new QAction("&Quit", this);
    menu_file->addAction(quit);
    connect(quit, SIGNAL(triggered()), this, SLOT(quit()));


    //
    QMenu *menu_about = menuBar()->addMenu("&About");
    QAction *about = new QAction("&about", this);
    menu_about->addAction(about);
    connect(about, SIGNAL(triggered()), this, SLOT(quit()));

    //
    QMenu *menu_help = menuBar()->addMenu("&Help");
    QAction *help = new QAction("&help", this);
    menu_help->addAction(help);
    connect(help, SIGNAL(triggered()), this, SLOT(quit()));
}
//+++++++++++++++++++++++++++++++++++++++++

//  Toolbar and actions.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_toolbar(){

    //
    QToolBar *toolbar = addToolBar("main toolbar");
    toolbar->setMovable(false);

    //
    act_popout = new QAction("Popout",0);
    act_lasso = new QAction("Lasso",0);
    act_table = new QAction("Table",0);
    act_zoom = new QAction("Zoom",0);
    act_peel = new QAction("Peel",0);

    //
    act_popout->setCheckable(false);
    act_lasso->setCheckable(true);
    act_table->setCheckable(true);
    act_zoom->setCheckable(true);
    act_peel->setCheckable(true);

    //
    toolbar->addAction( act_popout );
    toolbar->addAction( act_lasso );
    toolbar->addAction( act_table );
    toolbar->addAction( act_zoom );
    toolbar->addAction( act_peel );

    //
    connect(act_popout, SIGNAL(triggered()), this, SLOT(func_popout()));
    connect(act_lasso, SIGNAL(triggered()), this, SLOT(func_lasso()));
    connect(act_table, SIGNAL(triggered()), this, SLOT(func_zoom()));
    connect(act_zoom, SIGNAL(triggered()), this, SLOT(func_table()));
    connect(act_peel, SIGNAL(triggered()), this, SLOT(func_peel()));
}
void main_window::uncheck_toolbar(){

    //
    act_lasso->setChecked(false);
    act_table->setChecked(false);
    act_zoom->setChecked(false);
    act_peel->setChecked(false);

    //
    _toolbox_peel->setVisible(false);

}
void main_window::func_popout(){

    //
    launch_popout();
}
void main_window::func_lasso(){

    //
    uncheck_toolbar();

    //
    act_lasso->setChecked(true);
}
void main_window::func_zoom(){

    //
    uncheck_toolbar();

    //
    act_table->setChecked(true);
}
void main_window::func_table(){

    //
    uncheck_toolbar();

    //
    act_zoom->setChecked(true);
}
void main_window::func_peel(){

    //
    uncheck_toolbar();

    //
    act_peel->setChecked(true);

    //
    _toolbox_peel->setVisible(true);
}
//+++++++++++++++++++++++++++++++++++++++++

//  Major Container.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_containers(){

    //
    //  We want this.
    //
    //  =====================================
    //  |       |                           |
    //  |       |                           |
    //  |       |             B             |
    //  |       |                           |
    //  |   A   |                           |
    //  |       |                           |
    //  |       |============================
    //  |       |                           |
    //  |       |             C             |
    //  |       |                           |
    //  =====================================
    //
    //  A: questionaire. origin(0r,0c). size(10r,3c).
    //  B: canvas. origin(0r,3c). size(5r,7c).
    //  C: toolbox. origin(5r,3c). size(2r,7c).
    //
    //  The entire thing is within the "container_major".
    //
    //  The entire thing is 10x7.
    //

    //
    _container_major = new QWidget(this);
    _container_major->setStyleSheet("background-color:white;");
    setCentralWidget( _container_major );
    init_questionaire();
    init_canvas();
    init_toolbox();

    //
    QGridLayout *grid = new QGridLayout(_container_major);
    grid->addWidget( _container_questionaire, 0,0, 7,3 );
    grid->addWidget( _container_canvas, 0,3, 5,7 );
    grid->addWidget( _container_toolbox, 5,3, 2,7 );

}

//+++++++++++++++++++++++++++++++++++++++++

//  Quesionaire.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_questionaire(){

    //
    _container_questionaire = new QWidget;
    _container_questionaire->setStyleSheet("background-color:red;");

    //
    QVBoxLayout *vbox = new QVBoxLayout(_container_questionaire);
    vbox->addWidget( new QPushButton("QUESTIONAIRE") );
}
//+++++++++++++++++++++++++++++++++++++++++

//  Toolbox.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_toolbox(){

    //
    _toolbox_peel = new toolbox_peel( _glwidget );
    _glwidget->set_slider( _toolbox_peel->_peel_slider );
    _toolbox_peel->setVisible(false);

    //
    _container_toolbox= new QWidget();
    _container_toolbox->setStyleSheet("background-color:green;");

    //
    QVBoxLayout *vbox = new QVBoxLayout(_container_toolbox);
    vbox->addWidget( _toolbox_peel );
}
//+++++++++++++++++++++++++++++++++++++++++

//  Canvas.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_canvas(){

    //
    _container_canvas = new QWidget();
    _container_canvas->setStyleSheet("background-color:blue;");

    //
    _layout_canvas_vbox = new QVBoxLayout(_container_canvas);

    //
    init_glwidget();
    _layout_canvas_vbox->addWidget( _glwidget );
}
//+++++++++++++++++++++++++++++++++++++++++

//  GL Widget.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_glwidget(){

    //
    _glwidget = new glwidget();
}

//+++++++++++++++++++++++++++++++++++++++++


//  Canvas Popout
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_popout(){

    //
    _window_canvas_popout = new canvas_popout_widget( this, 0 );

    //
    _window_canvas_popout->resize(800,600);

    //
    _layout_popout_vbox = new QVBoxLayout(_window_canvas_popout);
}
void main_window::launch_popout(){

    //
    _window_canvas_popout->setVisible(true);

    //
    _layout_canvas_vbox->removeWidget(_glwidget);
    _layout_popout_vbox->addWidget(_glwidget);
}
void main_window::end_popout(){

    //
    _window_canvas_popout->setVisible(false);

    //
    _layout_popout_vbox->removeWidget(_glwidget);
    _layout_canvas_vbox->addWidget(_glwidget);
}
//+++++++++++++++++++++++++++++++++++++++++

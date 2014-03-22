#include "main_window.h"

//
#include "glwidget.h"
#include "toolbox_peel.h"
#include "canvas_popout_widget.h"
#include "view_dataset_table.h"
#include "view_legend.h"
#include "view_compile.h"
#include "view_player.h"
#include "interrogation_factory.h"
#include "tour_factory.h"
#include "tour.h"
#include "interrogation.h"
#include "visualizer.h"
#include "gl_unit.h"
#include "view_search.h"

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
    showMaximized();

    //
    setWindowTitle("Model Investigator");

    //
    init_menu_file();
    init_toolbar();

    //
    init_containers();

    //
    init_popout();
    init_table_view();
    init_view_legend();
    init_compile_view();
    init_search_view();

    //  Testing.
    //
    //test_bed test;
    //test.go( &_library );

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

    //
    end_table_view();

    //
    end_legend();

    //
    end_compile_view();

    //
    end_search_view();
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
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));

    //
    QMenu *menu_about = menuBar()->addMenu("&About");
    QAction *about = new QAction("&About", this);
    menu_about->addAction(about);
    connect(about, SIGNAL(triggered()), this, SLOT(close()));

    //
    QMenu *menu_help = menuBar()->addMenu("&Help");
    QAction *help = new QAction("&Help", this);
    menu_help->addAction(help);
    connect(help, SIGNAL(triggered()), this, SLOT(close()));
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
    act_legend = new QAction("Legend",0);
    act_compile = new QAction("Compile",0);
    act_tour = new QAction("Tour",0);
    act_interrogation = new QAction("Interrogation",0);
    act_search = new QAction("Search", 0);

    //
    act_popout->setCheckable(false);
    act_lasso->setCheckable(true);
    act_table->setCheckable(false);
    act_zoom->setCheckable(true);
    act_peel->setCheckable(true);
    act_legend->setCheckable(false);
    act_compile->setCheckable(false);
    act_tour->setCheckable(false);
    act_interrogation->setCheckable(false);
    act_search->setCheckable(false);

    //
    toolbar->addAction( act_popout );
    toolbar->addAction( act_lasso );
    toolbar->addAction( act_table );
    toolbar->addAction( act_zoom );
    toolbar->addAction( act_peel );
    toolbar->addAction( act_legend );
    toolbar->addAction( act_compile );
    toolbar->addAction( act_tour );
    toolbar->addAction( act_interrogation );
    toolbar->addAction( act_search );

    //
    connect(act_popout, SIGNAL(triggered()), this, SLOT(func_popout()));
    connect(act_lasso, SIGNAL(triggered()), this, SLOT(func_lasso()));
    connect(act_table, SIGNAL(triggered()), this, SLOT(func_table()));
    connect(act_zoom, SIGNAL(triggered()), this, SLOT(func_zoom()));
    connect(act_peel, SIGNAL(triggered()), this, SLOT(func_peel()));
    connect(act_legend, SIGNAL(triggered()), this, SLOT(func_legend()) );
    connect(act_compile, SIGNAL(triggered()), this, SLOT(func_compile()));
    connect(act_tour, SIGNAL(triggered()), this, SLOT(func_tour()));
    connect(act_interrogation, SIGNAL(triggered()), this, SLOT(func_interrogation()));
    connect(act_search, SIGNAL(triggered()), this, SLOT(func_search()) );
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
    act_zoom->setChecked(true);
}
void main_window::func_table(){


    //
    launch_table_view();
}
void main_window::func_peel(){

    //
    uncheck_toolbar();

    //
    act_peel->setChecked(true);

    //
    _toolbox_peel->setVisible(true);
}
void main_window::func_legend(){

    //
    launch_legend();
}
void main_window::func_compile(){

    //
    launch_compile_view();
}
void main_window::func_tour(){

    //  Show the QFileDialog.
    //
    QString filename = QFileDialog::getOpenFileName( this, QString("Open File"), "", QString("Tour Files(*.tour)") );
    if( filename == "" )
        return;

    //
    tour_factory fac( &_library );
    fac.load_file( filename );

    //
    _library.apply_model_tour( fac.get_tour() );
}
void main_window::func_interrogation(){

    //  Show the QFileDialog.
    //
    QString filename = QFileDialog::getOpenFileName( this, QString("Open File"), "", QString("Interrogation Files(*.int)") );
    if( filename == "" )
        return;


    //  Process.
    //
    {
        //
        _view_search->clear();
        _view_dataset->clear();
        _library._ref_visualizer->clear_databases();

        //
        interrogation_factory fac( &_library );
        fac.load_file( filename );

        //
        _library.apply_model_interrogation( fac.get_interrogation() );
    }
}
void main_window::func_search(){

    //
    launch_search_view();
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
    init_canvas();
    init_toolbox();
    init_player_view();

    //
    QGridLayout *grid = new QGridLayout(_container_major);
    grid->addWidget( _view_player, 0,0, 7,3 );
    grid->addWidget( _container_canvas, 0,3, 5,7 );
    grid->addWidget( _container_toolbox, 5,3, 2,7 );

}

//+++++++++++++++++++++++++++++++++++++++++

//  Toolbox.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_toolbox(){

    //
    _toolbox_peel = new toolbox_peel( &_visualizer->_gl  );
    //_visualizer->_gl->set_slider( _toolbox_peel->_peel_slider );
    _toolbox_peel->setVisible(false);

    //
    _container_toolbox= new QWidget();
    _container_toolbox->setStyleSheet("background-color:white;");

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
    _container_canvas->setStyleSheet("background-color:black;");

    //
    _layout_canvas_vbox = new QVBoxLayout(_container_canvas);

    //
    init_glwidget();
    _layout_canvas_vbox->addWidget( &_visualizer->_gl  );
}
//+++++++++++++++++++++++++++++++++++++++++

//  GL Widget.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_glwidget(){


    //
    _visualizer = new visualizer( &_library );

    //
    _library._ref_visualizer = _visualizer;
}
//+++++++++++++++++++++++++++++++++++++++++

//  Canvas popout.
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
    _layout_canvas_vbox->removeWidget( &_visualizer->_gl  );
    _layout_popout_vbox->addWidget( &_visualizer->_gl  );

}
void main_window::end_popout(){


    //
    _window_canvas_popout->setVisible(false);

    //
    _layout_popout_vbox->removeWidget( &_visualizer->_gl );
    _layout_canvas_vbox->addWidget( &_visualizer->_gl  );

}
//+++++++++++++++++++++++++++++++++++++++++

//  Table View.
//
//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_table_view(){

    //
    _view_dataset = new view_dataset_table();
    _view_dataset->hide();

    //
    _library._ref_view_dataset_table = _view_dataset;
}
void main_window::launch_table_view(){

    //
    _view_dataset->show();
}
void main_window::end_table_view(){

    //
    _view_dataset->hide();
}
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_view_legend(){

    //
    _view_legend = new view_legend();
    _view_legend->hide();

    //
    _library._ref_view_legend = _view_legend;
}
void main_window::launch_legend(){ _view_legend->show(); }
void main_window::end_legend(){ _view_legend->hide( ); }
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_compile_view(){

    //
    _view_compile = new view_compile( &_library );

    //
    _view_compile->hide();
}
void main_window::launch_compile_view(){ _view_compile->show(); }
void main_window::end_compile_view(){ _view_compile->hide(); }
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_player_view(){

    //
    _view_player = new view_player( &_library );

    //
    _library._ref_view_player=_view_player;
}
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void main_window::init_search_view(){

    //
    _view_search = new view_search(&_library);
}
void main_window::launch_search_view(){

    //
    _view_search->show();
}
void main_window::end_search_view(){ _view_search->manual_hide(); }
//+++++++++++++++++++++++++++++++++++++++++

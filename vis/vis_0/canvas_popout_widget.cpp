#include "canvas_popout_widget.h"

//
#include "main_window.h"

//
canvas_popout_widget::canvas_popout_widget(main_window *main_window, QWidget *parent)
    : _ref_main_window(main_window), QWidget(parent, Qt::Window)
{
    setWindowTitle("Model Popout");
    setWindowIcon(QIcon(QDir::currentPath() + "/../vis_0/data/MAPLE_logo_transparent.gif"));
}

//  Close.
//
//++++++++++++++++++++++
void canvas_popout_widget::closeEvent(QCloseEvent *event) {

    //
    _ref_main_window->end_popout();
}
//++++++++++++++++++++++

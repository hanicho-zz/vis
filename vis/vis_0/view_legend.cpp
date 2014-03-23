#include "view_legend.h"

view_legend::view_legend(QWidget *parent) :
    QWidget(parent)
{

    //
    resize(1000, 500);

    //
    setWindowTitle("Legend");
    setWindowIcon(QIcon(QDir::currentPath() + "/../vis_0/data/MAPLE_logo_transparent.gif"));

    //
    _vbox_maj = new QVBoxLayout;
    setLayout( _vbox_maj );

    //
    _vbox_min = new QVBoxLayout;

    //
    _container = new QWidget;
    _container->setLayout( _vbox_min );
    _vbox_maj->addWidget( _container );

    //
    push_element( "yabba", Qt::red );
    //
    push_element( "dabba", Qt::green );
    //
    push_element( "doo", Qt::blue );
}


//
void view_legend::push_element( QString name, QColor color )
{
    //  Make our text.
    //
    QLabel *label = new QLabel( name );

    //  Create our button.
    //
    QPushButton *button = new QPushButton( );
    button->setEnabled( false );

    //  Color our button.
    //
    QString style = QString("background-color: rgb(%1, %2, %3);")
            .arg(color.red()).arg(color.green()).arg(color.blue());
    button->setStyleSheet(style);

    //  Horizantally group the text and button.
    //
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget( label );
    hbox->addWidget( button );

    //  Vertically group the horizontal group.
    //
    _vbox_min->addLayout( hbox );

    //
    repaint();
}
void view_legend::clear_elements()
{
    //
    delete _vbox_min;
    _vbox_min = new QVBoxLayout;

    //
    delete _container;
    _container = new QWidget;

    //
    _container->setLayout( _vbox_min );
    _vbox_maj->addWidget( _container );
}

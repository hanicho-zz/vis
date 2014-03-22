#include "view_new_search.h"
#include "library.h"
#include "dataset_db.h"
#include "search_result.h"
#include "search_table.h"
#include "view_search.h"

//++++++++++++++++++++++++++++++++++
view_new_search::view_new_search(library *lib, QWidget *parent )
    :   QWidget(parent), _ref_library( lib )
{

    //
    resize( 800, 600 );

    //
    init_layout();

    //
    setWindowTitle("Create New Search");
}
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void view_new_search::init_layout(){

    //
    _vbox = new QVBoxLayout();
    setLayout(_vbox);

    //
    _hbox_top = new QHBoxLayout();
    _hbox_mid = new QHBoxLayout();
    _hbox_low = new QHBoxLayout();
    _vbox->addLayout( _hbox_top );
    _vbox->addLayout( _hbox_mid );
    _vbox->addLayout( _hbox_low );

    //  Top.
    //
    _list_attributes = new QListWidget();
    _list_cats = new QListWidget();
    connect( _list_attributes, SIGNAL( itemClicked(QListWidgetItem*) ), this, SLOT( write_categories(QListWidgetItem*) ) );
    connect( _list_cats, SIGNAL( itemClicked(QListWidgetItem*) ), this, SLOT( append_value_to_query(QListWidgetItem*) ) );
    _hbox_top->addWidget( _list_attributes );
    _hbox_top->addWidget( _list_cats );

    //  Mid.
    //
    _text_query = new QTextEdit();
    _hbox_mid->addWidget( _text_query );

    //  Low.
    //
    _button_help = new QPushButton( "Help" );
    _button_submit = new QPushButton( "Submit" );
    _button_cancel = new QPushButton( "Cancel" );
    connect(_button_help, SIGNAL(clicked()), this, SLOT(do_help()) );
    connect(_button_submit, SIGNAL(clicked()), this, SLOT(do_submit()) );
    connect(_button_cancel, SIGNAL(clicked()), this, SLOT(close()) );

    _hbox_low->addWidget( _button_help );
    _hbox_low->addWidget( _button_submit );
    _hbox_low->addWidget( _button_cancel );
}

//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void view_new_search::write(){

    //
    write_attributes();
}

void view_new_search::write_attributes(){

    //
    _list_attributes->clear();

    //
    if( !_ref_library->_active_database )
        return;

    //  Set our shown attributes in our list.
    //
    _list_attributes->addItems( _ref_library->_active_database->descriptor()->attributes() );
}
void view_new_search::write_categories(QListWidgetItem *item){

    //
    _list_cats->clear();

    //
    if( !_ref_library->_active_database || !item )
        return;

    //  Find if our attribute type is categorical or not.
    //
    QString attr = item->text();
    database_element_type ty = _ref_library->_active_database->descriptor()->value_type_to_data_type( attr );
    if( ty != E_STRING )
        return;

    //
    helpers::debug_out( QString("attribute: %0").arg(attr) );

    //  Set our shown attribute categorical values in our list.
    //
    QStringList *options = _ref_library->_active_database->descriptor()->cached_attribute_options(attr);
    if( options )
        _list_cats->addItems( *options );
}
void view_new_search::append_value_to_query(QListWidgetItem *item){


    //
    if( !item )
        return;

    //  Which category did we select?
    //
    QString attr = _list_attributes->currentItem()->text();

    //
    QString cat = item->text();

    //
    QString entry = QString("%1 = \"%2\"").arg(attr).arg(cat);

    //  Append this value to our text edit area.
    //
    _text_query->append( entry );
}

//++++++++++++++++++++++++++++++++++

void view_new_search::do_submit(){

    //  Get the filter.
    //
    QString filter = _text_query->toPlainText();

    //  Process the filter.
    //  Remove the last newline.
    //  Replace newlines with 'AND'
    //
    filter.replace("\n", " and ");

    //  Create a new search with it.
    //
    search_result* result = new search_result( _ref_library, filter.toStdString() );

    //  Store it in the library.
    //
    _ref_library->_search_results.push_back( result );

    //
    _ref_library->_ref_view_search->update_combobox();

    //
    hide();
}

void view_new_search::do_help(){

    //
    QString msg="";
    msg.append("   ---   Examples of use ---   \n");
    msg.append("example (females):\n");
    msg.append("\n");
    msg.append("Sex = \"Female\"\n");
    msg.append("\n");
    msg.append("example (females of race other):\n");
    msg.append("\n");
    msg.append("Sex = \"Female\"\n");
    msg.append("Race != \"Other\"\n");
    msg.append("\n");
    msg.append("example (females of race other age 30 and up):\n");
    msg.append("\n");
    msg.append("Sex = \"Female\"\n");
    msg.append("Race != \"Other\"\n");
    msg.append("Age >= 30\n");

    //
    QMessageBox messageBox;
    messageBox.setWindowTitle("Search Help");
    messageBox.setText(msg);
    messageBox.setDefaultButton( QMessageBox::Ok );
    messageBox.setFixedSize(500,200);
    messageBox.exec();
}

//
void view_new_search::clear(){

}

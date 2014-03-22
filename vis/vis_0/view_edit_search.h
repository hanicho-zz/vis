#ifndef VIEW_EDIT_SEARCH_H
#define VIEW_EDIT_SEARCH_H

//
#include "common.h"

//
class library;
class search_result;

//
class view_edit_search : public QWidget
{
    Q_OBJECT
public:
    view_edit_search( library *lib, QWidget *parent=0 );
    void write();


    //
    void clear();

    //
    search_result* _active_result;
public Q_SLOTS:
    void write_categories(QListWidgetItem*);
    void append_value_to_query(QListWidgetItem*);
    void do_submit();
    void do_help();

private:

    //
    void init_layout();

    //
    void write_attributes();

    //
    library *_ref_library;

    //
    QVBoxLayout *_vbox;
    QHBoxLayout *_hbox_top, *_hbox_mid, *_hbox_low;

    //
    QListWidget *_list_attributes;
    QListWidget *_list_cats;

    //
    QTextEdit *_text_query;

    //
    QPushButton *_button_use_attribute;
    QPushButton *_button_use_cat_value;
    QPushButton *_button_help;
    QPushButton *_button_submit;
    QPushButton *_button_cancel;
};

#endif // VIEW_EDIT_SEARCH_H

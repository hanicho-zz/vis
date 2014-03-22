#ifndef VIEW_SEARCH_H
#define VIEW_SEARCH_H

//
#include "common.h"

//
class library;
class view_new_search;
class view_edit_search;
class search_result;

//
class view_search : public QWidget
{
    Q_OBJECT
public:
    explicit view_search( library* lib, QWidget *parent = 0);
    
    //
    void manual_hide();

    //
    void update_combobox();
    void sort_column( int column );

    //
    void clear();

signals:
    
public slots:

    //
    void search_highlighted(QString result);

    //
    void func_rename();
    void func_new();
    void func_delete();
    void func_edit();
    void func_draw();
    void func_stats();
    void func_linear();

    //
    void func_view_new_search();
    void func_view_edit_search();

    //
    void onColumnChanged(const QModelIndex &index);
private:

    //
    void init_combobox();

    //
    void init_actions();

    //
    void init_table();

    //
    void init_view_new_search();
    void launch_view_new_search();
    void end_view_new_search();

    //
    void init_view_edit_search();
    void launch_view_edit_search();
    void end_view_edit_search();

    //
    search_result* get_highlighted_search();

    //
    QVBoxLayout *_main_layout;
    QHBoxLayout *_top_layout;

    //
    QComboBox *_combo_names;

    //
    QAction *_act_rename;
    QAction *_act_new;
    QAction *_act_delete;
    QAction *_act_edit;
    QAction *_act_draw;
    QAction *_act_stats;
    QAction *_act_linear;

    //
    QTableView *_table_view;

    //
    library* _ref_library;

    //
    view_new_search *_view_new_search;
    view_edit_search *_view_edit_search;

    //
    search_result* _current_result;
};

#endif // VIEW_SEARCH_H

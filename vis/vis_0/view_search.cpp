#include "view_search.h"
#include "library.h"
#include "view_new_search.h"
#include "view_edit_search.h"
#include "search_result.h"
#include <QInputDialog>
#include "visualizer.h"

//+++++++++++++++++++++++++++++++++++++++++
view_search::view_search( library* lib, QWidget *parent) :
    QWidget(parent), _ref_library(lib), _current_result(0)
{
    //
    resize( 800, 600 );

    //
    setWindowTitle("Dataset Search");

    //
    _main_layout = new QVBoxLayout();
    setLayout( _main_layout );

    //
    _top_layout = new QHBoxLayout();
    _main_layout->addLayout( _top_layout );

    //
    init_view_new_search();
    init_view_edit_search();

    //
    init_combobox();

    //
    init_actions();

    //
    init_table();

    //
    _ref_library->_ref_view_search=this;
}
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void view_search::init_combobox(){

    //
    _combo_names = new QComboBox();

    //
    _top_layout->addWidget( _combo_names );

    //
    connect( _combo_names, SIGNAL(highlighted(QString)), this, SLOT(search_highlighted(QString)) );
}
void view_search::update_combobox(){

    //
    _combo_names->clear();

    //  Add a name for each search result in the library.
    //
    for( int ii=0; ii<_ref_library->_search_results.size(); ii++ )
        _combo_names->addItem( _ref_library->_search_results.at(ii)->_name );

    //  Select the first result.
    //
    if( _combo_names->count() > 0 )
        _combo_names->setCurrentIndex(0);
}

search_result* find_result_in_library( QString name, library* lib){

    //
    std::vector <search_result*> *results = &lib->_search_results;

    //
    for( int ii=0; ii<results->size(); ii++ )
        if( name.compare( results->at(ii)->_name ) == 0 )
            return results->at(ii);

    //
    return 0;
}

void view_search::search_highlighted(QString result){

    //
    //helpers::debug_out( QString("highlighted result: %1...").arg(result) );

    //
    _current_result = find_result_in_library( result, _ref_library );
    if( !_current_result )
        return;

    if( _table_view->selectionModel() )
        disconnect( _table_view->selectionModel(), SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)), this, SLOT(onColumnChanged(QModelIndex)) );

    //
    _table_view->setModel( _current_result->_table._table_model );
    _table_view->show();

    //
    connect( _table_view->selectionModel(), SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)), this, SLOT(onColumnChanged(QModelIndex)) );
}
//+++++++++++++++++++++++++++++++++++++++++

void view_search::sort_column( int column ){

    //
    if( !_current_result )
        return;

    //  Sort by column.
    //
    _table_view->setSortingEnabled(true);
    _table_view->sortByColumn( column );
}
void view_search::onColumnChanged(const QModelIndex &index){

    //
    int col = index.column();

    //
    sort_column( col );
}

//+++++++++++++++++++++++++++++++++++++++++
void view_search::init_actions(){

    //
    QToolBar *toolbar = new QToolBar("toolbar");
    toolbar->setMovable(false);
    _top_layout->addWidget( toolbar );

    //
    _act_rename = new QAction("Rename",0);
    _act_new = new QAction("new",0);
    _act_delete = new QAction("delete",0);
    _act_edit = new QAction("edit",0);
    _act_draw = new QAction("draw",0);
    _act_stats = new QAction("stats",0);
    _act_linear = new QAction("linear",0);

    //
    _act_rename->setCheckable(false);
    _act_new->setCheckable(false);
    _act_delete->setCheckable(false);
    _act_edit->setCheckable(false);
    _act_draw->setCheckable(false);
    _act_stats->setCheckable(false);
    _act_linear->setCheckable(false);

    //
    toolbar->addAction( _act_rename );
    toolbar->addAction( _act_new );
    toolbar->addAction( _act_delete );
    toolbar->addAction( _act_edit );
    toolbar->addAction( _act_draw );
    toolbar->addAction( _act_stats );
    toolbar->addAction( _act_linear );

    //
    connect(_act_rename, SIGNAL(triggered()), this, SLOT(func_rename()));
    connect(_act_new, SIGNAL(triggered()), this, SLOT(func_new()));
    connect(_act_delete, SIGNAL(triggered()), this, SLOT(func_delete()));
    connect(_act_edit, SIGNAL(triggered()), this, SLOT(func_edit()));
    connect(_act_draw, SIGNAL(triggered()), this, SLOT(func_draw()));
    connect(_act_stats, SIGNAL(triggered()), this, SLOT(func_stats()) );
    connect(_act_linear, SIGNAL(triggered()), this, SLOT(func_linear()));
}
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void view_search::func_rename(){

    //
    if(!_current_result)
        return;

    //
    bool ok;
    QString new_name = QInputDialog::getText(this, tr("Enter New Name"),tr("Search Result Name:"), QLineEdit::Normal,"", &ok);
    if( !ok )
        return;

    //
    _current_result->_name = new_name;
    update_combobox();
}
void view_search::func_new(){ func_view_new_search(); }
void view_search::func_delete(){

    //
    if(!_current_result)
        return;

    //  Remove the result from the library.
    //
    std::vector< search_result*> *list = &_ref_library->_search_results;
    list->erase( std::remove( list->begin(), list->end(), _current_result ), list->end() );

    //  Clear our current.
    //
    _current_result=0;
    _view_edit_search->_active_result=0;

    //  Remove the model.
    //
    _table_view->setModel(0);

    //  Update.
    //
    update_combobox();
}
void view_search::func_edit(){ func_view_edit_search(); }
void view_search::func_draw(){

    //
    if( !_current_result )
        return;

    //  Redraw our glyphs.
    //
    _ref_library->_active_search_table = &_current_result->_table;
    _ref_library->_ref_visualizer->remake_active_vis();
    _current_result->_table.apply_filter();

}
void view_search::func_stats(){}
void view_search::func_linear(){}
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void view_search::init_table(){

    //
    _table_view = new QTableView();
    _table_view->setEditTriggers( QAbstractItemView::NoEditTriggers );

    //
    _main_layout->addWidget( _table_view );
}
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void view_search::init_view_new_search(){ _view_new_search = new view_new_search(_ref_library); }
void view_search::func_view_new_search(){

    //
    launch_view_new_search();

    //
    _view_new_search->write();
}
void view_search::launch_view_new_search(){ _view_new_search->show(); }
void view_search::end_view_new_search(){ _view_new_search->hide(); }
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void view_search::init_view_edit_search(){ _view_edit_search = new view_edit_search(_ref_library); }
void view_search::func_view_edit_search(){

    //
    launch_view_edit_search();

    //
    _view_edit_search->write();
}
void view_search::launch_view_edit_search(){

    //
    if(!_current_result)
        return;

    //
    _view_edit_search->_active_result = _current_result;

    //
    _view_edit_search->show();
}
void view_search::end_view_edit_search(){ _view_edit_search->hide(); }
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void view_search::manual_hide(){

    //
    end_view_new_search();
    end_view_edit_search();

    //
    hide();
}
//+++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++
void view_search::clear(){

    //
    _table_view->setModel(0);

    //
    _combo_names->clear();

    //
    _view_new_search->clear();
    _view_edit_search->clear();
}
//+++++++++++++++++++++++++++++++++++++++++

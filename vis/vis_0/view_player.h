#ifndef VIEW_PLAYER_H
#define VIEW_PLAYER_H

//
#include "common.h"
#include "model_player.h"

//
class library;

//
class view_player : public QWidget
{
    Q_OBJECT
public:
    explicit view_player( library *lib, QWidget *parent = 0);
    
    //
    void run_model_interrogation( model_player* model );
    void run_model_tour( model_player* model );

signals:
    
public slots:

    //
    void progress_next();
    
private:

    //
    void init_view();

    //
    void hide_all_options();

    //
    void set_question( question *q );

    //
    QGridLayout *_grid;
    QTextBrowser* _text_browser;
    std::vector< QHBoxLayout* > _list_hbox;
    std::vector< QLabel* > _list_label;
    std::vector< QCheckBox* > _list_check;

    //
    library *_ref_library;

    //
    model_player *_ref_model_player;
};

#endif // VIEW_PLAYER_H

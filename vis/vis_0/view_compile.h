#ifndef VIEW_COMPILE_H
#define VIEW_COMPILE_H

//
#include "common.h"
#include "model_compile.h"

//
class library;

//
class view_compile : public QWidget
{
    Q_OBJECT
public:
    explicit view_compile( library* lib, QWidget *parent = 0);
    
signals:
    
public slots:

    //
    void OnOkPressed();
    void OnCancelPressed();
    void compile_finished( );
    void cancel_compile();
    
private:

    //
    void init_view();

    //
    void show_progress();
    void show_success();
    void show_failure( QString err );

    //
    library *_ref_library;
    model_compile _model_compile;

    //
    QString _model_err;
    QFuture<bool> *_compile_future;
    QFutureWatcher<bool> *_compile_watcher;

    //
    QVBoxLayout *_vbox;
    QDialog *_progress_dialog;
};

#endif // VIEW_COMPILE_H

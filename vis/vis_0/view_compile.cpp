#include "view_compile.h"
#include "library.h"

//++++++++++++++++++++++++++++++++++
view_compile::view_compile( library* lib, QWidget *parent)
    : QWidget(parent), _ref_library( lib ), _model_compile( lib )
{

    //
    setWindowTitle("Compile Dataset");
    setWindowIcon(QIcon(QDir::currentPath() + "/../vis_0/data/MAPLE_logo_transparent.gif"));
    setFixedSize( 250, 100 );

    //
    init_view();
}
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void view_compile::init_view(){

    //
    _vbox = new QVBoxLayout;
    setLayout( _vbox );

    //
    QLabel *warning = new QLabel("WARNING: Dataset will be rebuilt if pre-existing...");
    QLabel *directions = new QLabel("Browse and open a .obsrv file:");
    QPushButton *ok = new QPushButton("Go");
    QPushButton *cancel = new QPushButton("Cancel");

    //
    connect(ok, SIGNAL(clicked()), this, SLOT(OnOkPressed()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(OnCancelPressed()));

    //
    QHBoxLayout *h1 = new QHBoxLayout;
    QHBoxLayout *h2 = new QHBoxLayout;
    QHBoxLayout *h3 = new QHBoxLayout;

    //
    h1->addWidget( warning );
    h2->addWidget( directions );
    h3->addWidget( ok );
    h3->addWidget( cancel );

    //
    _vbox->addLayout( h1 );
    _vbox->addLayout( h2 );
    _vbox->addLayout( h3 );

    //  Progress bar dialog.
    //
    _progress_dialog = new QDialog(0, Qt::CustomizeWindowHint|Qt::WindowTitleHint);
    _progress_dialog->setModal( true );
    _progress_dialog->setFixedSize( 300, 150 );
    _progress_dialog->setWindowTitle( "...Compiling Dataset...");

    //
    QLabel *progress_msg = new QLabel( "This may take a while." );

    //
    QProgressBar *bar = new QProgressBar( );
    bar->resize( 280, 40 );
    bar->setMinimum( 0 );
    bar->setMaximum( 0 );

    //
    QPushButton *compile_cancel_btn = new QPushButton("Cancel");
    connect(compile_cancel_btn, SIGNAL(clicked()), this, SLOT(cancel_compile()));

    //
    QVBoxLayout *vb = new QVBoxLayout;
    _progress_dialog->setLayout( vb );
    vb->addWidget( progress_msg );
    vb->addWidget( bar );
    vb->addWidget( compile_cancel_btn );
}
//++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++
void delay( int seconds ){

    //
    QTime dieTime = QTime::currentTime().addSecs( seconds );

    //
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
}
bool function_compile_model( model_compile *model, QString *err, QString base){

    //
    return model->compile(base,err);
}
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++

void view_compile::OnOkPressed(){

    //  Show the QFileDialog.
    //
    QString filename = QFileDialog::getOpenFileName( this, QString("Open FIle"), "", QString("Observe Files(*.obsrv)") );


    //  If null then they canceled.
    //
    if( filename == NULL ){

        //
        hide();

        //
        return;
    }

    //  Else, get the base path (remove the file ending).
    //
    QString path = filename.remove(".obsrv");

    //  Hide this view, show the progress view, then wait a bit before compiling.
    //
    hide();
    show_progress();
    delay(1);

    //  Compile for success.
    //
    _compile_watcher = new QFutureWatcher<bool>;
    _compile_future = new QFuture<bool>;

    //
    connect( _compile_watcher, SIGNAL(finished()), this, SLOT(compile_finished()) );

    //
    *_compile_future =  QtConcurrent::run( function_compile_model, &_model_compile, &_model_err, path );
    _compile_watcher->setFuture(*_compile_future);

}
void view_compile::OnCancelPressed(){ hide(); }
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
void view_compile::show_progress(){

    //
    _progress_dialog->show();

}
void view_compile::show_success(){

    //
    _progress_dialog->hide();

    //
    QMessageBox *mbox = new QMessageBox( QMessageBox::Information, QString("Success!"), QString("Successfully built dataset database.") );
    mbox->setModal(true);

    //
    mbox->setFixedSize( 300, 200 );

    //
    mbox->show();
}
void view_compile::show_failure( QString err ){

    //
    _progress_dialog->hide();

    //
    QMessageBox *mbox = new QMessageBox( QMessageBox::Critical, QString("Failure"), QString("Failed to build dataset database.\n%1").arg(err) );
    mbox->setModal(true);

    //
    mbox->setFixedSize( 300, 200 );

    //
    mbox->show();
}
void view_compile::compile_finished( ){

    //
    bool result = _compile_future->result();

    //  Success.
    //
    if( result )
        show_success();

    //  ...or failure.
    //
    else
        show_failure( _model_err );
}
void view_compile::cancel_compile(){

    //
    _compile_future->cancel();
    _compile_watcher->cancel();

    //
    _progress_dialog->hide();
}

//++++++++++++++++++++++++++++++++++

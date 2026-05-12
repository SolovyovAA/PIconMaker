#include "about_dialog.h"
#include "ui_about_dialog.h"

AboutDialog::AboutDialog( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::AboutDialog ){
    ui->setupUi(this);

    ui->l_build_ver->setText( "build ver.: " + qApp->applicationVersion() );
}

AboutDialog::~AboutDialog(){
    delete ui;
}

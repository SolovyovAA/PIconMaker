#include "icon_button.h"
#include "ui_icon_button.h"

#include <QIcon>

IconButton::IconButton(QSize size, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconButton)
{
    ui->setupUi(this);

    int w = size.width(), h = size.height();
    ui->l_size->setText( QString( "%1x%2" ).arg( w ).arg( h ) );

    if( w > 500 ){
        w = 80;
    } else if( w > 200 ){
        w = 60;
    } else if( w > 80 ){
        w = 80;
    } else if( w > 60 ){
        w = 60;
    }

    if( h > 500 ){
        h = 80;
    } else if( h > 200 ){
        h = 60;
    } else if( h > 80 ){
        h = 80;
    } else if( h > 60 ){
        h = 60;
    }

    ui->l_icon->setPixmap( QIcon( ":/icons/resources/icons/empty.png" ).pixmap( w, h ) );
}

IconButton::~IconButton(){
    delete ui;
}

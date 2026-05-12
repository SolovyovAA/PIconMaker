#include "scaled_widget.h"
#include "ui_scaled_widget.h"

#include <QIcon>

#include "ico_data.h"

ScaledWidget::ScaledWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScaledWidget){
    ui->setupUi(this);

    QIcon icon( ":/icons/resources/icons/empty.png" );
    ui->l_icon->setPixmap( icon.pixmap( 64, 64 ) );

    for( const auto &size : qAsConst( kIconSizes ) ){
        m_buttons.append( QSharedPointer< IconButton >( new IconButton( size, this ) ) );
        ui->layout_icon_gallery->addWidget( m_buttons.last().data() );
    }
}

ScaledWidget::~ScaledWidget(){
    delete ui;
}

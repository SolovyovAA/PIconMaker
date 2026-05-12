#include "scaled_widget.h"
#include "ui_scaled_widget.h"

#include <QIcon>
#include <QFileDialog>

#include "ico_data.h"

ScaledWidget::ScaledWidget(QWidget *parent) :
    AbstractWidget(parent),
    ui(new Ui::ScaledWidget){
    ui->setupUi(this);

    connect( this, &AbstractWidget::fromMainClearClicked, this, &ScaledWidget::onClearClicked );
    connect( this, &AbstractWidget::fromMainSaveClicked,  this, &ScaledWidget::onSaveClicked  );

    m_selectedId = -1;

    resetIcon();

    for( const auto &size : qAsConst( kIconSizes ) ){
        m_buttons.append( QSharedPointer< IconButton >( new IconButton( size, this ) ) );
        ui->layout_icon_gallery->addWidget( m_buttons.last().data() );

        connect( m_buttons.last().data(), &IconButton::selectionChanged, this, &ScaledWidget::onSelectionChanged );
        connect( m_buttons.last().data(), &IconButton::imageChanged, this, &ScaledWidget::checkButtonsAvaliable );
        connect( m_buttons.last().data(), &IconButton::showMessage, this, &AbstractWidget::showMessage );
    }

    connect( ui->btn_clear, &QPushButton::clicked, this, &ScaledWidget::onClearClicked );
    connect( ui->btn_save,  &QPushButton::clicked, this, &ScaledWidget::onSaveClicked  );

    setButtonEnabled( false );
}

ScaledWidget::~ScaledWidget(){
    delete ui;
}

void ScaledWidget::onClearClicked(){
    for( auto &btn : m_buttons ){
        btn->resetData();
    }
    resetIcon();
    m_selectedId = -1;

    setButtonEnabled( false );
}

void ScaledWidget::onSaveClicked(){
    QList< QImage > imgList;

    for( const auto &btn : qAsConst( m_buttons ) ){
        if( !btn->getImage().isNull() ){
            imgList.append( QImage( *(btn->getImage() ) ) );
        }
    }

    if( !imgList.isEmpty() ){
        QFileDialog saveDlg( this, tr( "Сохранение иконки..." ) );
        saveDlg.setAcceptMode(QFileDialog::AcceptSave);
        saveDlg.setNameFilter( tr( "ICON (*.ico)" ) );
        saveDlg.setDefaultSuffix( "ico" );
        if( saveDlg.exec() == QDialog::Accepted ){
            QString save = saveDlg.selectedFiles().value( 0 );
            emit saveIcon( save, imgList );
        }
    }
}

void ScaledWidget::onSelectionChanged( int id ){
    for( auto &btn : m_buttons ){
        if( btn->id() != id ){
            btn->setSelected( false );
        } else {
            m_selectedId = id;
            ui->l_icon->setPixmap( QPixmap::fromImage( *btn->getImage().data() ) );
            ui->l_icon_size->setText( QString( "%1x%2" ).arg( btn->getSize().width() ).arg( btn->getSize().height() ) );
        }
    }
}

void ScaledWidget::checkButtonsAvaliable( int lastChangedId ){
    bool isAvaliable = false;
    for( auto &btn : m_buttons ){
        isAvaliable |= !btn->getImage().isNull();
    }

    if( lastChangedId == m_selectedId ){
        resetIcon();
    }

    setButtonEnabled( isAvaliable );
}

void ScaledWidget::resetIcon(){
    QIcon icon( ":/icons/resources/icons/empty.png" );
    ui->l_icon->setPixmap( icon.pixmap( 64, 64 ) );

    ui->l_icon_size->setText( QString( "NxN" ) );
}

void ScaledWidget::setButtonEnabled( bool enabled ){
    ui->btn_save->setEnabled( enabled );
    ui->btn_clear->setEnabled( enabled );

    emit buttonsEnableStatusChanged( enabled );
}

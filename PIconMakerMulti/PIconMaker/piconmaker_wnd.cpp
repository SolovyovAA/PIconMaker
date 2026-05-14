#include "piconmaker_wnd.h"
#include "ui_piconmaker_wnd.h"

#include <qglobal.h>
#include <QMessageBox>

#include "ico_worker.h"

PIconMakerWnd::PIconMakerWnd( QWidget *parent )
    : QMainWindow( parent )
    , ui( new Ui::PIconMakerWnd ){
    ui->setupUi( this );

    m_btnGroup.addButton( ui->btn_listed, AppType::AT_Listed );
    m_btnGroup.addButton( ui->btn_scaled, AppType::AT_Scaled );

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    connect( &m_btnGroup, QOverload< int >::of( &QButtonGroup::idClicked ), this, &PIconMakerWnd::onBtnClicked );
#elif QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    connect( &m_btnGroup, QOverload< int >::of( &QButtonGroup::buttonClicked ), this, &PIconMakerWnd::onBtnClicked );
#endif

    ui->menubar->addAction( ui->act_about );
    connect( ui->act_about, &QAction::triggered, &m_aboutDlg, &AboutDialog::show );

    ui->menubar->addAction( ui->act_exit );
    connect( ui->act_exit, &QAction::triggered, this, &PIconMakerWnd::onExitClicked );

    processButtonsEnable( false );

    // TODO: check updates
}

PIconMakerWnd::~PIconMakerWnd(){
    delete ui;
}

void PIconMakerWnd::onBtnClicked( int pageIndex ){
    switch( pageIndex ){
    case AT_Listed:{
        m_mainWgt = new ListedWidget( this );
    }; break;
    case AT_Scaled:{
        m_mainWgt = new ScaledWidget( this );
        ui->act_open->setVisible( false );
    }; break;
    }
    setCentralWidget( m_mainWgt );
    connect( m_mainWgt, &AbstractWidget::buttonsEnableStatusChanged, this, &PIconMakerWnd::processButtonsEnable );
    connect( m_mainWgt, &AbstractWidget::saveIcon, this, &PIconMakerWnd::processSave );
    connect( m_mainWgt, &AbstractWidget::showMessage, ui->statusbar, &QStatusBar::showMessage );

    connect( ui->act_clear, &QAction::triggered, m_mainWgt, &AbstractWidget::fromMainClearClicked );
    connect( ui->act_save,  &QAction::triggered, m_mainWgt, &AbstractWidget::fromMainSaveClicked  );
    connect( ui->act_open,  &QAction::triggered, m_mainWgt, &AbstractWidget::fromMainOpenClicked  );
}

void PIconMakerWnd::onExitClicked(){
    QMessageBox exitDialog( QMessageBox::Icon::Question, tr( "Завершение работы" ), tr( "Вы уверены, что хотите выйти?" ), QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::Cancel, this );
    if( exitDialog.exec() == QMessageBox::StandardButton::Yes ){
        qApp->quit();
    }
}

void PIconMakerWnd::processButtonsEnable( bool enabled ){
    ui->act_clear->setEnabled( enabled );
    ui->act_save->setEnabled( enabled );
    ui->act_open->setEnabled( enabled );
}

void PIconMakerWnd::processSave( const QString &path, QList< QImage > images ){
    if( saveIco( path, images ) ){
        ui->statusbar->showMessage( tr( "Успешное сохранение иконки (%1)" ).arg( path ) );
    } else {
        ui->statusbar->showMessage( tr( "Во время сохранения возникли ошибки" ) );
    }
}


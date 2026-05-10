#include "listed_widget.h"
#include "ui_listed_widget.h"

#include <QFileDialog>
#include <QStringList>
#include <QIcon>
#include <QPixmap>

ListedWidget::ListedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListedWidget){
    ui->setupUi(this);

    connect( ui->btn_add,       &QPushButton::clicked, this, &ListedWidget::onLoadClicked );
    connect( ui->btn_remove,    &QPushButton::clicked, this, &ListedWidget::onSaveClicked );
    connect( ui->btn_clear,     &QPushButton::clicked, this, &ListedWidget::onClearClicked );

    connect( ui->w_iconsList, &QListWidget::currentItemChanged, this, &ListedWidget::onListIndexChanged );

}

ListedWidget::~ListedWidget(){
    delete ui;
}

void ListedWidget::onLoadClicked(){
    QFileDialog loadDlg( this, tr( "Загрузить картинки" ) );
    loadDlg.setFileMode( QFileDialog::FileMode::ExistingFiles );
    loadDlg.setNameFilter( "Доступные типы картинок (*.png, *.bmp, *.jpg)" ); // TODO: fix
    loadDlg.setNameFilters( { "*.png", "*.bmp", "*.ico" } );

    if( loadDlg.exec() ){
        QStringList pathes = loadDlg.selectedFiles();
        for( const auto &file : qAsConst( pathes ) ){
            if( !loadByPath( file ) ){
                // TODO: inc
            }
        }
    }
    // TODO: fail signal
}

void ListedWidget::onSaveClicked(){

}

void ListedWidget::onClearClicked(){
    if( !m_imagesList.isEmpty() ){
        m_imagesList.clear();
        ui->w_iconsList->clear();
    }
}

void ListedWidget::onListIndexChanged( QListWidgetItem *item ){
    QSize curRowSize = m_imagesList.at( ui->w_iconsList->currentRow() ).size();
    ui->w_icon->setPixmap( QPixmap( item->icon().pixmap( curRowSize ) ) );
}

bool ListedWidget::loadByPath( const QString &path ){
    QImage tmp( path );
    if( tmp.width() == tmp.height() && tmp.width() <= 1024 ){
        m_imagesList.append( tmp );

        QPixmap tmpPxMp;
        tmpPxMp.convertFromImage( tmp );
        QListWidgetItem *item = new QListWidgetItem( QIcon( tmpPxMp ), QString( "%1x%2" ).arg( tmp.width() ).arg( tmp.height() ) );
        item->setSizeHint( QSize( ui->w_iconsList->viewport()->width(), 120 ) );
        ui->w_iconsList->addItem( item );

        return true;
    }

    return false;
}

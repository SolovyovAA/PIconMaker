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

    connect( ui->btn_add,    &QPushButton::clicked, this, &ListedWidget::onLoadClicked   );
    connect( ui->btn_remove, &QPushButton::clicked, this, &ListedWidget::onRemoveClicked );
    connect( ui->btn_clear,  &QPushButton::clicked, this, &ListedWidget::onClearClicked  );
    connect( ui->btn_save,   &QPushButton::clicked, this, &ListedWidget::onSaveClicked   );

    connect( ui->w_iconsList, &QListWidget::currentItemChanged, this, &ListedWidget::onListIndexChanged );

    setButtonEnabled( ui->w_iconsList->count() > 0 );
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

        if( ui->w_iconsList->count() > 0 ){
            ui->w_iconsList->setCurrentItem( ui->w_iconsList->item( 0 ) );
        }

        setButtonEnabled( ui->w_iconsList->count() > 0 );
    }
    // TODO: fail signal
}

void ListedWidget::onSaveClicked(){

}

void ListedWidget::onRemoveClicked(){
    QListWidgetItem *current = ui->w_iconsList->currentItem();
    if (current) {
        int row = ui->w_iconsList->row(current);
        ui->w_iconsList->takeItem(row);
        delete current;
    }

    if( ui->w_iconsList->count() == 0 ){
        ui->w_icon->clear();
        setButtonEnabled( false );
    }
}

void ListedWidget::onClearClicked(){
    if( ui->w_iconsList->count() > 0 ){
        ui->w_iconsList->clear();

        ui->w_icon->clear();
        setButtonEnabled( false );
    }
}

void ListedWidget::onListIndexChanged( QListWidgetItem *item ){
    if( item ){
        QSize curRowSize = item->data( Qt::UserRole ).value< QImage >().size();
        ui->w_icon->setPixmap( QPixmap( item->icon().pixmap( curRowSize ) ) );
    }
}

bool ListedWidget::loadByPath( const QString &path ){
    QImage tmp( path );
    if( tmp.width() == tmp.height() && tmp.width() <= 1024 ){
        QPixmap tmpPxMp;
        tmpPxMp.convertFromImage( tmp );
        QListWidgetItem *item = new QListWidgetItem();//( QIcon( tmpPxMp ), QString( "%1x%2" ).arg( tmp.width() ).arg( tmp.height() ) );
        item->setIcon( QIcon( QPixmap::fromImage( tmp ) ) );
        item->setData( Qt::UserRole, QVariant::fromValue( tmp ) );
        item->setText( QString( "%1x%2" ).arg( tmp.width() ).arg( tmp.height() ) );
        item->setSizeHint( QSize( ui->w_iconsList->viewport()->width() - 30, 120 ) );
        ui->w_iconsList->addItem( item );

        return true;
    }

    return false;
}

void ListedWidget::setButtonEnabled( bool enabled ){
    ui->btn_save->setEnabled( enabled );
    ui->btn_remove->setEnabled( enabled );
    ui->btn_clear->setEnabled( enabled );

    emit buttonsEnableStatusChanged( enabled );
}

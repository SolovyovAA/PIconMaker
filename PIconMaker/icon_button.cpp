#include "icon_button.h"
#include "ui_icon_button.h"

#include <QIcon>
#include <QMouseEvent>
#include <QFileDialog>

IconButton::IconButton(QSize size, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconButton)
{
    ui->setupUi(this);

    m_id = size.width();
    m_originalSize = size;
    m_showSize = size;
    ui->l_size->setText( QString( "%1x%2" ).arg( size.width() ).arg( size.height() ) );

    // if( m_showSize.width() > 500 ){
    //     m_showSize.setWidth( 85 );
    // } else if( m_showSize.width() > 200 ){
    //     m_showSize.setWidth( 80 );
    // } else if( m_showSize.width() > 100 ){
    //     m_showSize.setWidth( 70 );
    // } else if( m_showSize.width() > 80 ){
    //     m_showSize.setWidth( 60 );
    // } else if( m_showSize.width() > 60 ){
    //     m_showSize.setWidth( 50 );
    // }

    // if( m_showSize.height() > 500 ){
    //     m_showSize.setHeight( 85 );
    // } else if( m_showSize.height() > 200 ){
    //     m_showSize.setHeight( 80 );
    // } else if( m_showSize.height() > 100 ){
    //     m_showSize.setHeight( 70 );
    // } else if( m_showSize.height() > 80 ){
    //     m_showSize.setHeight( 60 );
    // } else if( m_showSize.height() > 60 ){
    //     m_showSize.setHeight( 50 );
    // }
    if( m_showSize.width() > 85 ){
        m_showSize.setWidth( 85 );
    }
    if( m_showSize.height() > 85 ){
        m_showSize.setHeight( 85 );
    }

    resetData();
}

IconButton::~IconButton(){
    delete ui;
}

void IconButton::setSelected( bool selected ){
    if( selected ){
        ui->frame->setLineWidth( 1 );
        emit selectionChanged( m_id );
    } else {
        ui->frame->setLineWidth( 0 );
    }
}

void IconButton::mousePressEvent( QMouseEvent *event ){
    if( event->button() == Qt::MouseButton::LeftButton ){
        if( !m_image ){
            loadDialog();
        }
        if( m_image ){
            setSelected( true );
        }
    } else if( m_image && event->button() == Qt::MouseButton::RightButton ){
        resetData();
        if( ui->frame->lineWidth() != 0 ){
            emit imageChanged( m_id );
        }
    }
}

void IconButton::mouseDoubleClickEvent( QMouseEvent *event ){
    if( m_image && event->button() == Qt::MouseButton::LeftButton ){
        loadDialog();
        setSelected( true );
    }
}

void IconButton::resetData(){
    if( m_image ){
        m_image.clear();
        m_image = Q_NULLPTR;

        setSelected( false );
    }

    ui->l_icon->setPixmap( QIcon( ":/icons/resources/icons/empty.png" ).pixmap( m_showSize.width(), m_showSize.height() ) );
}

void IconButton::loadDialog(){
    QFileDialog loadDlg( this, tr( "Загрузить картинку" ) );
    loadDlg.setFileMode( QFileDialog::FileMode::ExistingFile );
    loadDlg.setNameFilter( tr( "Доступные типы картинок (*.png *.bmp *.jpg)" ) );

    if( loadDlg.exec() == QFileDialog::Accepted ){
        QStringList pathes = loadDlg.selectedFiles();
        for( const auto &file : qAsConst( pathes ) ){
            if( !loadByPath( file ) ){
                emit showMessage( tr( "Во время загрузки изображения (%1) возникла ошибка" ).arg( file ) );
            } else {
                emit imageChanged( m_id );
            }

        }
    }
}

bool IconButton::loadByPath( const QString &path ){
    QImage tmp( path );
    if( tmp.width() == tmp.height() && tmp.width() <= 1024 ){
        m_image.clear();
        if( tmp.size() != m_originalSize ){
            tmp = tmp.scaled( m_originalSize, Qt::KeepAspectRatio, Qt::SmoothTransformation );
        }

        m_image.reset( new QImage( tmp ) );
        ui->l_icon->setPixmap( QIcon( path ).pixmap( m_showSize.width(), m_showSize.height() ) );
        return true;
    }

    return false;
}

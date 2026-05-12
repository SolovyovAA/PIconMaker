#ifndef ICON_BUTTON_H
#define ICON_BUTTON_H

#include <QWidget>
#include <QSize>
#include <QImage>
#include <QSharedPointer>

namespace Ui {
class IconButton;
}

class IconButton : public QWidget {
    Q_OBJECT

public:
    explicit IconButton( QSize size, QWidget *parent = nullptr );
    ~IconButton();

    int id() { return m_id; }
    void setSelected( bool selected );

    QSharedPointer< QImage > getImage() { return m_image; }
    QSize getSize() { return m_originalSize; }

    void resetData();

    Q_SIGNAL void selectionChanged( int );
    Q_SIGNAL void imageChanged( int );

    Q_SIGNAL void showMessage( const QString &message, int tm = 0 );

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void loadDialog();
    bool loadByPath( const QString &path );

    Ui::IconButton *ui;

    int m_id;
    QSharedPointer< QImage > m_image;
    QSize m_showSize, m_originalSize;
};

#endif // ICON_BUTTON_H

#ifndef ABSTRACT_WIDGET_H
#define ABSTRACT_WIDGET_H

#include <QWidget>
#include <QList>
#include <QImage>

class AbstractWidget : public QWidget {
    Q_OBJECT
public:
    AbstractWidget( QWidget *wgt ) : QWidget( wgt ){};
    ~AbstractWidget() {}

signals:
    void buttonsEnableStatusChanged( bool enabled );
    void fromMainClearClicked();
    void fromMainSaveClicked();
    void fromMainOpenClicked();

    void saveIcon( const QString &path, QList< QImage > images );

    void showMessage( const QString &message, int timeout = 0 );
};

#endif // ABSTRACT_WIDGET_H

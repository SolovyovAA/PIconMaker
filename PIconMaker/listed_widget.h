#ifndef LISTED_WIDGET_H
#define LISTED_WIDGET_H

// #include <QWidget>
#include "abstract_widget.h"
//#include <QList>
#include <QImage>
#include <QString>

#include <QListWidget>
#include <QListWidgetItem>

namespace Ui {
class ListedWidget;
}

class ListedWidget : public AbstractWidget {
    Q_OBJECT

public:
    explicit ListedWidget(QWidget *parent = nullptr);
    ~ListedWidget();

    // Q_SIGNAL void buttonsEnableStatusChanged( bool enabled );

private:
    Q_SLOT void onLoadClicked();
    Q_SLOT void onSaveClicked();
    Q_SLOT void onRemoveClicked();
    Q_SLOT void onClearClicked();

    Q_SLOT void onListIndexChanged( QListWidgetItem *item );

    bool loadByPath( const QString &path );
    void setButtonEnabled( bool enabled );

    Ui::ListedWidget *ui;

//    QList< QImage > m_imagesList;
};

#endif // LISTED_WIDGET_H

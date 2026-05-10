#ifndef LISTED_WIDGET_H
#define LISTED_WIDGET_H

#include <QWidget>
#include <QList>
#include <QImage>
#include <QString>

#include <QListWidget>
#include <QListWidgetItem>

namespace Ui {
class ListedWidget;
}

class ListedWidget : public QWidget {
    Q_OBJECT

public:
    explicit ListedWidget(QWidget *parent = nullptr);
    ~ListedWidget();

private:
    Q_SLOT void onLoadClicked();
    Q_SLOT void onSaveClicked();
    Q_SLOT void onClearClicked();

    Q_SLOT void onListIndexChanged( QListWidgetItem *item );

    bool loadByPath( const QString &path );

    Ui::ListedWidget *ui;

    QList< QImage > m_imagesList;
};

#endif // LISTED_WIDGET_H

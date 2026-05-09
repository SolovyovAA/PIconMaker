#ifndef LISTED_WIDGET_H
#define LISTED_WIDGET_H

#include <QWidget>

namespace Ui {
class ListedWidget;
}

class ListedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListedWidget(QWidget *parent = nullptr);
    ~ListedWidget();

private:
    Ui::ListedWidget *ui;
};

#endif // LISTED_WIDGET_H

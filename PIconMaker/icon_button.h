#ifndef ICON_BUTTON_H
#define ICON_BUTTON_H

#include <QWidget>
#include <QSize>

namespace Ui {
class IconButton;
}

class IconButton : public QWidget {
    Q_OBJECT

public:
    explicit IconButton( QSize size, QWidget *parent = nullptr );
    ~IconButton();

private:
    Ui::IconButton *ui;
};

#endif // ICON_BUTTON_H

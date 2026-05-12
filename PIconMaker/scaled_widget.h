#ifndef SCALED_WIDGET_H
#define SCALED_WIDGET_H

#include <QWidget>
#include <QList>
#include <QSharedPointer>

#include "icon_button.h"

namespace Ui {
class ScaledWidget;
}

class ScaledWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScaledWidget(QWidget *parent = nullptr);
    ~ScaledWidget();

private:
    Ui::ScaledWidget *ui;

    QList< QSharedPointer< IconButton > > m_buttons;
};

#endif // SCALED_WIDGET_H

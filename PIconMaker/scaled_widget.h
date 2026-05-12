#ifndef SCALED_WIDGET_H
#define SCALED_WIDGET_H

// #include <QWidget>
#include "abstract_widget.h"
#include <QList>
#include <QSharedPointer>

#include "icon_button.h"

namespace Ui {
class ScaledWidget;
}

class ScaledWidget : public AbstractWidget {
    Q_OBJECT

public:
    explicit ScaledWidget(QWidget *parent = nullptr);
    ~ScaledWidget();

    // Q_SIGNAL void buttonsEnableStatusChanged( bool enabled );

private:    
    Q_SLOT void onClearClicked();
    Q_SLOT void onSaveClicked();

    Q_SLOT void onSelectionChanged( int id );
    Q_SLOT void checkButtonsAvaliable( int lastChangedId );

    void resetIcon();
    void setButtonEnabled( bool enabled );

    Ui::ScaledWidget *ui;

    QList< QSharedPointer< IconButton > > m_buttons;
    int m_selectedId;
};

#endif // SCALED_WIDGET_H

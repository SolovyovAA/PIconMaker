#ifndef PICONMAKERWND_H
#define PICONMAKERWND_H

#include <QMainWindow>
#include <QButtonGroup>

#include <QList>
#include <QImage>

#include "abstract_widget.h"
#include "about_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PIconMakerWnd; }
QT_END_NAMESPACE

class PIconMakerWnd : public QMainWindow
{
    Q_OBJECT

public:
    PIconMakerWnd(QWidget *parent = nullptr);
    ~PIconMakerWnd();

private:
    enum AppType {
        AT_Listed,
        AT_Scaled,
    };

    Q_SLOT void onBtnClicked(int pageIndex );
    Q_SLOT void onExitClicked();

    Q_SLOT void processButtonsEnable( bool enabled );
    Q_SLOT void processSave( const QString &path, QList< QImage > images );

    Ui::PIconMakerWnd *ui;

    QButtonGroup m_btnGroup;
    AboutDialog m_aboutDlg;

    AbstractWidget *m_mainWgt;
};
#endif // PICONMAKERWND_H

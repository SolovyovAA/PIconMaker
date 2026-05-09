#ifndef PICONMAKERWND_H
#define PICONMAKERWND_H

#include <QMainWindow>

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
    Ui::PIconMakerWnd *ui;
};
#endif // PICONMAKERWND_H

#include "piconmaker_wnd.h"
#include "ui_piconmaker_wnd.h"

PIconMakerWnd::PIconMakerWnd(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PIconMakerWnd){
    ui->setupUi(this);
}

PIconMakerWnd::~PIconMakerWnd(){
    delete ui;
}


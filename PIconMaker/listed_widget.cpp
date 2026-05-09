#include "listed_widget.h"
#include "ui_listed_widget.h"

ListedWidget::ListedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListedWidget)
{
    ui->setupUi(this);
}

ListedWidget::~ListedWidget()
{
    delete ui;
}

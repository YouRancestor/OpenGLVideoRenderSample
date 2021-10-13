#define ssize_t size_t
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    on_pushButton_clicked();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->widget->setInput(ui->lineEdit->text());
    ui->widget->play();
}

void Widget::on_pushButton_2_clicked()
{
    ui->widget->pause();
}

void Widget::on_pushButton_3_clicked()
{
    ui->widget->stop();
}

void Widget::on_pushButton_4_clicked()
{
    double angle = ui->doubleSpinBox->value();
    ui->widget->setRotate(angle);
}

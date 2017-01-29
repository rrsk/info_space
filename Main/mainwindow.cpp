#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*QDir dir;

    foreach (QFileInfo var,dir.drives())
    {
        ui->comboBox->addItem(var.absoluteFilePath());
    }

    QDir dir2("C:/Users/RISHAB/OneDrive/Documents/qt");

    foreach (QFileInfo var, dir.entryInfoList())
    {
        ui->listWidget->addItem(var.absoluteFilePath());
    }
    */


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString s = ui->lineEdit->text();

    hide();
    sp = new Space(this);
    sp->setData(s);
    sp->show();

}

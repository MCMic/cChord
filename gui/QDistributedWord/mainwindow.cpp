#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "distributedtextedit.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    cout << "COUCOU" << endl;
    ui->verticalLayout->addWidget(new DistributedTextEdit(ui->input_ip->text().toStdString(),ui->input_port->text().toInt()));
}

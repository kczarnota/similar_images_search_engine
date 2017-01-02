#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

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

void MainWindow::on_loadDatabaseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    ui->databaseEdit->setText(fileName);
}

void MainWindow::on_loadImagesButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    ui->imagesEdit->setText(fileName);
}

void MainWindow::on_loadDictionaryButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    ui->dictionaryEdit->setText(fileName);
}

void MainWindow::radioBtnSelected()
{
    QRadioButton * rb = (QRadioButton*)QObject::sender();
    ui->label->setText(rb->text());
}

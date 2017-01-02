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
    this->databasePath = fileName.toUtf8().constData();
    ui->databaseEdit->setText(fileName);
}

void MainWindow::on_loadImagesButton_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this, "Open file", QDir::homePath());
    this->imagesPath = fileName.toUtf8().constData();
    ui->imagesEdit->setText(fileName);
}

void MainWindow::on_loadDictionaryButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    this->dictionaryPath = fileName.toUtf8().constData();
    ui->dictionaryEdit->setText(fileName);
}

void MainWindow::radioBtnSelected()
{
    QRadioButton * rb = (QRadioButton*)QObject::sender();
    this->selectedDescriptor = rb->text().toUtf8().constData();
    ui->label->setText(rb->text());
}

void MainWindow::prepareBtnSelected()
{
    QRadioButton * rb = (QRadioButton*)QObject::sender();
    ui->label->setText(rb->text());
    
    int dictionarySize = atoi(ui->dictionarySizeEdit->text().toUtf8().constData());
    if(dictionarySize == 0)
	dictionarySize = 1000;

    float siftWeight = atof(ui->siftWeightEdit->text().toUtf8().constData());
float lbpWeight = atof(ui->lbpWeightEdit->text().toUtf8().constData());
float hueWeight = atof(ui->hueWeightEdit->text().toUtf8().constData());

std::cout << ui->siftWeightEdit->text().toUtf8().constData() << " " << ui->lbpWeightEdit->text().toUtf8().constData() << " " << ui->hueWeightEdit->text().toUtf8().constData() << std::endl;
std::cout << siftWeight << " " << lbpWeight << " " << hueWeight << std::endl;

	string pathToDatabase = ui->databaseEdit->text().toUtf8().constData();
std::cout << pathToDatabase << std::endl;

    string pathToImages = ui->imagesEdit->text().toUtf8().constData();
std::cout << pathToImages << std::endl;

    string pathToDictionary = ui->dictionaryEdit->text().toUtf8().constData();
std::cout << pathToDictionary << std::endl;

    string databaseName = ui->databaseEdit->text().toUtf8().constData();
    //BOW bow();
    //bow.init();
}

void MainWindow::queryBtnSelected()
{
    QRadioButton * rb = (QRadioButton*)QObject::sender();
    ui->label->setText(rb->text());
}


void MainWindow::testBtnSelected()
{
    QRadioButton * rb = (QRadioButton*)QObject::sender();
    ui->label->setText(rb->text());
}

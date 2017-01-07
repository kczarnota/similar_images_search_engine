#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setViewMode(QListWidget::IconMode);
    //ui->listWidget->selectionMode();
    ui->listWidget->setIconSize(QSize(200,200));
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    ui->listWidget->setGridSize(QSize(220, 225));
    ui->listWidget->setMovement(QListView::Static);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bow;
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


void MainWindow::radioBtnSelected()
{
    QRadioButton * rb = (QRadioButton*)QObject::sender();
    this->selectedDescriptor = rb->text().toUtf8().constData();
    cout << this->selectedDescriptor << endl;
}

void MainWindow::prepareBtnSelected()
{
    QRadioButton * rb = (QRadioButton*)QObject::sender();

    if(!checkPreparation())
        return;

    int dictionarySize = atoi(ui->dictionarySizeEdit->text().toUtf8().constData());
    if(dictionarySize == 0)
	    dictionarySize = 1000;

    double siftWeight = ui->siftWeightEdit->text().toDouble();
    double lbpWeight = ui->lbpWeightEdit->text().toDouble();
    double hueWeight = ui->hueWeightEdit->text().toDouble();
    string pathToDatabase = ui->databaseEdit->text().toUtf8().constData();
    string pathToImages = ui->imagesEdit->text().toUtf8().constData();
    string databaseName = BOW::getNLastPathSegments(pathToDatabase, 1);

    QList<string> images = findAllImages();
    cout << images.count() << endl;
    for(int i = 0; i < images.count(); ++i)
    {
        QString fileName = QString::fromStdString(images.at(i));
        ui->listWidget->addItem(new QListWidgetItem(QIcon(fileName), QString::fromStdString(BOW::getNLastPathSegments(images.at(i), 2))));
    }

    this->bow = new BOW(dictionarySize, pathToImages, databaseName, this->selectedDescriptor, siftWeight, lbpWeight, hueWeight);

    if(!this->bow->isDictionaryReady())
        return;

    this->bow->init();

    if(!bow->isDatabaseReady())
        return;

    readyForQuery = true;
    cout << "End of preparation" << endl;
}

void MainWindow::queryBtnSelected()
{
    if(!checkQuery())
        return;

    QListWidgetItem * it = ui->listWidget->item(0);
    cout << "Image name " << it->text().toUtf8().constData() << endl;
    QString selectedItem = ui->imagesEdit->text() + "/" + ui->listWidget->currentItem()->text();
    ImagesWindow * images = new ImagesWindow(bow, selectedItem, ui->returnImagesEdit->text().toInt());
    images->statusBar()->setSizeGripEnabled(false);
    images->show();
}

void MainWindow::testBtnSelected()
{
    TestWindow * testWindow = new TestWindow(bow, ui->imagesEdit->text().toUtf8().constData());
    testWindow->show();
}

QList<string> MainWindow::findAllImages()
{
    path p(ui->imagesEdit->text().toUtf8().constData());
    recursive_directory_iterator dir(p), end;

    QList<string> list;
    while (dir != end)
    {
        file_status fs = status(dir->path());
        if (!is_directory(fs))
        {
            string s = dir->path().string();
            list.append(s);
        }

        ++dir;
    }

    return list;
}

bool MainWindow::checkPreparation()
{
    string msg = "";
    string databaseName = this->ui->databaseEdit->text().toUtf8().constData();
    string imagesPath = this->ui->imagesEdit->text().toUtf8().constData();
    string dictionarySize = this->ui->dictionarySizeEdit->text().toUtf8().constData();

    if(databaseName == "")
        msg = "Please provide name of database to create or path to existing one";
    else if(imagesPath == "")
        msg = "Please provide path to images";
    else if(dictionarySize == "")
        msg = "Please provide dictionary size";
    else if(selectedDescriptor == "")
        msg = "Please select one of descriptors";

    if(msg != "")
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Warning", QString::fromStdString(msg));
        messageBox.setFixedSize(500, 200);
        return false;
    }
    else
    {
        return true;
    }
}

bool MainWindow::checkQuery()
{
    string msg = "";
    double siftWeight = ui->siftWeightEdit->text().toDouble();
    double lbpWeight = ui->lbpWeightEdit->text().toDouble();
    double hueWeight = ui->hueWeightEdit->text().toDouble();

    if(!readyForQuery)
    {
        msg = "Please prepare dictionary and database first";
    }
    else if(ui->listWidget->currentItem() == nullptr)
        msg = "Please select image to query";
    else if(ui->returnImagesEdit->text().toInt() < 1 || ui->returnImagesEdit->text().toInt() > 101)
        msg = "Please provide image number to return(between 1 and 100)";
    else if(selectedDescriptor == "SIFT and LBP" || selectedDescriptor == "SIFT and OC-LBP" || selectedDescriptor == "HOG and LBP" )
    {
        if(siftWeight + lbpWeight != 1)
            msg = "Please provide correct weights for SIFT/HOG and LBP/OC-LBP(sum must be 1)";
        else
        {
            bow->setSIFTWeight(siftWeight);
            bow->setLBPWeight(lbpWeight);
        }
    }
    else if(selectedDescriptor == "SIFT, LBP, HUE" || selectedDescriptor == "SIFT, OC-LBP, HUE" )
    {
        if(siftWeight + lbpWeight + hueWeight != 1)
        {
            msg = "Please provide correct weights for SIFT/HOG and LBP/OC-LBP and HUE(sum must be 1)";
        } else
        {
            bow->setSIFTWeight(siftWeight);
            bow->setLBPWeight(lbpWeight);
            bow->setHUEWeight(hueWeight);
        }
    }

    if(msg != "")
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Warning", QString::fromStdString(msg));
        messageBox.setFixedSize(500, 200);
        return false;
    }
    else
    {
        return true;
    }
}

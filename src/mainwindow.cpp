#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

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
    
    int dictionarySize = atoi(ui->dictionarySizeEdit->text().toUtf8().constData());
    if(dictionarySize == 0)
	    dictionarySize = 1000;

    float siftWeight = ui->siftWeightEdit->text().toFloat();
    float lbpWeight = ui->lbpWeightEdit->text().toFloat();
    float hueWeight = ui->hueWeightEdit->text().toFloat();
    string pathToDatabase = ui->databaseEdit->text().toUtf8().constData();
    string pathToImages = ui->imagesEdit->text().toUtf8().constData();
    string databaseName = ui->databaseEdit->text().toUtf8().constData();

    QList<string> images = findAllImages();
    cout << images.count() << endl;
    for(int i = 0; i < images.count(); ++i)
    {
        QString fileName = QString::fromStdString(images.at(i));
        ui->listWidget->addItem(new QListWidgetItem(QIcon(fileName), QString::fromStdString(BOW::getLastTwoPathSegments(images.at(i)))));
    }

    this->bow = new BOW(dictionarySize, pathToImages, pathToDatabase, this->selectedDescriptor);
    this->bow->init();
    cout << "End of preparation" << endl;
}

void MainWindow::queryBtnSelected()
{
    QRadioButton *rb = (QRadioButton *) QObject::sender();

    QListWidgetItem * it = ui->listWidget->item(0);
    cout << "Image name " << it->text().toUtf8().constData() << endl;
    QString selectedItem = ui->imagesEdit->text() + "/" + ui->listWidget->currentItem()->text();
    ImagesWindow * images = new ImagesWindow(bow, selectedItem, ui->returnImagesEdit->text().toInt());
    images->statusBar()->setSizeGripEnabled(false);
    images->show();
}

void MainWindow::testBtnSelected()
{
    QRadioButton * rb = (QRadioButton*)QObject::sender();
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
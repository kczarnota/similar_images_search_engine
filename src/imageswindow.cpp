#include "imageswindow.h"
#include "ui_imageswindow.h"

ImagesWindow::ImagesWindow(BOW * b, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImagesWindow)
{
    ui->setupUi(this);
    bow = b;
    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->selectionMode();
    ui->listWidget->setIconSize(QSize(200,200));
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    QThread* thread = new QThread;
    Worker* worker = new Worker(bow);
    worker->moveToThread(thread);
    qRegisterMetaType< QList<QString> >( "QList<QString>" );
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(worker, SIGNAL(giveData(QList<QString>)), this, SLOT(getData(QList<QString>)));
    thread->start();
}

ImagesWindow::~ImagesWindow()
{
    delete ui;
}

void ImagesWindow::getData(QList<QString> list)
{
    for(int i = 0; i < list.size(); ++i)
    {
        ui->listWidget->addItem(new QListWidgetItem(QIcon(list.at(i)), ""));
    }
}

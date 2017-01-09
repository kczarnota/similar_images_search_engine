#include "TestWindow.hpp"
#include "ui_testwindow.h"

TestWindow::TestWindow(BOW * bow, string pathToImages, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    shouldStop = new bool(false);
    int all = BOW::countFiles(pathToImages);
    progress = new QProgressDialog("Processing queries...", "Abort action", 0, all);
    QThread* thread = new QThread;
    TestWorker* worker = new TestWorker(bow, pathToImages, shouldStop);
    worker->moveToThread(thread);
    qRegisterMetaType< QList<QString> >( "QList<QString>" );
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(worker, SIGNAL(giveData(QList<QString>)), this, SLOT(getData(QList<QString>)));
    connect(worker, SIGNAL(tick()), this, SLOT(tick()));
    connect(progress, SIGNAL(canceled()), this, SLOT(wasCanceled()));

    thread->start();
}

TestWindow::~TestWindow()
{
    delete ui;
    //if(progress != nullptr)
    delete progress;
    delete shouldStop;
}

void TestWindow::getData(QList<QString> list)
{
    string firstItem = list.at(0).toUtf8().constData();
    if(firstItem == "Process Canceled")
    {
        ui->label->setStyleSheet("QLabel { color : red; }");
        ui->label->setText("Process was canceled. Please close this window and start again.");
    }
    else
    {
        ui->precision10->setText(list.at(0));
        ui->recall10->setText(list.at(1));
        ui->precision20->setText(list.at(2));
        ui->recall20->setText(list.at(3));
        ui->precision30->setText(list.at(4));
        ui->recall30->setText(list.at(5));
        ui->precision40->setText(list.at(6));
        ui->recall40->setText(list.at(7));
        ui->precision50->setText(list.at(8));
        ui->recall50->setText(list.at(9));
        ui->precision60->setText(list.at(10));
        ui->recall60->setText(list.at(11));
        ui->precision70->setText(list.at(12));
        ui->recall70->setText(list.at(13));
        ui->precision80->setText(list.at(14));
        ui->recall80->setText(list.at(15));
        ui->precision90->setText(list.at(16));
        ui->recall90->setText(list.at(17));
        ui->precisionA->setText(list.at(18));
        ui->recallA->setText(list.at(19));
    }

    //delete progress;
}

void TestWindow::tick()
{
    progress->setValue(++processedImages);
}

void TestWindow::wasCanceled()
{
    *this->shouldStop = true;
}

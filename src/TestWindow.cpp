#include "TestWindow.hpp"
#include "ui_testwindow.h"

TestWindow::TestWindow(BOW * bow, string pathToImages, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    shouldStop = new bool(false);
    int all = BOW::countFiles(pathToImages);
    progress = new QProgressDialog("Processing queries...", "Abort action", 0, all, this);
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
    delete progress;
    delete shouldStop;
}

void TestWindow::getData(QList<QString> list)
{
    ui->label->setText(list.at(0));
}

void TestWindow::tick()
{
    progress->setValue(++processedImages);
}

void TestWindow::wasCanceled()
{
    *this->shouldStop = true;
}

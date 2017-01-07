#include "imageswindow.h"
#include "ui_imageswindow.h"

ImagesWindow::ImagesWindow(BOW * b, QString selectedImage, int nImgs, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImagesWindow)
{
    ui->setupUi(this);
    bow = b;
    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->selectionMode();
    ui->listWidget->setIconSize(QSize(200,200));
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    ui->listWidget->setGridSize(QSize(220, 225));
    ui->listWidget->setMovement(QListView::Static);

    QThread* thread = new QThread;
    QueryWorker* worker = new QueryWorker(bow, selectedImage, nImgs);
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
    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        delete ui->listWidget->item(i);
    }
}

void ImagesWindow::getData(QList<QString> list)
{
    QIcon ic(list.at(0));
    QSize size = ic.availableSizes()[0];
    cout << size.width() << " " << size.height() << endl;

    ui->queryImageLabel->setPixmap(QPixmap(list.at(0)).scaled(150, 150, Qt::KeepAspectRatio));
    string firstItem = BOW::getNLastPathSegments(list.at(0).toUtf8().constData(), 2);
    ui->queryImageName->setText(QString::fromStdString(firstItem));
    for(int i = 1; i < list.size() - 2; ++i)
    {
        string l = BOW::getNLastPathSegments(list.at(i).toUtf8().constData(), 2);
        ui->listWidget->addItem(new QListWidgetItem(QIcon(list.at(i)), QString::fromStdString(l)));
    }

    ui->precisionText->setText(list.at(list.count() - 2));
    ui->recallText->setText(list.at(list.count() - 1));
    //cout << "Precision " << list.at(list.count() - 2).toUtf8().constData() << endl;
    //cout << "Recall " << list.at(list.count() - 1).toUtf8().constData() << endl;
}
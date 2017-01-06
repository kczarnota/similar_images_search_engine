#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <chrono>
#include <thread>
#include "src/Model/BOW.hpp"

class Worker : public QObject {
    Q_OBJECT

public:
    Worker(BOW * b, QString selectedItem, int nImgs);
    ~Worker();
    void showManyImages(char* title, int nArgs, IplImage ** images);

public slots:
    void process();

signals:
    void finished();
    void giveData(QList<QString> str);
    void error(QString err);

private:
    BOW * bow;
    QString selectedItem;
    int numberOfImagesToDisplay;
};

#endif // WORKER_H

#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <chrono>
#include <thread>
#include "src/Model/BOW.hpp"

class QueryWorker : public QObject {
    Q_OBJECT

public:
    QueryWorker(BOW * b, QString selectedItem, int nImgs);
    ~QueryWorker();

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

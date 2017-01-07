#ifndef BAGOFWORDS_TESTWORKER_HPP
#define BAGOFWORDS_TESTWORKER_HPP

#include <QObject>
#include <chrono>
#include <thread>
#include <QtWidgets/QProgressDialog>
#include "src/Model/BOW.hpp"

class TestWorker : public QObject {
Q_OBJECT

public:
    TestWorker(BOW * b, string pToImgs, bool * shouldStop);
    ~TestWorker();

public slots:
    void process();

signals:
    void finished();
    void giveData(QList<QString> str);
    void error(QString err);
    void tick();

private:
    BOW * bow;
    string pathToImages;
    QProgressDialog * progressDialog;
    volatile bool * cancel;
};

#endif //BAGOFWORDS_TESTWORKER_HPP

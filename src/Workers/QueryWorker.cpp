#include "QueryWorker.hpp"

QueryWorker::QueryWorker(BOW * b, QString it, int nImgs) {
    this->bow = b;
    this->selectedItem = it;
    this->numberOfImagesToDisplay = nImgs;
}

QueryWorker::~QueryWorker() {}


void QueryWorker::process() {
    QList<QString> list;

    int totalNumberToDisplay = numberOfImagesToDisplay + 1;
    ResultVector res = bow->makeQuery(selectedItem.toUtf8().constData(),
                                      totalNumberToDisplay);


    std::pair<double, double> p = bow->getPrecisionAndRecall(res, totalNumberToDisplay);

    for(int i = 0; i < res.getSize(); ++i)
    {
        list.append(QString::fromStdString(res.getPairAt(i).first));
    }
    list.append(QString::fromStdString(to_string(p.first)));
    list.append(QString::fromStdString(to_string(p.second)));
    emit giveData(list);
    emit finished();
}
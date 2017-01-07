#include "TestWorker.hpp"

// --- CONSTRUCTOR ---
TestWorker::TestWorker(BOW * b, string pToImgs, bool * sS) {
    this->bow = b;
    this->pathToImages = pToImgs;
    this->cancel = sS;
}

// --- DECONSTRUCTOR ---
TestWorker::~TestWorker() {
    // free resources
}

// --- PROCESS ---
// Start processing data.
void TestWorker::process()
{
    QList<QString> list;
    path p(pathToImages);
    recursive_directory_iterator dir(p), end;
    double averagePrecision[9];
    double averageRecall[9];

    for(int i = 0; i < 9; ++i)
        averagePrecision[i] = 0.0;

    for(int i = 0; i < 9; ++i)
        averageRecall[i] = 0.0;

    int imagesQueried = 0;
    while (dir != end)
    {
        file_status fs = status(dir->path());

        if (!is_directory(fs))
        {
            ResultVector res = bow->makeQuery(dir->path().string(), 90);

            if(res.getSize() == 0)
                continue;


            std::pair<double, double> p;
            p = bow->getPrecisionAndRecall(res, 10);
            averagePrecision[0] += p.first;
            averageRecall[0] += p.second;

            p = bow->getPrecisionAndRecall(res, 20);
            averagePrecision[1] += p.first;
            averageRecall[1] += p.second;

            p = bow->getPrecisionAndRecall(res, 30);
            averagePrecision[2] += p.first;
            averageRecall[2] += p.second;

            p = bow->getPrecisionAndRecall(res, 40);
            averagePrecision[3] += p.first;
            averageRecall[3] += p.second;

            p = bow->getPrecisionAndRecall(res, 50);
            averagePrecision[4] += p.first;
            averageRecall[4] += p.second;

            p = bow->getPrecisionAndRecall(res, 60);
            averagePrecision[5] += p.first;
            averageRecall[5] += p.second;

            p = bow->getPrecisionAndRecall(res, 70);
            averagePrecision[6] += p.first;
            averageRecall[6] += p.second;

            p = bow->getPrecisionAndRecall(res, 80);
            averagePrecision[7] += p.first;
            averageRecall[7] += p.second;

            p = bow->getPrecisionAndRecall(res, 90);
            averagePrecision[8] += p.first;
            averageRecall[8] += p.second;

            ++imagesQueried;
        }

        if(*cancel)
        {
            list.append("Process Canceled");
            emit giveData(list);
            emit finished();
            return;
        }
        emit tick();
        ++dir;
    }


    for(int i = 0, j = 10; i < 9; ++i, j+= 10)
    {
        averagePrecision[i] /= imagesQueried;
        cout << "Average precison for: "<< j << "    " << averagePrecision[i] << endl;
        list.append(QString::fromStdString(to_string(averagePrecision[i])));

        averageRecall[i] /= imagesQueried;
        cout << "Average recall for: "<< j << "    " << averageRecall[i] << endl;
        list.append(QString::fromStdString(to_string(averageRecall[i])));
    }


    emit giveData(list);
    emit finished();
}
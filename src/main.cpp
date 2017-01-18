#include <boost/regex.hpp>
#include <opencv2/core/core.hpp>
#include "src/View/mainwindow.h"
#include <QApplication>
#include "QStatusBar"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    MainWindow w;
    w.statusBar()->setSizeGripEnabled(false);
    w.setWindowTitle("BoW");
    w.show();

    return a.exec();
}
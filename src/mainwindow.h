#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadDatabaseButton_clicked();

    void on_loadImagesButton_clicked();

    void on_loadDictionaryButton_clicked();
    void radioBtnSelected();
    void prepareBtnSelected();
    void queryBtnSelected();
    void testBtnSelected();

private:
    Ui::MainWindow *ui;
    string databasePath;
    string dictionaryPath;
    string imagesPath;
    string selectedDescriptor;

};

#endif // MAINWINDOW_H

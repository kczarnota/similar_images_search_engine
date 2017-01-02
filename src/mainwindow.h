#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

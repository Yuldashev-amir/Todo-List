#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QLineEdit>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveTask();
    void loadTask();

private:
    QStandardItemModel * model;
    QLineEdit * inputTask;

    void setupUi();
};
#endif // MAINWINDOW_H

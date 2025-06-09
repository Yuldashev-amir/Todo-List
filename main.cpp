#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QLabel>
#include <QCheckBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow wgt;
    wgt.show();
    return a.exec();
}

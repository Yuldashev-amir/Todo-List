#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QListView>
#include <QFont>
#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), model(new QStandardItemModel(this))
{
    if (model == nullptr)
        qDebug() << "Model to has invalid value";
    else
    {
        setupUi();
        loadTask();
    }
}

MainWindow::~MainWindow() {}


void MainWindow::setupUi()
{
    QWidget * central = new QWidget;
    this->setWindowTitle("Todo List");

    QVBoxLayout * layout = new QVBoxLayout;
    QHBoxLayout * qhbxLayout = new QHBoxLayout;
    QLabel * label = new QLabel("Введите задачу");
    inputTask = new QLineEdit;
    inputTask->setPlaceholderText("Купить чай");

    QPushButton * button = new QPushButton("Добавить");

    QListView * listView = new QListView;
    listView->setModel(model);
    listView->setEditTriggers(QAbstractItemView::SelectedClicked);

    layout->addWidget(label);
    layout->addWidget(inputTask);
    layout->addWidget(button);
    layout->addLayout(qhbxLayout);
    qhbxLayout->addWidget(listView);
    central->setLayout(layout);
    this->setCentralWidget(central);

    QObject::connect(button, &QPushButton::clicked, this, [=](){
        QString task = inputTask->text();
        if (!task.isEmpty())
        {
            QStandardItem * item = new QStandardItem(task);
            item->setCheckable(true);
            item->setEditable(false);
            model->appendRow(item);
            inputTask->clear();
            this->saveTask();
        }
    });

    QObject::connect(model, &QStandardItemModel::dataChanged,
        this, [=](const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
    {
        Q_UNUSED(bottomRight);
        Q_UNUSED(roles);
            if (!topLeft.isValid())
            {
                qDebug() << "Невалидный индекс!";
                return;
            }

            QStandardItem * item = model->itemFromIndex(topLeft);
            if (!item) {
                qDebug() << "Item nullptr!";
                return;
            }

            if (item->checkState() == Qt::Checked)
            {
                QFont font = item->font();
                font.setStrikeOut(item->checkState() == Qt::Checked);
                item->setFont(font);
                qDebug() << "Изменение флажка обработано.";
                model->removeRow(item->row());
                this->saveTask();
                qDebug() << "Задача удалена!";
            }
    });
}

void MainWindow::loadTask()
{
    QFile fileTasks("fileTasks.csv");
    if (!fileTasks.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Ошибка в открытии файла";
        return;
    }
    QTextStream in(&fileTasks);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty())
        {
            QStandardItem * item = new QStandardItem(line);
            item->setCheckable(true);
            item->setEditable(false);
            model->appendRow(item);
        }
    }
    fileTasks.close();
}

void MainWindow::saveTask()
{
    QFile fileTasks("fileTask.csv");
    if (!fileTasks.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Ошибка в открытие файла";
        return;
    }
    QTextStream out(&fileTasks);
    for (int row = 0; row < model->rowCount(); ++row)
    {
        QStandardItem * item = model->item(row);
        if (item)
            out << item->text() << '\n';
    }
    fileTasks.close();
}

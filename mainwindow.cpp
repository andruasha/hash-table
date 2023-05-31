#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Test.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage(QString::fromStdString(Test()));

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Key" << "Value");
    ui->tableWidget->verticalHeader()->hide();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Add_clicked()
{
    collection << ui->wordLine->text().toStdString();
    update();
}


void MainWindow::on_Delete_clicked()
{
    collection.erase(ui->wordLine->text().toStdString());
    ui->wordLine->clear();
    update();
}


void MainWindow::on_Find_clicked()
{
    try
    {
        const QString msg = QString::number(collection.finding(ui->numberLine->text().toInt()));
        QMessageBox window;
        window.setText(msg);
        window.exec();
    }
    catch (std::runtime_error)
    {
        QMessageBox::warning(0, "Error", "No such values");
    }

}


void MainWindow::on_pushButton_clicked()
{
    collection.clear();
    update();
}


void MainWindow::on_actionSave_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save the file");
    collection.writeToFile(file_name.toStdString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
    collection.readFromFile(file_name.toStdString());
    update();
}


void MainWindow::update()
{
    ui->tableWidget->setRowCount(0);
    if (collection.unoccupied()) {
        return;
    }
    int index = 0;
    for (auto iterContainer = collection.containers_.begin(); iterContainer != collection.containers_.end(); iterContainer++) {
        const auto &container = *iterContainer;
        if (!container.empty()) {
            for (auto iterPair = container.begin(); iterPair != container.end(); iterPair++) {
                const auto &[key_, value_] = *iterPair;

                ui->tableWidget->insertRow(index);
                ui->tableWidget->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(key_), 0));
                ui->tableWidget->setItem(index, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(value_)), 0));
            }
        }
    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "HashTable.h"


typedef HashTable<std::string> Table;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_Add_clicked();

    void on_Delete_clicked();

    void on_Find_clicked();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

private:
    void update();

    Table collection;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

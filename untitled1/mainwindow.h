#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"
#include <QFile>
#include <QTableWidgetItem>
#include <QTableView>
#include <QFileDialog>
#include "csvparser.h"
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void infoPage();

private slots:

    void open();
    void save();
    void save_as();
    void exit();
    void cellEdit(QTableWidgetItem*);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    CSVFile *parser = nullptr;
};
#endif // MAINWINDOW_H

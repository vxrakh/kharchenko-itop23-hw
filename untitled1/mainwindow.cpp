#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setText(QString::number(settings::instanse()->getMin()));
    ui->lineEdit_2->setText(QString::number(settings::instanse()->getMax()));
    connect(ui->actOpen,    &QAction::triggered, this, &MainWindow::open);
    connect(ui->actSave,    &QAction::triggered, this, &MainWindow::save);
    connect(ui->actSaveAs,    &QAction::triggered, this, &MainWindow::save_as);
    connect(ui->actExit,    &QAction::triggered, this, &MainWindow::exit);
    connect(ui->tableWidget, &QTableWidget::itemChanged, this, &MainWindow::cellEdit);
    QObject::connect(ui->actionabout, &QAction::triggered, this, &MainWindow::infoPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::save()
{
    if (parser){
        auto path = parser->getFileName();
        parser->save(path);
        ui->statusBar->showMessage(QString("File Saved"));
    }else{
        QMessageBox::warning(this, "Error", "Try Again");
    }

}

void MainWindow::save_as()
{
    if (parser){
        auto path = QFileDialog::getSaveFileName(this);
        ui->statusBar->showMessage(QString("File Saved to ") + path);
        parser->save(path.toStdString());
    }else{
        QMessageBox::warning(this, "Error", "Try Again");
    }
}

void MainWindow::exit()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Save File?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        save();
        close();
    }else{
        close();
    }
}

void MainWindow::open()
{
    if (parser) {
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Open", "Save File?",
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes) {
              save();
              auto path = QFileDialog::getOpenFileName(this);
              if (path.isEmpty()) {
                  return;
              }

              ui->statusBar->showMessage(QString("File Uploaded ") + path);
              try{
                  parser = new CSVFile(path.toStdString());
              }catch(exception &problem){
                  QMessageBox::warning(this, "Error", "Try Again");
              }

              ui->tableWidget->setRowCount(parser->rowCount());
              ui->tableWidget->setColumnCount(parser->columnCount());

              for (size_t row = 0; row < parser->rowCount(); row++) {
                  Row rowVal = parser->getRow(row);
                  for (size_t col = 0; col < rowVal.size(); col++) {
                      QTableWidgetItem *newItem = new QTableWidgetItem(QString::fromStdString(rowVal[col]));
                      ui->tableWidget->setItem(row, col, newItem);
                  }
              }
          } else if(reply == QMessageBox::No) {
              auto path = QFileDialog::getOpenFileName(this);
              if (path.isEmpty()) {
                  return;
              }

              ui->statusBar->showMessage(QString("File Uploaded ") + path);

              try{
                  parser = new CSVFile(path.toStdString());
              }catch(exception &problem){
                  QMessageBox::warning(this, "Error", "Try Again");
              }

              ui->tableWidget->setRowCount(parser->rowCount());
              ui->tableWidget->setColumnCount(parser->columnCount());

              for (size_t row = 0; row < parser->rowCount(); row++) {
                  Row rowVal = parser->getRow(row);
                  for (size_t col = 0; col < rowVal.size(); col++) {
                      QTableWidgetItem *newItem = new QTableWidgetItem(QString::fromStdString(rowVal[col]));
                      ui->tableWidget->setItem(row, col, newItem);
                  }
              }
          }

    }else {
        auto path = QFileDialog::getOpenFileName(this);
        if (path.isEmpty()) {
            return;
        }

        ui->statusBar->showMessage(QString("File Uploaded ") + path);

        try{
            parser = new CSVFile(path.toStdString());
        }catch(exception &problem){
            QMessageBox::warning(this, "Error", "Try Again");
        }

        ui->tableWidget->setRowCount(parser->rowCount());
        ui->tableWidget->setColumnCount(parser->columnCount());

        for (size_t row = 0; row < parser->rowCount(); row++) {
            Row rowVal = parser->getRow(row);
            for (size_t col = 0; col < rowVal.size(); col++) {
                QTableWidgetItem *newItem = new QTableWidgetItem(QString::fromStdString(rowVal[col]));
                ui->tableWidget->setItem(row, col, newItem);
            }
        }
    }
}


void MainWindow::cellEdit(QTableWidgetItem *item)
{
    parser->setValue(item->row(), item->column(), item->text().toStdString());
}


void MainWindow::infoPage()
{
    About about;
    if (about.exec())
    {

    }
}

void MainWindow::on_pushButton_clicked()
{
    if (parser){
        parser->NewRow();
        ui->tableWidget->setRowCount(parser->rowCount());
        ui->statusBar->showMessage(QString("Row Added"));
    }else{
        QMessageBox::warning(this, "Error", "Try Again");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (parser){
        parser->NewColumn();
        ui->tableWidget->setColumnCount(parser->columnCount());
        ui->statusBar->showMessage(QString("Column Added"));
    }else{
        QMessageBox::warning(this, "Error", "Try Again");
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QString min = ui->lineEdit->text();
    settings::instanse()->setMin(stod(min.toStdString()));
    QString max = ui->lineEdit_2->text();
    settings::instanse()->setMax(stod(max.toStdString()));
}


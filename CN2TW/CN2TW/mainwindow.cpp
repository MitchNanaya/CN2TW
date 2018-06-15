#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*----set dirModel----*/
    QStringList filters;
    filters << "*.txt";
    dirModel = new QFileSystemModel;
    dirModel->setNameFilters(filters);
    dirModel->setNameFilterDisables(false);
    dirModel->setRootPath(QDir::rootPath());
    ui->treeView->setModel(dirModel);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
    ui->treeView->hideColumn(4);
    ui->treeView->setColumnWidth(0,200);
    /*----set fileModel----*/
    fileModel = new QFileSystemModel;
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(false);
    ui->treeView_file->setModel(fileModel);
    ui->treeView_file->hideColumn(1);
    ui->treeView_file->hideColumn(2);
    ui->treeView_file->hideColumn(3);
    ui->treeView_file->hideColumn(4);
    ui->treeView_file->setColumnWidth(0,200);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QList<QString> path_list;
    int numRows = fileModel->rowCount(rootIndex);
    for (int row = 0; row < numRows; ++row) {
        QModelIndex childIndex = fileModel->index(row, 0, rootIndex);
        if(!fileModel->isDir(childIndex)){
            QString path = fileModel->data(childIndex).toString();
            path_list.append(path);
            qDebug()<< rootPath+"/"+path;
            QFile file(rootPath+"/"+path);
            QTextStream in(&file);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
                QString lineAll = in.readAll();
                ui->textBrowser->append(lineAll);
            }
        }
    }


}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    rootPath = dirModel->filePath(index);
    rootIndex = fileModel->setRootPath(rootPath);
    ui->treeView_file->setRootIndex(fileModel->index(rootPath));
    ui->label_Path->setText(rootPath);
    QFile file(rootPath);
    QTextStream in(&file);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString lineAll = in.readAll();
        ui->textBrowser->setText(lineAll);

    }
}

void MainWindow::on_pushButton_loadText_clicked()
{
    QList<QString> path_list;
    int numRows = fileModel->rowCount(rootIndex);
    QString path = fileModel->filePath(rootIndex);
    QString fpath;
    for (int row = 0; row < numRows; ++row) {
        QModelIndex childIndex = fileModel->index(row, 0, rootIndex);
        if(!fileModel->isDir(childIndex)){
            fpath = fileModel->data(childIndex).toString();
            path_list.append(fpath);
            qDebug()<< path+fpath;
            break;
        }
    }
    QFile file(path+fpath);
    QTextStream in(&file);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString lineAll = in.readAll();
        ui->textBrowser->setText(lineAll);

    }
    else{
        qDebug()<<44;
    }

}

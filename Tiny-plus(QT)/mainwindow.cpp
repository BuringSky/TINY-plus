#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solve.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile source_file("D:\\SAMPLE.txt");
    source_file.open(QFile::WriteOnly);
    QTextStream out(&source_file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<ui->sourceEdit->toPlainText();
    QApplication::restoreOverrideCursor();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadFile(const QString &fileName)  //加载文件
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,tr("多文档编辑器"),tr("无法读取文件 %1:\n%2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->sourceEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    curFile = QFileInfo(fileName).canonicalFilePath();
    return true;
}

bool MainWindow::saveFile(const QString &fileName)//保存文件
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,tr("多文档编辑器"),
                             tr("无法写入文件 %1: /n %2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
     out<<ui->sourceEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    curFile = QFileInfo(fileName).canonicalFilePath();
    return true;
}

void MainWindow::on_openFileBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty()){
        loadFile(fileName);
        ui->sourceEdit->setVisible(true);
    }
}

void MainWindow::on_saveFileBtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存源码"),curFile);
    saveFile(fileName);
}

void MainWindow::on_createTreeBtn_clicked()
{
    QFile source_file("source.txt");
    source_file.open(QFile::WriteOnly);
    QTextStream out(&source_file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<ui->sourceEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    source_file.close();
    ui->syntaxTree->clear();

    qDebug()<<"未调用syntree";

    syntree(); //调用语法树生成函数
    QFile file("syntaxTree.txt");
    if(file.open(QIODevice::ReadOnly))
    {

        qDebug()<<"测试";
        QTextStream read(&file);
        while(!read.atEnd())
        {
           ui->syntaxTree->append(read.readAll());
        }
    }
}

void MainWindow::on_exitBtn_clicked()
{
    exit(1);
}

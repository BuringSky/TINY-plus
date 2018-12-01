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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool loadFile(const QString &fileName); //加载文件
    bool save(int witchfile);    //保存操作
    bool saveFile(const QString &fileName); //保存文件

private slots:
    void on_openFileBtn_clicked();

    void on_saveFileBtn_clicked();

    void on_createTreeBtn_clicked();

private:
    Ui::MainWindow *ui;
    QString curFile;    //保存当前文件的路径
};

#endif // MAINWINDOW_H

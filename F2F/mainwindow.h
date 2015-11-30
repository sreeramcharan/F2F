#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileSystemModel>
#include <QTableWidgetItem>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void on_pushButton_9_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index); // Not used: 14 Nov2015
    void on_btn_src_up_clicked();
    //void on_tableWidget_itemClicked(QTableWidgetItem *item); // // Not used: 14 Nov2015
    void on_pushButton_4_clicked();
    void on_btn_src_up_2_clicked();
    void on_dest_tableWidget_clicked(const QModelIndex &index);
    void on_dest_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButton_clicked();
    void on_btn_move_clicked();
    void on_btn_delete_clicked();
    void on_info_btn_clicked();

private:
    Ui::MainWindow *ui;
    QDir currentDir,dest_Dir;
    QFileSystemModel *dirtree;
    void Refresh(const QString &fPath, QTableWidget *table_widget, QDir *Directory);
    void showFiles(const QStringList &files);
    int FileCopy(QString &src,QString &des);
    void update_status(QString string);
    void Update_Drive_Size(const QString &filepath,QLabel *lable);
    void update_properties(bool UI,QString filename);
    void Update_File_Size(const QString &filepath,QLabel *lable);

};

#endif // MAINWINDOW_H

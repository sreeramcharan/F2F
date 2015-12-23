#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * Qt Header Files
 *
 *
 *
*/
#include <QDebug>
//#include <QFileSystemModel>
//#include <QTreeView>
//#include <QSortFilterProxyModel>
#include <QMessageBox>

/*
*   Custom Header File
*
*
*
*
*/
#include "file_utils.h"

#define Level0  0 // Basic
#define Level1  1 // medium
#define Level2  2 // High

#define Debug_Level Level0 //


/*
*
*
*
*
*
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowFlags(Qt::CustomizeWindowHint);

    QString Src_Path = QDir::homePath();

    //  ui->comboBox->addItem(text);

    ui->lineEdit_src->setDisabled(true);
    ui->lineEdit_dest->setDisabled(true);
    ui->lineEdit_src->setText(Src_Path);
    ui->lineEdit_dest->setText(Src_Path);

 /*
  * Source Side TableWiget settings
  *
 */
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    QStringList labels;
    labels << tr("Name");// << tr("Size");
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setShowGrid(false);

    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
/*
 *  Destination side TableWiget settings
 *
*/
    ui->dest_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dest_tableWidget->setColumnCount(1);
    ui->dest_tableWidget->setHorizontalHeaderLabels(labels);
    ui->dest_tableWidget->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);
    ui->dest_tableWidget->verticalHeader()->hide();
    ui->dest_tableWidget->setShowGrid(false);

    ui->dest_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
#if 0
//    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

   // QStringList labels;
  //  labels << tr("Filename") << tr("Size");
  //  ui->tableView->setColumnCount(2);
   // ui->tableView->setHorizontalHeaderLabels(labels);
//    ui->tableView->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);

 //   ui->tableView->verticalHeader()->hide();
  //  ui->tableView->setShowGrid(false);
#endif

#if Debug_Level == Level1
    qDebug() << "Directory Path: " + Src_Path;
#endif
    Refresh(Src_Path,ui->tableWidget,&currentDir);
    Refresh(Src_Path,ui->dest_tableWidget,&dest_Dir);

    ui->foldername_label->setText(QFileInfo(Src_Path).fileName());
    ui->foldername_label1->setText(QFileInfo(Src_Path).fileName());

    if(QFileInfo(Src_Path).isDir())
    {
        ui->type_label1->setText("Folder");
        ui->type_label2->setText("Folder");
    }
    Update_Drive_Size(Src_Path,ui->Foldersize_label);
    Update_Drive_Size(Src_Path,ui->Foldersize_label1);

   // connect(ui->src_sradioButton,SIGNAL(released()),this,SLOT(this->on_radio_button_released));
    connect(ui->src_mradioButton,SIGNAL(released()),this,SLOT(on_src_sradioButton_released()));
    connect(ui->dest_sradioButton,SIGNAL(released()),this,SLOT(on_src_sradioButton_released()));
    connect(ui->dest_mradioButton,SIGNAL(released()),this,SLOT(on_src_sradioButton_released()));

    ui->src_mradioButton->setEnabled(true);
    ui->src_sradioButton->setEnabled(true);
    ui->dest_mradioButton->setEnabled(false);
    ui->dest_sradioButton->setEnabled(false);

    /*Tested and working...*/
    /*Need to implement compleely*/
    //unsigned int count=0;
    //qint64 size=0;
    //Size_Folder_File(QString(Src_Path+"/Qt_Repo"),&count,&size);//+"/Folder2Copy/"

    ui->dest_tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

//    disconnect(ui->dest_tableWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(on_dest_tableWidget_clicked(QModelIndex)));
//    disconnect(ui->dest_tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_dest_tableWidget_doubleClicked(QModelIndex)));

  //  ui->dest_tableWidget->setDisabled(true);
  //  ui->dest_tableWidget->clearSelection();
  //  ui->dest_tableWidget->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * This function is used to print the file and folder names on to the screen.
 * Scree here is the TableWidget.
 *
 * Improvements:
 *  1. Need to generalise the function -> able to set both the tableswidget
 *      using same fuunction.
 *    : Done : 14_Nov_2015
 *  2. Added directory as a parameter too.
 *    : Done : 16_Nov_2015
 *
 */

void MainWindow::Refresh(const QString &fPath, QTableWidget *table_widget, QDir *Directory)
{
#if Debug_Level == Level2
    qDebug("---------------------------------------------------------------");
#endif
    //ui->tableWidget->setRowCount(0);
    table_widget->setRowCount(0);

    //QString path = str;//ui->comboBox->currentText();
    Directory->setPath(fPath);
    Directory->setFilter(QDir::NoDotAndDotDot|QDir::NoSymLinks);
    QFileInfoList filelist = Directory->entryInfoList(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks);

    for(int i=0;i<filelist.size();i++)
    {
        QFileInfo fileinfo = filelist.at(i);

        //QString FILENAME = fileinfo.fileName();

        if(fileinfo.isDir())
        {
#if Debug_Level == Level2
            qDebug() << "DIR:" + FILENAME;
#endif
            QTableWidgetItem *dirNameItem = new QTableWidgetItem(fileinfo.fileName());
            dirNameItem->setFlags(dirNameItem->flags() ^ Qt::ItemIsEditable);
           // dirNameItem->setIcon(QIcon("/home/sreeram/learn/qt/GUI_v1/Foldericon.png"));
            dirNameItem->setIcon(QIcon(":/images/images/Foldericon.png"));

            int row = table_widget->rowCount();
            table_widget->insertRow(row);
            table_widget->setItem(row, 0, dirNameItem);

        }
        else if(fileinfo.isFile())
        {
            //QFile file(FILENAME);
            //qint64 size = QFileInfo(file).size();

            QTableWidgetItem *fileNameItem = new QTableWidgetItem(fileinfo.fileName());
            fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
            fileNameItem->setIcon(QIcon(":/images/images/Fileicon.png"));

            // fileNameItem->setIcon(QIcon(":/images/images/Fileicon_ok.png"));

            //fileNameItem->setIcon(QIcon("/home/sreeram/learn/qt/GUI_v1/Fileicon.png"));
            /*QTableWidgetItem *sizeItem = new QTableWidgetItem(tr("%1 KB").arg(int((size + 1023) / 1024)));
            sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            sizeItem->setFlags(sizeItem->flags() ^ (Qt::ItemIsEditable | Qt::ItemIsSelectable));*/

            int row = table_widget->rowCount();
            table_widget->insertRow(row);
            table_widget->setItem(row, 0, fileNameItem);
            //table_widget->setItem(row, 1, sizeItem);
        }
    }

#if Debug_Level == Level2
    qDebug("---------------------------------------------------------------");
#endif
}


/*
 *  When an item/row in the TableWiget is clicked using mouse the below
 *  event is called.
 *
 */
QString Source_FileName="";
QString Source_FilePath="";
void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
   // QDir  *local_dir = new QDir(currentDir);

    if(ui->src_mradioButton->isChecked())
    {
        qDebug("Multiple files selected");
        return;
    }

    qDebug() << "Clicked from source";
    QString str = ui->tableWidget->model()->data(index).toString();

    qDebug() << "Selected:" + str;

    QFileInfo myinfo = currentDir.absoluteFilePath(str);
#if 1
    if(myinfo.isDir())
    {

        Source_FilePath = myinfo.filePath();
        Source_FileName = myinfo.fileName();

#if  Debug_Level==Level1
        qDebug() << "It is Dir";
        qDebug() << "Folder Name:" + Source_FileName;
        qDebug() << "Path:" + Source_FilePath;
#endif
       // qDebug() << "Folder Size" + QString("%1 Bytes").arg(myinfo.size());
       // ui->comboBox->clear();
       // ui->comboBox->addItem(myinfo.filePath());
       // Refresh(myinfo.absoluteFilePath());
    }
#endif
    if(myinfo.isFile())
    {
      //  qDebug() << "File Name:" + myinfo.fileName();
      //  QFile myfile(myinfo.absoluteFilePath());
      //  qint64 size = myinfo.absoluteFilePath().size();//QFileInfo();
        Source_FilePath = myinfo.filePath();
        Source_FileName = myinfo.fileName();



#if  Debug_Level==Level1
        qDebug() << "It is File";
        qDebug() << "File Name:" + Source_FileName;
        qDebug() << "Path:" + Source_FilePath;
        qDebug() << "File Size:" + QString("%1 Bytes").arg(myinfo.size());
#endif
    }
    update_properties(0,myinfo.filePath());
}

#if 1
// This is not used as of now. : 14 Nov 2015
/*
 * When an item/row in the TableWiget is double clicked using mouse the below
 * event is called.
 *
 * May not be required.
 */
void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    qDebug() << "Double Clicked from source";
    QString str = ui->tableWidget->model()->data(index).toString();
    qDebug() << "Selected:" + str;

    QFileInfo myinfo = currentDir.absoluteFilePath(str);

    if(myinfo.isDir())
    {
        qDebug() << "It is Dir";

        qDebug() << "File Path:" + myinfo.filePath();
        qDebug() << "File Name:" + myinfo.fileName();
        //ui->comboBox->addItem(myinfo.filePath());

        ui->lineEdit_src->setText(myinfo.filePath());

        // Refresh(myinfo.absoluteFilePath());
        //  Refresh(myinfo.absoluteFilePath(),ui->tableWidget);
          Refresh(myinfo.absoluteFilePath(),ui->tableWidget,&currentDir);

          ui->foldername_label->setText(myinfo.fileName());
          ui->type_label1->setText("Folder");
          Update_Drive_Size(myinfo.filePath(),ui->Foldersize_label);
    }
}
#endif
/*
 * When the UP button is clicked this event is called.
 *
 * This function changes the directory.
 */
void MainWindow::on_btn_src_up_clicked()
{
    // Move the current Directory
    currentDir.cdUp();

    QString  fPath = currentDir.absolutePath();
   // Refresh(currentDir.absolutePath(),ui->tableWidget);

    // To display the Path
   ui->lineEdit_src->setText(fPath);

   // To display the files and folders
   Refresh(fPath,ui->tableWidget, &currentDir);
   ui->foldername_label->setText(QFileInfo(fPath).fileName());
   ui->type_label1->setText("Folder");
   Update_Drive_Size(fPath,ui->Foldersize_label);
}

bool toggle=1;
void MainWindow::on_pushButton_4_clicked()
{
    if(toggle==1)
    {
        ui->pushButton_4->setText("<<-");
        ui->src_mradioButton->setEnabled(false);
        ui->src_sradioButton->setEnabled(false);
        ui->dest_mradioButton->setEnabled(true);
        ui->dest_sradioButton->setEnabled(true);
        toggle = 0;
    }
    else
    {
        ui->pushButton_4->setText("->>");

        ui->src_mradioButton->setEnabled(true);
        ui->src_sradioButton->setEnabled(true);
        ui->dest_mradioButton->setEnabled(false);
        ui->dest_sradioButton->setEnabled(false);

        toggle = 1;
    }

    // Clear the Selection if Toggled
    ui->tableWidget->clearSelection();
    ui->dest_tableWidget->clearSelection();
}

void MainWindow::on_btn_src_up_2_clicked()
{
    dest_Dir.cdUp();

    QString  fPath = dest_Dir.absolutePath();

    // To display the Path
   ui->lineEdit_dest->setText(fPath);

   // To display the files and folders
   Refresh(fPath,ui->dest_tableWidget, &dest_Dir);

   ui->foldername_label1->setText(QFileInfo(fPath).fileName());
   ui->type_label2->setText("Folder");
   Update_Drive_Size(fPath,ui->Foldersize_label1);
}

/*
 *
 *
 *
 *
 */
QString Dest_FileName="";
QString Dest_FilePath="";
void MainWindow::on_dest_tableWidget_clicked(const QModelIndex &index)
{
    qDebug() << " Destination Table Clicked";
    QString str = ui->dest_tableWidget->model()->data(index).toString();
    qDebug() << "Selected:" + str;

    QFileInfo myinfo = dest_Dir.absoluteFilePath(str);

    if(myinfo.isDir())
    {
        qDebug() << "It is Dir";
        Dest_FilePath = myinfo.filePath();
        qDebug() << "Path:" + Dest_FilePath;
        Dest_FileName = myinfo.fileName();
        qDebug() << "Folder Name:" + Dest_FileName;
   }
   if(myinfo.isFile())
    {
        Dest_FilePath = myinfo.filePath();
        Dest_FileName = myinfo.fileName();

#if Debug_Level==Level1
        qDebug() << "It is File";
        qDebug() << "File Name:" + Dest_FileName;
        qDebug() << "Path:" + Dest_FilePath;
        qDebug() << "File Size:" + QString("%1 Bytes").arg(myinfo.size());
#endif

    }

   update_properties(1,myinfo.filePath());

}


/*
 *
 *
 *
 *
 *
 */
void MainWindow::on_dest_tableWidget_doubleClicked(const QModelIndex &index)
{
    qDebug() << "Double Clicked from Destination Table";
    QString str = ui->dest_tableWidget->model()->data(index).toString();
    qDebug() << "Selected:" + str;

    QFileInfo myinfo = dest_Dir.absoluteFilePath(str);

    if(myinfo.isDir())
    {
        qDebug() << "It is Dir";
        qDebug() << "File Path:" + myinfo.filePath();
        qDebug() << "File Name:" + myinfo.fileName();

        ui->lineEdit_dest->setText(myinfo.filePath());
        Refresh(myinfo.absoluteFilePath(),ui->dest_tableWidget,&dest_Dir);

        ui->foldername_label1->setText(myinfo.fileName());
        ui->type_label2->setText("Folder");
        Update_Drive_Size(myinfo.filePath(),ui->Foldersize_label1);
    }
}

int MainWindow::FileCopy(QString &src,QString &des)
{
    //QFile  in(src),out(des);
    bool rewrite = true;
    bool status = 0;

#if 1   // Method 1
    if(QFile::exists(des))
    {
        int ret = QMessageBox::information(this,"File Information","File already exists!!!\nClick save to overwrite.\nClick cancel to exit."
                                           ,QMessageBox::Save, QMessageBox::Cancel);
        switch (ret)
        {
        case QMessageBox::Save:
            qDebug() << "Save Pressed";
            rewrite = true;
            if(!QFile::remove(des))
            {
                qDebug() << "File cant be deleted";
            }
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel Pressed";
            rewrite = false;
            break;
        default:
            break;
        }
    }

    if(rewrite==true)
    {
        if(!QFile::copy(src,des))
        {
            qDebug() << "Operation Failed";
            status = 0; // Failure
        }
        else
        {
            status = 1; // Success
        }
    }
    else
    {


    }
#else   // Method 2
    if(!in.open(QIODevice::ReadOnly))
    {
        qDebug() << "File Can't open";
    }
    if(!out.exists())
    {
        if(!out.open(QIODevice::WriteOnly))
        {
            qDebug() << "Cant open File";
        }
        char file_data = 0;
        unsigned int filesize = 0;
        while(!in.atEnd())
        {
            in.getChar(&file_data);
            out.putChar(file_data);
            filesize++;
            ui->progressBar->setValue(filesize/2);
        }
        out.close();
        qDebug() << QString("New Written File Size:%1").arg(filesize);


        if(toggle)
            Refresh(dest_Dir.path(),ui->dest_tableWidget,&dest_Dir);
        else
            Refresh(currentDir.path(),ui->tableWidget,&currentDir);

    }
    else
    {
        qDebug() << "File already exists";
    }
    in.close();
#endif
    return status;
}

QStringList multi_file_list;
// This is Copy Button
void MainWindow::on_copy_btn_clicked()
{
// Copy from Source to Destication / Destination to Source
// qDebug() << " Destination Current Dir:" + dest_Dir.path();
// qDebug() << " Source Current Dir:" + currentDir.path();

    QString File2Write;
    QString File2Read;
    QList<QTableWidgetItem*>   sellist;

    if(toggle)
    {
        sellist = ui->tableWidget->selectedItems();
    }
    else
    {
        sellist = ui->dest_tableWidget->selectedItems();
    }
    multi_file_list.clear();
    for(int i=0;i<sellist.size();i++)
    {
        QTableWidgetItem *myitem = sellist.at(i);
        QString str = myitem->text();

        multi_file_list.append(str);

        qDebug() << QString("List(%1):").arg(i)<<str;
    }
    int nFiles = multi_file_list.length();
    if(nFiles>1)
    {
        if(toggle)
        {
            Copy_Multiple_Files(multi_file_list,currentDir.path(),dest_Dir.path());
        }
        else
        {
            Copy_Multiple_Files(multi_file_list,dest_Dir.path(),currentDir.path());
        }

    }
    else if(nFiles==1)
    {
        if(toggle)
        {
            File2Write = dest_Dir.path() +"/"+multi_file_list.at(0);
            File2Read = Source_FilePath;
        }
        else
        {
            File2Read = Dest_FilePath;
            File2Write =currentDir.path() + "/"+multi_file_list.at(0);
        }

        qDebug() << "File to Read"+ File2Read;
        qDebug() << "File To Write:"+File2Write;

        if(File2Read != "")
        {
            QFileInfo  file(File2Read);
            if(file.isFile())
            {
                if(FileCopy(File2Read,File2Write))
                {

                }
            }
            else
            {
                qDebug() << "Selected Directory";
                int ret = QMessageBox::information(this,"Information","Directory Selected.\nDo you want to copy all files in the Folder?",QMessageBox::Yes,QMessageBox::No);
                switch (ret) {
                case QMessageBox::Yes:
                            Copy_Directory(File2Read,File2Write);
                    break;
                case QMessageBox::No:

                    break;
                default:
                    break;
                }
            }
        }
    }
    else
    {
        // No File Selected.
    }
    //Write Successful.
    if(toggle)
    {
        Refresh(dest_Dir.path(),ui->dest_tableWidget,&dest_Dir);
        update_properties(toggle,Dest_FilePath);
    }
    else
    {
        Refresh(currentDir.path(),ui->tableWidget,&currentDir);
        update_properties(toggle,Source_FilePath);
    }

    Dest_FilePath = "";
    Source_FilePath = "";
    ui->tableWidget->clearSelection();
    ui->dest_tableWidget->clearSelection();

}

/*
*
*
*  To Do
*/
void MainWindow::on_btn_move_clicked()
{

    QString File2Write;
    QString File2Read;

    update_status("Moving File");

    if(toggle)
    {
        File2Write = dest_Dir.path() +"/"+Source_FileName;
        File2Read = Source_FilePath;
    }
    else
    {
        File2Read = Dest_FilePath;
        File2Write =currentDir.path() + "/"+Dest_FileName;
    }

    qDebug() << "File to Read"+ File2Read;
    qDebug() << "File To Write:"+File2Write;

    if(File2Read != "")
    {
        QFileInfo  file(File2Read);
        if(file.isFile())
        {
            if(FileCopy(File2Read,File2Write))
            {
                // File Write Successful.
                if(toggle)
                {
                    if(QDir(currentDir.path()).remove(Source_FileName))
                    {
                        update_status("File Moved");
                       // Refresh(dest_Dir.path(),ui->dest_tableWidget,&dest_Dir);
                    }
                    else
                    {
                        update_status("File Not Moved");
                    }

                }
                else
                {

                    if(QDir(dest_Dir.path()).remove(Dest_FileName))
                    {
                        update_status("File Moved");

                    }
                    else
                    {
                        update_status("File Not Moved");
                    }
                }
            }
            else
            {
                update_status("File Copy Failed");
            }
        }
        else if(file.isDir())
        {
            qDebug() << "Selected Directory";
            QMessageBox::information(this,"Information","Directory Selected.\nDo you want to copy all files in the Folder?",QMessageBox::Yes,QMessageBox::No);
          //  Move_Directory(File2Read,File2Write); // Need to analise more

        }
    }
    Refresh(dest_Dir.path(),ui->dest_tableWidget,&dest_Dir);
    Refresh(currentDir.path(),ui->tableWidget,&currentDir);

    ui->tableWidget->clearSelection();
    ui->dest_tableWidget->clearSelection();

    Source_FilePath = "";
    Dest_FilePath = "";

}

/*
 *
 *
 *
 * To Do
*/
void MainWindow::on_btn_delete_clicked()
{
    QString File2Del="",FilePath="";

    QList<QTableWidgetItem*>   sellist;
    if(toggle)
    {
        sellist = ui->tableWidget->selectedItems();
    }
    else
    {
        sellist = ui->dest_tableWidget->selectedItems();
    }
    multi_file_list.clear();
    for(int i=0;i<sellist.size();i++)
    {
        QTableWidgetItem *myitem = sellist.at(i);
        QString str = myitem->text();

        multi_file_list.append(str);

        qDebug() << QString("List(%1):").arg(i)<<str;
    }
    int nFiles = multi_file_list.length();

    if(nFiles>1)    // Multiple Files.
    {

    }
    else if(nFiles==1)
    {
        if(toggle)
        {
            //File2Write = dest_Dir.path() +"/"+Source_FileName;
            File2Del = multi_file_list.at(0);
            FilePath = currentDir.path();
        }
        else
        {
            File2Del = multi_file_list.at(0);
            FilePath = dest_Dir.path();
            //File2Write =currentDir.path() + "/"+Dest_FileName;
        }

        if(File2Del != "")
        {
            QString Del_path = FilePath+"/"+File2Del;
            QFileInfo file(Del_path);

            if(file.isDir())
            {
                QString Folder_details = QString("Do you want to delete folder and files inside?\n"
                                                 "Folder Name: %1\n"
                                                 "Folder Size: %2 Bytes\n").arg(file.fileName()).arg(Direc_Size(Del_path));

                int ret =  QMessageBox::warning(this,"Delete Folder",Folder_details,QMessageBox::Yes,QMessageBox::No);

                switch(ret)
                {
                case QMessageBox::Yes:
                #if 1
                    //if(file.path() == )
                    // Del_Directory(Del_path);
                   // This function created a big problem.
                #endif
        // Need to add here
                    break;

                case QMessageBox::No:

                    break;

                default:break;
                }
            }
            else if(file.isFile())
            {
                QDateTime   created = file.created();
                QString created_date = created.toString();
                QString modi_date = QDateTime(file.lastModified()).toString();
                int si = file.size();

                QString Fdetails = QString("Do you want to delete File?\nFile Name: %1\n"
                                           "File Size: %2 Bytes\n"
                                           "File Created: %3\n").arg(File2Del).arg(si).arg(created_date).arg(modi_date);

                int ret =  QMessageBox::warning(this,"Delete File",Fdetails,QMessageBox::Yes,QMessageBox::No);

                   switch(ret)
                   {
                   case QMessageBox::Yes:

                    if(QDir(FilePath).remove(File2Del))
                    {
                        update_status("File Deleted");
                    }
                    else
                    {
                        update_status("File Not Deleted");
                    }
                   break;

                   case QMessageBox::No:

                       break;

                   default:break;
                   }

            }
        }
    }
    else
    {

    }

    // Refresh the Deleted table
    if(!toggle)
        Refresh(dest_Dir.path(),ui->dest_tableWidget,&dest_Dir);
    else
        Refresh(currentDir.path(),ui->tableWidget,&currentDir);

    Source_FileName = "";
    Dest_FileName = "";
}

/*
 *
 *
 *
*/
void MainWindow::update_status(QString string)
{
    ui->status_label->clear();
    ui->status_label->setText(string);
}

void MainWindow::update_properties(bool UI,QString filename)
{
    QFileInfo   info(filename);
    QString FileName = info.fileName();
    bool type = info.isDir();

    if(FileName.length()>15)
    {
        FileName.chop(14);
        FileName.append("~");
    }
    if(UI==0)
    {
        ui->foldername_label->setText(FileName);

        if(type)
        {
            ui->type_label1->setText("Folder");
            ui->label_4->setText("Contents");
            ui->Foldersize_label->setText("-");
        }
        else
        {
            ui->type_label1->setText("File");
            ui->label_4->setText("Size");
            Update_File_Size(filename,ui->Foldersize_label);
        }
    }
    else
    {
        ui->foldername_label1->setText(FileName);
        if(type)
        {
            ui->type_label2->setText("Folder");
            ui->label_7->setText("Contents");
            ui->Foldersize_label1->setText("-");
        }
        else
        {
            ui->type_label2->setText("File");
            ui->label_7->setText("Size");
            Update_File_Size(filename,ui->Foldersize_label1);
            //ui->Foldersize_label1->setText("");
        }
    }
}

/*
 *
 *
 *
 *
 *
 *
 *
*/
QStringList list = QStringList() << "Bytes" << "MB" << "GB";
void MainWindow::Update_Drive_Size(const QString &filepath,QLabel *lable)
{
    qint64 dirsize = Direc_Size(filepath);
    qint64 local = 0;
    float s=0;
    int i=0;

    local = dirsize/1000000; // Bytes to MB
    if(local==0)
    {
        s = dirsize;    // get bytes
        i = 0;
    }
    else if((local>0) && ((local/1000)==0))
    {
        s = (float)dirsize/1000000;
        i = 1;
    }
    else
    {
        s = (float)dirsize/1000000; // bytes to MB
        s = s/1000; // MB to GB
        i = 2;
    }

    lable->setText(QString("%1 %2").arg(s).arg(list.at(i)));
}

/*
 *
 *
 *
 *
 *
*/
void MainWindow::Update_File_Size(const QString &filepath,QLabel *lable)
{
    qint64 dirsize = QFileInfo(filepath).size();//Direc_Size(filepath);
    qint64 local = 0;
    float s=0;
    int i=0;

    local = dirsize/1000000; // Bytes to MB
    if(local==0)
    {
        s = dirsize;    // get bytes
        i = 0;
    }
    else if((local>0) && ((local/1000)==0))
    {
        s = (float)dirsize/1000000;
        i = 1;
    }
    else
    {
        s = (float)dirsize/1000000; // bytes to MB
        s = s/1000; // MB to GB
        i = 2;
    }

    lable->setText(QString("%1 %2").arg(s).arg(list.at(i)));
}


void MainWindow::on_src_sradioButton_released()
{
    if(toggle)
    {
        if(ui->src_sradioButton->isChecked())
        {
            ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        }
        else// if(ui->src_mradioButton->isChecked())
        {
            ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        }
        ui->dest_tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
//        disconnect(ui->dest_tableWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(on_dest_tableWidget_clicked(QModelIndex)));
//        disconnect(ui->dest_tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_dest_tableWidget_doubleClicked(QModelIndex)));
       // ui->dest_tableWidget->setSelectionBehavior();
    }
    else
    {
//        connect(ui->dest_tableWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(on_dest_tableWidget_clicked(QModelIndex)));
//        connect(ui->dest_tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_dest_tableWidget_doubleClicked(QModelIndex)));

        if(ui->dest_sradioButton->isChecked())
        {
            ui->dest_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        }
        else
        {
            ui->dest_tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        }

        ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
//        disconnect(ui->tableWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(on_tableWidget_clicked(QModelIndex)));
//        disconnect(ui->tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_tableWidget_doubleClicked(QModelIndex)));

    }
    ui->tableWidget->clearSelection();
    ui->dest_tableWidget->clearSelection();
}

/*  */
void MainWindow::on_info_btn_clicked()
{
    QString  information = "This is a file copy software.\n\n"
                           "Author  : _______________\n"
                           "Version : 0.1\n"
                           "\nThankyou.\n";
    QMessageBox::information(this,"About",information,QMessageBox::Close);
}


/*  */
void MainWindow::on_info_btn_2_clicked()
{
    exit(EXIT_SUCCESS);
}

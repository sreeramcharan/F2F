/*
 *  File Name :
 *  Description :
 *
 *
 *  Modifications :
 *  Author    :
*/
#include <QtCore>


#include  "file_utils.h"


/*
 *
 *
 *
 *
 *
*/
qint64  Direc_Size(const QString &filepath)
{
   qint64   sizex = 0;
   QFileInfo  strinfo(filepath);

   if(strinfo.isDir())
   {
        QDir    folder(filepath);
        QFileInfoList   fileslist = folder.entryInfoList(QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::AllDirs|QDir::Files|QDir::Hidden);
        for(int i=0;i<fileslist.size();i++)
        {
            QFileInfo   info = fileslist.at(i);

            if(info.isDir())
            {
                //qDebug() << "Dir Found:" + info.fileName();
                sizex += Direc_Size(info.absoluteFilePath());
            }
            else
            {
                sizex += info.size();
            }
        }
   }
   return sizex;
}


/*
 *
 *
 *
 *
 *
*/
bool  Copy_Directory(const QString &srcfilepath,const QString &destfilepath)
{
   qint64   sizex = 0;
   //int nfiles=0;
   QFileInfo  strinfo(srcfilepath);
   QFileInfo  destinfo(destfilepath);

   if(!destinfo.exists())
   {
       qDebug()<<"Directory Does not exist:"+destinfo.fileName();
       QDir     dir(destinfo.absolutePath());
       dir.mkdir(destinfo.filePath());
       qDebug()<<"Hope its done";
   }

   if(strinfo.isDir())
   {
        QDir    folder(srcfilepath);
        QFileInfoList   fileslist = folder.entryInfoList(QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::AllDirs|QDir::Files|QDir::Hidden);
        for(int i=0;i<fileslist.size();i++)
        {
            QFileInfo   info = fileslist.at(i);

            if(info.isDir())
            {
                //qDebug() << "Dir Found:" + info.fileName();
               // QDir()::mkdir(QString(destfilepath+info.fileName()));
                QString dest_path = destinfo.absoluteFilePath()+QDir::separator()+info.fileName();
                Copy_Directory(info.absoluteFilePath(),dest_path);
               // sizex += Direc_Size(info.absoluteFilePath());
            }
            else
            {
                sizex += info.size();
                qDebug() << "Copying from:"+info.filePath();
                QString dname = QString(destinfo.absoluteFilePath()+QDir::separator()+info.fileName());
                qDebug() << "Copying to:" + dname;
                if(QFile::exists(dname))
                {
                    qDebug() << "File Already exists";
                    if(QFile::remove(dname))
                    {
                        qDebug("File removed");
                    }
                }
                QFile::copy(info.filePath(),dname);
            }
        }
   }

   return 0;//sizex;
}

/*
 *
 *
 *
 *
 *
*/
bool  Move_Directory(const QString &srcfilepath,const QString &destfilepath)
{
   qint64   sizex = 0;
   //int nfiles=0;
   QFileInfo  strinfo(srcfilepath);
   QFileInfo  destinfo(destfilepath);

   if(!destinfo.exists())
   {
       qDebug()<<"Directory Does not exist:"+destinfo.fileName();
       QDir     dir(destinfo.absolutePath());
       dir.mkdir(destinfo.filePath());
       qDebug()<<"Hope its done";
   }

   if(strinfo.isDir())
   {
        QDir    folder(srcfilepath);
        QFileInfoList   fileslist = folder.entryInfoList(QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::AllDirs|QDir::Files|QDir::Hidden);
        for(int i=0;i<fileslist.size();i++)
        {
            QFileInfo   info = fileslist.at(i);

            if(info.isDir())
            {
                QString dest_path = destinfo.absoluteFilePath()+QDir::separator()+info.fileName();
                Copy_Directory(info.absoluteFilePath(),dest_path);
                folder.rmdir(info.fileName());
            }
            else
            {
                sizex += info.size();
                qDebug() << "Copying from:"+info.filePath();
                QString dname = QString(destinfo.absoluteFilePath()+QDir::separator()+info.fileName());
                qDebug() << "Copying to:" + dname;
                if(QFile::exists(dname))
                {
                    qDebug() << "File Already exists";
                    if(QFile::remove(dname))
                    {
                        qDebug("File removed");
                    }
                }
                QFile::copy(info.filePath(),dname);
            }
        }
   }

   return 0;//sizex;
}
/*
 *
 *
 *
 *
 *
*/
bool  Del_Directory(const QString &srcfilepath)
{
  QFileInfo  strinfo(srcfilepath);
  if(strinfo.isDir())
   {
        QDir    folder(srcfilepath);
        QFileInfoList   fileslist = folder.entryInfoList(QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::AllDirs|QDir::Files|QDir::Hidden);
        for(int i=0;i<fileslist.size();i++)
        {
            QFileInfo   info = fileslist.at(i);
            if(info.isDir())
            {
                Del_Directory(info.absoluteFilePath());
                folder.rmdir(info.fileName());
            }
            else
            {
                QFile::remove(info.filePath());
            }
        }
   }
   return 0;
}


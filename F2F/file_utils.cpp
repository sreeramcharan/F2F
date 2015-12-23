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
 */
void  Size_Folder_File(const QString &filepath, unsigned int *filecnt, qint64 *fol_size)
{
   QFileInfo  strinfo(filepath);
   if(strinfo.isDir())
   {
        QDir    folder(filepath);
        QFileInfoList   fileslist = folder.entryInfoList(QDir::NoDotAndDotDot|QDir::AllDirs|QDir::Files|QDir::NoSymLinks);//QDir::Dirs|QDir::Files);
        for(int i=0;i<fileslist.size();i++)
        {
            QFileInfo   info = fileslist.at(i);

            if(info.isDir())
            {
                //qDebug() << "Dir Found:" + info.fileName();
                (*filecnt)++;
                Size_Folder_File(info.absoluteFilePath(),filecnt,fol_size);
            }
            else if(info.isFile())
            {
                QString name = info.fileName();
                if(name.endsWith('~'))
                {

                }
                else
                {
                    (*fol_size) += info.size();
                    (*filecnt)++;
                }
            }
        }
   }
}
/*
 *
 *
 *
 *
 *
*/
qint64  Direc_Items(const QString &filepath)
{
   qint64   total_items = 0;
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
                total_items += Direc_Items(info.absoluteFilePath());
            }
            else
            {
                total_items += 1;//info.size();
            }
        }
   }
   else if(strinfo.isFile())
   {
       total_items += 1;
   }

   return total_items;
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
       //qDebug()<<"Directory Does not exist:"+destinfo.fileName();
       QDir     dir(destinfo.absolutePath());
       dir.mkdir(destinfo.filePath());
       //qDebug()<<"Hope its done";
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
                //qDebug() << "Copying from:"+info.filePath();
                QString dname = QString(destinfo.absoluteFilePath()+QDir::separator()+info.fileName());
                //qDebug() << "Copying to:" + dname;
                if(QFile::exists(dname))
                {
                    qDebug() << "File Already exists";
                    if(QFile::remove(dname))
                    {
                        qDebug("File removed");
                    }
                }
                if(!QFile::copy(info.filePath(),dname))
                    return true;
            }
        }
   }

   return true;//sizex;
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
  QDir  dir(srcfilepath);
  if(!dir.exists())
      return true;

  QFileInfo  strinfo(srcfilepath);
  if(strinfo.isDir())
   {
        QDir    folder(srcfilepath);
        QFileInfoList   fileslist = folder.entryInfoList(QDir::NoDotAndDotDot|QDir::AllDirs|QDir::Files|QDir::Hidden);
        for(int i=0;i<fileslist.size();i++)
        {
            QFileInfo   info = fileslist.at(i);
            if(info.isDir())
            {
                if(!Del_Directory(info.filePath()))
                    return false;
            }
            else
            {
                if(!QFile::remove(info.filePath()))
                    return false;
            }
        }
   }

  QDir parentDir(QFileInfo(srcfilepath).path());
  return parentDir.rmdir(QFileInfo(srcfilepath).fileName());
}


/*
 *
 *
 *
 */
bool Copy_Multiple_Files(const QStringList &flist,const QString &srcpath,const QString &despath)
{
    for(int i=0;i<flist.size();i++)
    {
        QString  File2Read = srcpath    +"/" +  flist.at(i);
        QString File2Write = despath    +"/" +  flist.at(i);

        QFileInfo   finfo = File2Read;
        if(finfo.isDir())
        {
            Copy_Directory(File2Read,File2Write);
        }
        else if(finfo.isFile())
        {
            if(!QFile::copy(File2Read,File2Write))
                return false;
        }
    }
    return true;
}

#ifndef FILE_UTILS
#define FILE_UTILS

#include <QtCore>

qint64  Direc_Size(const QString &filepath);
bool  Copy_Directory(const QString &srcfilepath,const QString &destfilepath);
bool  Move_Directory(const QString &srcfilepath,const QString &destfilepath);
bool  Del_Directory(const QString &srcfilepath);
//qint64  Size_Folder_File(const QString &filepath);
//qint64  Size_Folder_File(const QString &filepath, unsigned int *filecnt);
void  Size_Folder_File(const QString &filepath, unsigned int *filecnt, qint64 *fol_size);
qint64  Direc_Items(const QString &filepath);
bool Copy_Multiple_Files(const QStringList &flist,const QString &srcpath,const QString &despath);

#endif // FILE_UTILS


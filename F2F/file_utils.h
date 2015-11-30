#ifndef FILE_UTILS
#define FILE_UTILS

#include <QtCore>

qint64  Direc_Size(const QString &filepath);
bool  Copy_Directory(const QString &srcfilepath,const QString &destfilepath);
bool  Move_Directory(const QString &srcfilepath,const QString &destfilepath);
bool  Del_Directory(const QString &srcfilepath);



#endif // FILE_UTILS


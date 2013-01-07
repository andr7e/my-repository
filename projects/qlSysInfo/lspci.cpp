#include <stdio.h>
#include "systeminfo.h"


//type - line count, host bridge one, other can be 2
bool makeCorrectingLspci (char *buf, QString &res, int type){
    if (!buf) return 0;
    /*
    //For only one line
    int c=0;
    while (c<len && buf[c]!='\n') c++; c++;
    while (c<len && buf[c]!='\n') c++;
    buf[c]=0;

    char *p=buf;

    while (*p!=' ') p++;
    while (*p!=':') p++;
    p++; p++;
    */

    QString qstr (buf);
    QStringList slist = qstr.split('\n');

    //qDebug () << slist.size ();

    for (int i=0; i < qMin<int>(slist.size ()-1, type); i++){
        int ind=slist[i].indexOf (" ");
        slist[i].remove(0, ind);
        ind=slist[i].indexOf (":");
        slist[i].remove(0, ind+2);

        if (i!=0) res +='\n';
        res += slist[i];
    }

    return 1;
}

#define BUF_MAX_SIZE 1024
#define LSPCI "lspci"

bool
SystemInfo::
LoadLspciInfo (){
    char buf[BUF_MAX_SIZE];
    char path[256];

    QList<QString> lspciList;
    lspciList << "Host" << "VGA" << "Audio" << "Ethernet" << "Network";

    for (int i=0; i<lspciList.size(); i++){
        sprintf (path, "%s | grep %s", LSPCI, lspciList[i].toStdString().c_str());

        FILE *fd = popen (path, "r");
        if (fd){
            memset (buf, 0, sizeof(buf));
            fread (buf, BUF_MAX_SIZE-1, 1, fd);
            //qDebug () << buf;
            makeCorrectingLspci (buf, lspciInfo_[i], i==0? 1 : 2);

            fclose (fd);
        }
    }

    return 1;
}

QString&
SystemInfo::GetChipset (){ return lspciInfo_[0];}

QString&
SystemInfo::GetVideocard (){ return lspciInfo_[1];}

QString&
SystemInfo::GetAudiocard (){ return lspciInfo_[2];}

QString&
SystemInfo::GetEthernet (){ return lspciInfo_[3];}

QString&
SystemInfo::GetNetwork (){ return lspciInfo_[4];}

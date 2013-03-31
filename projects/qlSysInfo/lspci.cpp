#include <stdio.h>
#include "systeminfo.h"

#define KEY_HOST "Host"
#define KEY_VGA "VGA"
#define KEY_AUDIO "Audio"
#define KEY_ETHERNET "Ethernet"
#define KEY_NETWORK "Network"

//type - line count, host bridge one, other can be 2
bool makeCorrectingLspci (const char *buf, QString &res, int type){
    if (!buf) return 0;

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

    lspciList << KEY_HOST << KEY_VGA << KEY_AUDIO << KEY_ETHERNET << KEY_NETWORK;

    for (int i=0; i < lspciList.size(); i++){
        sprintf (path, "%s | grep %s", LSPCI, lspciList[i].toStdString().c_str());

        FILE *fd = popen (path, "r");
        if (fd){
            memset (buf, 0, sizeof(buf));
            fread (buf, BUF_MAX_SIZE-1, 1, fd);
            //qDebug () << buf;
            makeCorrectingLspci (buf, lspciInfo_[lspciList[i]], i==0? 1 : 2);

            fclose (fd);
        }
    }

    return 1;
}

QString&
SystemInfo::GetChipset (){ return lspciInfo_[KEY_HOST];}

QString&
SystemInfo::GetVideocard (){ return lspciInfo_[KEY_VGA];}

QString&
SystemInfo::GetAudiocard (){ return lspciInfo_[KEY_AUDIO];}

QString&
SystemInfo::GetEthernet (){ return lspciInfo_[KEY_ETHERNET];}

QString&
SystemInfo::GetNetwork (){ return lspciInfo_[KEY_NETWORK];}

#include <fstream>
#include "systeminfo.h"

#define PROC_CPUINFO "/proc/cpuinfo"
//#define PROC_MEMINFO "/proc/meminfo"

#define CPU_BUF_MAX_SIZE 512
void ParseCpuInfo (std::ifstream &in, QHash <QString, QString> &map, QVector<QString> &names){
    int count=0;
    char line[CPU_BUF_MAX_SIZE];
    int values = names.size();

    while (!in.eof() && count < values){
        in.getline (line, CPU_BUF_MAX_SIZE-1, '\n');

        if (strlen(line)<2) break;

        for (int i=0; i < values; i++){
            const char *pItem=(names[i]).toStdString().c_str();
            if (strstr (line, pItem)){
                char *p=line+strlen(pItem);
                while  (*p !=':') *p++;
                while  (*p ==':' || *p ==' ') *p++;

                map[names[i]]=p;
                count++;

                break;
            }
        }
    }
}

bool
SystemInfo::
LoadCpuInfo (){
    cpuKeys_ << "vendor_id" << "model name" << "cpu cores" << "cpu MHz" << "cache size" << "bogomips" << "family" << "model" << "stepping";

    std::ifstream in (PROC_CPUINFO);

    if (in){
        ParseCpuInfo (in, cpuMap_, cpuKeys_);
        in.close();
        //qDebug()<<cpuMap_;

        return 1;
    }

    return 0;
}

QString&
SystemInfo::
GetCpuInfo (int ind){
    if (ind<0 || ind>=cpuKeys_.size()) ind=0;
    return cpuMap_[cpuKeys_[ind]];
}

QString&
SystemInfo::GetCpuVendor (){ return cpuMap_[cpuKeys_[0]];}

QString&
SystemInfo::GetCpuModelName (){ return cpuMap_[cpuKeys_[1]];}

QString&
SystemInfo::GetCpuCores (){ return cpuMap_[cpuKeys_[2]];}

QString&
SystemInfo::GetCpuCoreClock (){ return cpuMap_[cpuKeys_[3]];}

QString&
SystemInfo::GetCpuCacheSize (){ return cpuMap_[cpuKeys_[4]];}

QString&
SystemInfo::GetCpuBogomips (){ return cpuMap_[cpuKeys_[5]];}

QString&
SystemInfo::GetCpuFamily (){ return cpuMap_[cpuKeys_[6]];}

QString&
SystemInfo::GetCpuModel (){ return cpuMap_[cpuKeys_[7]];}

QString&
SystemInfo::GetCpuStepping (){ return cpuMap_[cpuKeys_[8]];}

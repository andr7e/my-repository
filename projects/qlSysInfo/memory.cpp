#include <sys/sysinfo.h>
#include "systeminfo.h"

bool
SystemInfo::
LoadMemoryInfo (){
    struct sysinfo sys_info;

    if (!sysinfo (&sys_info)){
        totalMem_=(quint32)(sys_info.totalram/1024*sys_info.mem_unit/1024);
        freeMem_=(quint32)(sys_info.freeram/1024*sys_info.mem_unit/1024);
        totalSwap_=(quint32)(sys_info.totalswap/1024*sys_info.mem_unit/1024);
        freeSwap_=(quint32)(sys_info.freeswap/1024*sys_info.mem_unit/1024);

        //qDebug()<<sys_info.mem_unit; // 1 - x86_64, 4096 - i686

        return 1;
    }

    return 0;
}

quint32
SystemInfo::GetTotalMemory(){ return totalMem_;}

quint32
SystemInfo::GetFreeMemory(){ return freeMem_;}

quint32
SystemInfo:: GetTotalSwap(){ return totalSwap_;}

quint32
SystemInfo::GetFreeSwap(){ return freeSwap_;}

quint32
SystemInfo::
GetMemoryInfo (int ind){
    switch (ind){
        case 0:    return totalMem_;
        case 1:    return freeMem_;
        case 2:    return totalSwap_;
        case 3:    return freeSwap_;
        default: return 0;
    }
}




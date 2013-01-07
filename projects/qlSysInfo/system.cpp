#include <sys/utsname.h>
#include "systeminfo.h"

bool
SystemInfo::
LoadSystemInfo (){
    utsname info;
    if (!uname (&info)){
        kernel_.sprintf ("%s %s", info.sysname, info.release);
        kversion_=(info.version);
        arch_=(info.machine);
        hostname_=(info.nodename);

        return 1;
    }

    return 0;
}

QString&
SystemInfo::GetHostname (){ return hostname_;}

QString&
SystemInfo::GetKernel (){ return kernel_;}

QString&
SystemInfo::GetKVersion (){ return kversion_;}

QString&
SystemInfo::GetArch (){ return arch_;}

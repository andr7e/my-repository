#include <fstream>
#include "systeminfo.h"

#define ETC_RELEASE "/etc/lsb-release"

bool
SystemInfo::
LoadReleaseInfo (){
    const char *release_name[]={"DISTRIB_ID=", "DISTRIB_RELEASE=", "DISTRIB_CODENAME="};

    std::ifstream in (ETC_RELEASE);

    if (in){
        char line[256];

        in.getline (line, 255, '\n');
        if (strstr (line, release_name[0])){
            distroName_=(line+strlen(release_name[0]));
        }

        in.getline (line, 255, '\n');
        if (strstr (line, release_name[1])){
            releaseName_ =(line+strlen(release_name[1]));
        }

        in.getline (line, 255, '\n');
        if (strstr (line, release_name[2])){
            releaseName_.append (" ");
            releaseName_.append (line+strlen(release_name[2]));
        }

        return 1;
    }

    in.close();

    return 0;
}

QString&
SystemInfo::GetDistroName (){ return distroName_;}

QString&
SystemInfo::GetReleaseName (){ return releaseName_;}

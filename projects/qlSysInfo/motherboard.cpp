#include <fstream>
#include "systeminfo.h"

#define MOBO_BASE "/sys/devices/virtual/dmi/id/"

bool GetLineFromFile (const char *fname, char *line){
    std::ifstream in (fname);

    if (in){
        in.getline (line, 255, '\n');
        in.close();
        return 1;
    }

    return 0;
}

bool GetMoboInfo (const char *value, char *line){
    char path[256];
    sprintf (path, "%s%s", MOBO_BASE, value);

    return GetLineFromFile (path, line);
}

bool
SystemInfo::
LoadMotherboardInfo (){
    QVector <QString> mobo;
    mobo << "board_vendor" << "board_name" << "bios_vendor" << "bios_version" << "bios_date";
    char tmp[256];

    for (int i=0; i<mobo.size(); i++){
        GetMoboInfo (mobo[i].toStdString().c_str(), tmp);
        motherBoard_[i] = (tmp);
    }

    return 1;
}

QString&
SystemInfo::GetMotherboardInfo (int ind){
    if (ind<0 || ind>=5) ind=0;
    return motherBoard_[ind];
}

QString&
SystemInfo::GetMotherboardManufacturer (){ return motherBoard_[0];}

QString&
SystemInfo::GetMotherboardModel (){ return motherBoard_[1];}

QString&
SystemInfo::GetBiosVendor (){ return motherBoard_[2];}

QString&
SystemInfo::GetBiosVersion (){ return motherBoard_[3];}

QString&
SystemInfo::GetBiosDate (){ return motherBoard_[4];}





#include <fstream>
#include "systeminfo.h"

#define KEY_BOARD_VENDOR "board_vendor"
#define KEY_BOARD_NAME "board_name"
#define KEY_BIOS_VENDOR "bios_vendor"
#define KEY_BIOS_VER "bios_version"
#define KEY_BIOS_DATE "bios_date"

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

bool GetMoboInfo (const char *key, char *value){
    char path[256];
    sprintf (path, "%s%s", MOBO_BASE, key);

    return GetLineFromFile (path, value);
}

bool
SystemInfo::
LoadMotherboardInfo (){
    QVector <QString> mobo;
    mobo << KEY_BOARD_VENDOR << KEY_BOARD_NAME << KEY_BIOS_VENDOR << KEY_BIOS_VER << KEY_BIOS_DATE;

    char tmp[256];

    for (int i=0; i < mobo.size(); i++){
        QString key = mobo[i];
        GetMoboInfo (key.toStdString().c_str(), tmp);
        motherBoard_[key] = (tmp);
    }

    return 1;
}

QString&
SystemInfo::GetMotherboardManufacturer (){ return motherBoard_[KEY_BOARD_VENDOR];}

QString&
SystemInfo::GetMotherboardModel (){ return motherBoard_[KEY_BOARD_NAME];}

QString&
SystemInfo::GetBiosVendor (){ return motherBoard_[KEY_BIOS_VENDOR];}

QString&
SystemInfo::GetBiosVersion (){ return motherBoard_[KEY_BIOS_VER];}

QString&
SystemInfo::GetBiosDate (){ return motherBoard_[KEY_BIOS_DATE];}





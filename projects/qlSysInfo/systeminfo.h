#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
class SystemInfo;
}

class SystemInfo : public QMainWindow
{
    Q_OBJECT

private:
    Ui::SystemInfo *ui;

    //ReleaseInfo
    QString distroName_;
    QString releaseName_;

    //MotherboardInfo
    QHash <QString, QString> motherBoard_;

    //MemoryInfo
    quint32 totalMem_;
    quint32 freeMem_;
    quint32 totalSwap_;
    quint32 freeSwap_;

    //SysInfo
    QString hostname_;
    QString kernel_;
    QString kversion_;
    QString arch_;

    //LspciInfo
    QHash <QString, QString> lspciInfo_;

    //CpuInfo
    QHash <QString, QString> cpuMap_;
    QVector <QString> cpuKeys_;

    //Resolution
    quint32 screenW_;
    quint32 screenH_;

public:
    explicit SystemInfo(QWidget *parent = 0);
    ~SystemInfo();

    //Release
    QString& GetDistroName ();
    QString& GetReleaseName ();

    //Memory
    quint32 GetTotalMemory();
    quint32 GetFreeMemory();
    quint32 GetTotalSwap();
    quint32 GetFreeSwap();

    //System
    QString& GetHostname ();
    QString& GetKernel ();
    QString& GetKVersion ();
    QString& GetArch ();

    //Lspci
    QString& GetChipset ();
    QString& GetVideocard ();
    QString& GetAudiocard ();
    QString& GetEthernet ();
    QString& GetNetwork ();

    //Cpu
    QString& GetCpuVendor ();
    QString& GetCpuModelName ();
    QString& GetCpuCores ();
    QString& GetCpuCoreClock ();
    QString& GetCpuCacheSize ();
    QString& GetCpuBogomips ();
    QString& GetCpuFamily ();
    QString& GetCpuModel ();
    QString& GetCpuStepping ();

    //Motherboard
    QString& GetMotherboardManufacturer ();
    QString& GetMotherboardModel ();

    QString& GetBiosVendor ();
    QString& GetBiosVersion ();
    QString& GetBiosDate ();

    //Multi
    QString& GetMotherboardInfo (int ind);
    quint32 GetMemoryInfo (int ind);
    QString& GetCpuInfo (int ind);

    bool LoadReleaseInfo ();
    bool LoadMotherboardInfo ();
    bool LoadMemoryInfo ();
    bool LoadSystemInfo ();
    bool LoadLspciInfo ();
    bool LoadCpuInfo ();
};

#endif // SYSTEMINFO_H

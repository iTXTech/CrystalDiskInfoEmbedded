#pragma once

#include "AtaSmart.h"
#include "NVMeInterpreter.h"

extern "C" __declspec(dllexport) CAtaSmart* CreateAtaSmart()
{
	auto ata = new CAtaSmart;
	ata->SetAtaPassThroughSmart(TRUE);
	ata->FlagUsbSat = TRUE;
	ata->FlagUsbIodata = TRUE;
	ata->FlagUsbSunplus = TRUE;
	ata->FlagUsbLogitec = TRUE;
	ata->FlagUsbProlific = TRUE;
	ata->FlagUsbJmicron = TRUE;
	ata->FlagUsbCypress = TRUE;
	ata->FlagUsbASM1352R = TRUE;
	ata->FlagUsbMemory = TRUE;
	ata->FlagUsbNVMeJMicron = TRUE;
	ata->FlagUsbNVMeASMedia = TRUE;
	ata->FlagUsbNVMeRealtek = TRUE;
	ata->FlagMegaRAID = TRUE;
	return ata;
}

extern "C" __declspec(dllexport) void DestroyAtaSmart(CAtaSmart* ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

extern "C" __declspec(dllexport) void InitAtaSmart(CAtaSmart* ptr, bool useWmi, bool advancedDiskSearch,
                                                   bool flagChangeDisk, bool workaroundHD204UI, bool workaroundAdataSsd,
                                                   bool flagHideNoSmartDisk)
{
	auto flagCD = flagChangeDisk ? TRUE : FALSE;
	ptr->Init(useWmi ? TRUE : FALSE, advancedDiskSearch ? TRUE : FALSE, &flagCD, workaroundHD204UI ? TRUE : FALSE,
	          workaroundAdataSsd ? TRUE : FALSE, flagHideNoSmartDisk ? TRUE : FALSE);
}

char* csToString(CString str)
{
	auto len = str.GetLength() + 1;
	auto buff = new TCHAR[len];
	memcpy(buff, (LPCTSTR)str, sizeof(TCHAR) * (len));
	char* charBuf = new char[len];
	size_t converted;
	wcstombs_s(&converted, charBuf, len, buff, len);
	return charBuf;
}

extern "C" __declspec(dllexport) int GetPhysicalDriveId(CAtaSmart* ptr, int index)
{
	return ptr->vars[index].PhysicalDriveId;
}

extern "C" __declspec(dllexport) int GetInterfaceType(CAtaSmart* ptr, int index)
{
	return ptr->vars[index].InterfaceType;
}

extern "C" __declspec(dllexport) char* GetModel(CAtaSmart* ptr, int index)
{
	return csToString(ptr->vars[index].Model);
}

extern "C" __declspec(dllexport) char* GetSerialNumber(CAtaSmart* ptr, int index)
{
	return csToString(ptr->vars[index].SerialNumber);
}

extern "C" __declspec(dllexport) char* GetFirmware(CAtaSmart* ptr, int index)
{
	return csToString(ptr->vars[index].FirmwareRev);
}

extern "C" __declspec(dllexport) _SMART_ATTRIBUTE* GetSmart(CAtaSmart* ptr, int index)
{
	return ptr->vars[index].Attribute;
}

extern "C" __declspec(dllexport) int GetDiskCount(CAtaSmart* ptr)
{
	return ptr->vars.GetCount();
}

#pragma once

#include "ScaleSetupDialog.h";
#include "vector";
#include "array";
#include "cTime";


class MetaDataSaveLoad
{
public:
	MetaDataSaveLoad();
	~MetaDataSaveLoad();
	static bool WriteMetaData(FlyCapture2::Camera* pCam, CString filePath, CString description);
	static void ReadMetaData(FlyCapture2::Camera* pCam, CString filePath);
private:
	static CString cameraModel;
	static CString timeStamp;
	static CString preset;
	static CString description;
	static std::vector<std::array<CString,5>> properties;
	static CString videoMode;
	static CString frameRate;
	static CString format7[7];
};


#include "stdafx.h"
#include "MetaDataSaveLoad.h"
#include "MetadataLoadDialog.h"
#include "MetadataConfirmationDialog.h"


MetaDataSaveLoad::MetaDataSaveLoad()
{
}


MetaDataSaveLoad::~MetaDataSaveLoad()
{
}

CString MetaDataSaveLoad::cameraModel = "ERROR!";
CString MetaDataSaveLoad::timeStamp = "ERROR!";
CString MetaDataSaveLoad::preset = "ERROR!";
CString MetaDataSaveLoad::description = "ERROR!";
std::vector<std::array<CString, 5>> MetaDataSaveLoad::properties;
CString MetaDataSaveLoad::videoMode = "ERROR!";
CString MetaDataSaveLoad::frameRate = "ERROR!";
CString MetaDataSaveLoad::format7[7] = { "ERROR!","ERROR!","ERROR!","ERROR!","ERROR!","ERROR!","ERROR!" };

FlyCapture2::PropertyType propTypes[18] = {
	FlyCapture2::BRIGHTNESS, FlyCapture2::AUTO_EXPOSURE, FlyCapture2::SHARPNESS, FlyCapture2::WHITE_BALANCE,
	FlyCapture2::HUE, FlyCapture2::SATURATION, FlyCapture2::GAMMA, FlyCapture2::IRIS, FlyCapture2::FOCUS,
	FlyCapture2::ZOOM, FlyCapture2::PAN, FlyCapture2::TILT, FlyCapture2::SHUTTER, FlyCapture2::GAIN,
	FlyCapture2::TRIGGER_MODE, FlyCapture2::TRIGGER_DELAY, FlyCapture2::FRAME_RATE, FlyCapture2::TEMPERATURE };
CString propStrings[18] = {
	"BRIGHTNESS", "AUTO_EXPOSURE", "SHARPNESS", "WHITE_BALANCE", "HUE", "SATURATION", "GAMMA", "IRIS", "FOCUS",
	"ZOOM", "PAN", "TILT", "SHUTTER", "GAIN", "TRIGGER_MODE", "TRIGGER_DELAY", "FRAME_RATE", "TEMPERATURE" };

FlyCapture2::VideoMode videoModes[24] = {
	FlyCapture2::VIDEOMODE_160x120YUV444, FlyCapture2::VIDEOMODE_320x240YUV422, FlyCapture2::VIDEOMODE_640x480YUV411,
	FlyCapture2::VIDEOMODE_640x480YUV422, FlyCapture2::VIDEOMODE_640x480RGB, FlyCapture2::VIDEOMODE_640x480Y8,
	FlyCapture2::VIDEOMODE_640x480Y16, FlyCapture2::VIDEOMODE_800x600YUV422, FlyCapture2::VIDEOMODE_800x600RGB,
	FlyCapture2::VIDEOMODE_800x600Y8, FlyCapture2::VIDEOMODE_800x600Y16, FlyCapture2::VIDEOMODE_1024x768YUV422,
	FlyCapture2::VIDEOMODE_1024x768RGB, FlyCapture2::VIDEOMODE_1024x768Y8, FlyCapture2::VIDEOMODE_1024x768Y16,
	FlyCapture2::VIDEOMODE_1280x960YUV422, FlyCapture2::VIDEOMODE_1280x960RGB, FlyCapture2::VIDEOMODE_1280x960Y8,
	FlyCapture2::VIDEOMODE_1280x960Y16, FlyCapture2::VIDEOMODE_1600x1200YUV422, FlyCapture2::VIDEOMODE_1600x1200RGB,
	FlyCapture2::VIDEOMODE_1600x1200Y8, FlyCapture2::VIDEOMODE_1600x1200Y16, FlyCapture2::VIDEOMODE_FORMAT7 };
CString videoModeStrings[24] = {
	"160x120 YUV444", "320x240 YUV422", "640x480 YUV411", "640x480 YUV422", "640x480 24 - bit RGB", "640x480 8 - bit",
	"640x480 16 - bit", "800x600 YUV422", "800x600 RGB", "800x600 8 - bit", "800x600 16 - bit", "1024x768 YUV422",
	"1024x768 RGB", "1024x768 8 - bit", "1024x768 16 - bit", "1280x960 YUV422", "1280x960 RGB", "1280x960 8 - bit",
	"1280x960 16 - bit", "1600x1200 YUV422", "1600x1200 RGB", "1600x1200 8 - bit", "1600x1200 16 - bit", "Format7" };
FlyCapture2::FrameRate frameRates[9] = {
	FlyCapture2::FRAMERATE_1_875, FlyCapture2::FRAMERATE_3_75, FlyCapture2::FRAMERATE_7_5,
	FlyCapture2::FRAMERATE_15, FlyCapture2::FRAMERATE_30, FlyCapture2::FRAMERATE_60,
	FlyCapture2::FRAMERATE_120, FlyCapture2::FRAMERATE_240, FlyCapture2::FRAMERATE_FORMAT7 };
CString frameRateStrings[9] = {
	"1.875 fps", "3.75 fps", "7.5 fps", "15 fps", "30 fps", "60 fps", "120 fps", "240 fps", "Format7" };

FlyCapture2::PixelFormat pixelFormats[17] = {
	FlyCapture2::PIXEL_FORMAT_MONO8, FlyCapture2::PIXEL_FORMAT_411YUV8, FlyCapture2::PIXEL_FORMAT_422YUV8, FlyCapture2::PIXEL_FORMAT_444YUV8,
	FlyCapture2::PIXEL_FORMAT_RGB8, FlyCapture2::PIXEL_FORMAT_MONO16, FlyCapture2::PIXEL_FORMAT_RGB16, FlyCapture2::PIXEL_FORMAT_S_MONO16,
	FlyCapture2::PIXEL_FORMAT_S_RGB16, FlyCapture2::PIXEL_FORMAT_RAW8, FlyCapture2::PIXEL_FORMAT_RAW16, FlyCapture2::PIXEL_FORMAT_MONO12,
	FlyCapture2::PIXEL_FORMAT_RAW12, FlyCapture2::PIXEL_FORMAT_BGR, FlyCapture2::PIXEL_FORMAT_BGRU, FlyCapture2::PIXEL_FORMAT_RGB, FlyCapture2::PIXEL_FORMAT_RGBU };
CString pixelFormatStrings[17] = {
	"8 bits of mono information",       "YUV 4:1 : 1",                     "YUV 4 : 2 : 2",                    "YUV 4 : 4 : 4",
	"R = G = B = 8 bits",               "16 bits of mono information",     "R = G = B = 16 bits",              "16 bits of signed mono information",
	"R = G = B = 16 bits signed",       "8 bit raw data output of sensor", "16 bit raw data output of sensor", "12 bits of mono information",
	"12 bit raw data output of sensor", "24 bit BGR",                      "32 bit BGRU",                      "24 bit RGB",                         "32 bit RGBU" };

bool MetaDataSaveLoad::WriteMetaData(FlyCapture2::Camera* pCam, CString filePath, CString description)
{
	std::ofstream fileOut;
	fileOut.open(filePath+".txt", std::ios_base::out);
	if (fileOut.is_open())
	{
		FlyCapture2::CameraInfo camInfo;
		pCam->GetCameraInfo(&camInfo);
		fileOut << camInfo.modelName << " (" << camInfo.serialNumber <<")" <<"\r\n\r\n";
		time_t now = time(0);
		timeStamp = ctime(&now);
		fileOut << timeStamp << "\r\n\r\n";
		fileOut << "\"" << description << "\"" << "\r\n\r\n";
		fileOut << "Preset," << ScaleSetupDialog::preset << "\r\n\r\n";

		FlyCapture2::Property camProp;
		FlyCapture2::PropertyInfo camPropInfo;
		fileOut << "Property,Value,On/Off,Auto/Manual,One Push\r\n";
		for (int i = 0; i<18; i++)
		{
			camPropInfo.type = propTypes[i];
			pCam->GetPropertyInfo(&camPropInfo);
			camProp.type = propTypes[i];
			pCam->GetProperty(&camProp);
			if (camProp.present)
			{
				switch (camPropInfo.absValSupported)
				{
					case true:
						fileOut << propStrings[i]
						<< "," << camProp.absValue << " " << camPropInfo.pUnitAbbr
						<< "," << camProp.onOff << "," << camProp.autoManualMode << "," << camProp.onePush << "\r\n";
						break;
					case false:
						fileOut << propStrings[i]
						<< "," << ( camProp.type == FlyCapture2::WHITE_BALANCE ? std::to_string(camProp.valueA)+"/"+std::to_string(camProp.valueB) : std::to_string(camProp.valueA) )
						<< "," << camProp.onOff << "," << camProp.autoManualMode << "," << camProp.onePush << "\r\n";
						break;
				}
			}
		}
		fileOut << "\r\n";

		fileOut << "Property,Value\r\n";
		FlyCapture2::VideoMode videoMode;
		FlyCapture2::FrameRate frameRate;
		pCam->GetVideoModeAndFrameRate(&videoMode, &frameRate);
		fileOut << "Video Mode," << videoModeStrings[videoMode] << "\r\n";
		fileOut << "Frame Rate," << frameRateStrings[frameRate] << "\r\n";
		fileOut << "\r\n";

		fileOut << "Format7 Property,Value\r\n";
		FlyCapture2::Format7ImageSettings format7Settings;
		unsigned int packetSize;
		float packetSizePercent;
		pCam->GetFormat7Configuration(&format7Settings, &packetSize, &packetSizePercent);
		fileOut << "Mode," << format7Settings.mode << "\r\n";
		fileOut << "XOffset," << format7Settings.offsetX << "\r\n";
		fileOut << "YOffset," << format7Settings.offsetY << "\r\n";
		fileOut << "Width," << format7Settings.width << "\r\n";
		fileOut << "Height," << format7Settings.height << "\r\n";
		fileOut << "Pixel Format," << pixelFormatStrings[std::distance(pixelFormats, std::find(pixelFormats, pixelFormats+17, format7Settings.pixelFormat))] << "\r\n";
		fileOut << "Packet Size," << packetSize;
	}
	fileOut.close();
	
	std::ifstream fileIn;
	fileIn.open(filePath + ".txt", std::ios_base::in);
	if (fileIn.is_open())
	{
		std::stringstream buffer;
		buffer << fileIn.rdbuf();
		std::string content(buffer.str());
		MetadataConfirmationDialog MetadataConfirmDlg(buffer.str(), filePath);
		fileIn.close();
		INT_PTR nRet = MetadataConfirmDlg.DoModal();
		if (nRet == IDOK)
		{
			fileOut.open(filePath + ".txt", std::ios_base::out | std::ios_base::trunc);
			if (fileOut.is_open())
			{
				fileOut << MetadataConfirmDlg.Metadata;
				fileOut.close();
			}
			return true;
		}
		std::remove(filePath + ".txt");
		if (nRet == MetadataConfirmDlg.IDCANCELSAVE)
		{
			return false;
		}
		return true;
	}
	return true;
}


void MetaDataSaveLoad::ReadMetaData(FlyCapture2::Camera* pCam, CString filePath)
{
	cameraModel = "ERROR!";
	timeStamp = "ERROR!";
	preset = "ERROR!";
	description = "ERROR!";
	properties.clear();
	videoMode = "ERROR!";
	frameRate = "ERROR!";
	for (int i = 0; i < 7; i++)
	{
		format7[i] = "ERROR!";
	}

	std::ifstream fileIn;
	fileIn.open(filePath, std::ios_base::in);
	if (fileIn.is_open())
	{
		std::stringstream buffer;
		buffer << fileIn.rdbuf();
		MetadataLoadDialog MetadataLoadDlg(buffer.str(), filePath);
		if (MetadataLoadDlg.DoModal()!=IDOK)
		{
			return;
		}

		std::string line;
		std::stringstream lineIn;
		
		getline(buffer, line, '\r');
		if (line.size() == 0) { return; }
		buffer.get();
		lineIn << line;
		getline(lineIn, line, '(');
		line.substr(0,line.length()-2);
		cameraModel = line.c_str();
		buffer.get();
		buffer.get();
		lineIn.clear();
		lineIn.str("");
		getline(buffer, line, '\r');
		buffer.get();
		timeStamp = line.c_str();
		buffer.get();
		buffer.get();
		lineIn.clear();
		lineIn.str("");

		while (!buffer.eof())
		{
			getline(buffer, line, '\r');
			buffer.get();
			lineIn << line;
			if (buffer.peek() == '\r')
			{
				buffer.get();
				buffer.get();
				break;
			}
		}

		description = lineIn.rdbuf()->str().c_str();
		description.Mid(1, description.GetLength()-2);
		
		if (!buffer.eof())
		{
			lineIn.clear();
			lineIn.str("");
			getline(buffer, line, '\r');
			buffer.get();
			lineIn << line;
			getline(lineIn, line, ',');
			getline(lineIn, line, '\r');
			preset = line.c_str();
			buffer.get();
			buffer.get();
		}

		while (!buffer.eof())
		{
			lineIn.clear();
			lineIn.str("");
			getline(buffer, line, '\r');
			buffer.get();
			lineIn << line;
			std::array<CString, 5> property;
			getline(lineIn, line, ',');
			property[0] = line.c_str();
			getline(lineIn, line, ',');
			property[1] = line.c_str();
			getline(lineIn, line, ',');
			property[2] = line.c_str();
			getline(lineIn, line, ',');
			property[3] = line.c_str();
			getline(lineIn, line, '\r');
			property[4] = line.c_str();
			properties.push_back(property);
			if (buffer.peek()=='\r') { break; }
		}
		buffer.get();
		buffer.get();
		getline(buffer, line, '\r');
		buffer.get();

		lineIn.clear();
		lineIn.str("");
		getline(buffer, line, '\r');
		buffer.get();
		lineIn << line;
		getline(lineIn, line, ',');
		getline(lineIn, line, '\r');
		videoMode = line.c_str();
		lineIn.clear();
		lineIn.str("");
		getline(buffer, line, '\r');
		buffer.get();
		lineIn << line;
		getline(lineIn, line, ',');
		getline(lineIn, line, '\r');
		frameRate = line.c_str();
		buffer.get();
		buffer.get();
		getline(buffer, line, '\r');
		buffer.get();

		for (int i=0; !buffer.eof() && i<7; i++)
		{
			lineIn.clear();
			lineIn.str("");
			getline(buffer, line, '\r');
			buffer.get();
			lineIn << line;
			getline(lineIn, line, ',');
			getline(lineIn, line, '\r');
			format7[i] = line.c_str();
		}

		pCam->StopCapture();

		ScaleSetupDialog::preset = preset;
		for (int i = 0; i<properties.size(); i++)
		{
			FlyCapture2::Property prop;
			prop.type = 
				propTypes[std::distance(propStrings, std::find(propStrings, propStrings + 18, properties[i][0]))];
			if (prop.type == FlyCapture2::WHITE_BALANCE)
			{
				prop.absControl = false;
				prop.valueA = (unsigned int) atoi(properties[i][1].Left(properties[i][1].Find('/')));
				prop.valueB = (unsigned int) atoi(properties[i][1].Mid(properties[i][1].Find('/')+1));
			}
			else if (properties[i][1].Find(" ")==-1)
			{
				prop.absControl = false;
				prop.valueA = atoi(properties[i][1]);
			}
			else
			{
				prop.absControl = true;
				prop.absValue = strtof(properties[i][1], NULL);
			}
			prop.onOff = atoi(properties[i][2]);
			prop.autoManualMode = atoi(properties[i][3]);
			prop.onePush = atoi(properties[i][4]);
			pCam->SetProperty(&prop);
		}
		pCam->SetVideoModeAndFrameRate(
			videoModes[std::distance(videoModeStrings, std::find(videoModeStrings, videoModeStrings + 24, videoMode))],
			frameRates[std::distance(frameRateStrings, std::find(frameRateStrings, frameRateStrings +9, frameRate))]);
		FlyCapture2::Format7ImageSettings format7ImageSettings;
		format7ImageSettings.mode = (FlyCapture2::Mode) atoi(format7[0]);
		format7ImageSettings.offsetX = atoi(format7[1]);
		format7ImageSettings.offsetY = atoi(format7[2]);
		format7ImageSettings.width = atoi(format7[3]);
		format7ImageSettings.height = atoi(format7[4]);
		format7ImageSettings.pixelFormat = 
			pixelFormats[std::distance(pixelFormatStrings, std::find(pixelFormatStrings, pixelFormatStrings + 17, format7[5]))];
		pCam->SetFormat7Configuration(&format7ImageSettings, (unsigned int) atoi(format7[6]));
		pCam->StartCapture();
	}
	fileIn.close();
}

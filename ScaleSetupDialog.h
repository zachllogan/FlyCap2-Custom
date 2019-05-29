#pragma once

#include <afxwin.h>
#include "Resource.h"
#include "afxcmn.h"
#include "vector"
#include "map"

// ScaleSetupDialog dialog

class ScaleSetupDialog : public CDialog
{
	DECLARE_DYNAMIC(ScaleSetupDialog)

public:
	ScaleSetupDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ScaleSetupDialog();

	/*double pxlSz;
	CString pxlSzUnt;
	BOOL drwSclOnLvFd;
	BOOL drwSclOnSvdFl;
	BOOL mjrTcks;
	double mjrTcksSz;
	CString mjrTcksSzUnt;
	BOOL mjrTcksLbls;
	BOOL mjrTcksGrd;
	BOOL mnrTcks;
	double mnrTcksSz;
	CString mnrTcksSzUnt;
	BOOL mnrTcksLbls;
	BOOL mnrTcksGrd;*/
	CComboBox presetControl;
	CMFCColorButton color;

	BOOL OnInitDialog();

	static void drawScaleBar(BITMAPINFOHEADER header, unsigned char* pImagePixels);
	static void loadConfig(FlyCapture2::CameraInfo camInfo, FlyCapture2::Format7Info modeInfo);
	static void createCompatibleDC(CDC* dc);

	static std::vector<std::string> presets;
	static std::map<unsigned int, std::map<unsigned int, std::map<std::string, double>>> config;
	static unsigned int cameraSerial;
	static unsigned int mode;
	static std::string preset;
	static double microns;
	static double micronsPerPixel;
	static bool configLoaded;
	static COLORREF clr;
	static bool drawScale;
	static CDC compatibleDC;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETUP_SCALE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

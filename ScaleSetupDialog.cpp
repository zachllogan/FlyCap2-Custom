// ScaleSetupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ScaleSetupDialog.h"
#include "afxdialogex.h"


// ScaleSetupDialog dialog

IMPLEMENT_DYNAMIC(ScaleSetupDialog, CDialog)

ScaleSetupDialog::ScaleSetupDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_SETUP_SCALE, pParent)
	, color()
	, presetControl()
{
}

ScaleSetupDialog::~ScaleSetupDialog()
{
}

BOOL ScaleSetupDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	for (int i = 0; i < presets.size(); i++)
	{
		presetControl.AddString(presets[i].c_str());
	}
	int temp = presetControl.FindStringExact(0, preset.c_str());
	if (temp == CB_ERR)	{ presetControl.SetCurSel(0); }
	else				{ presetControl.SetCurSel(temp); }
	color.SetColor(clr);
	return TRUE;
}

void ScaleSetupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCALE_COLOR_PICKER, color);
	DDX_Control(pDX, IDC_SCALE_MAG_COMBO, presetControl);
	if (pDX->m_bSaveAndValidate != 0)
	{
		CString temp;
		presetControl.GetLBText(presetControl.GetCurSel(), temp);
		preset = temp.GetString();
		clr = color.GetColor();
		micronsPerPixel = config[cameraSerial][mode][preset];
	}
}


BEGIN_MESSAGE_MAP(ScaleSetupDialog, CDialog)
END_MESSAGE_MAP()

void ScaleSetupDialog::loadConfig(FlyCapture2::CameraInfo camInfo, FlyCapture2::Format7Info modeInfo)
{
	ScaleSetupDialog::cameraSerial = camInfo.serialNumber;
	ScaleSetupDialog::mode = modeInfo.mode;
	std::ifstream fileIn;
	fileIn.open("./res/ScaleBarConfig.txt", std::ios_base::in);
	if (fileIn.is_open())
	{
		std::string line;
		std::stringstream lineIn;
		while (!fileIn.eof())
		{
			lineIn.clear();
			getline(fileIn, line, '\n');
			lineIn << line;
			std::string cameraSerial;
			std::string mode;
			std::string preset;
			std::string micronsPerPixel;
			getline(lineIn, cameraSerial, ';');
			getline(lineIn, mode, ';');
			getline(lineIn, preset, ';');
			getline(lineIn, micronsPerPixel, ';');
			ScaleSetupDialog::config[stoul(cameraSerial)][stoul(mode)][preset] = stod(micronsPerPixel);
			for (int i = 0;; i++)
			{
				if (i < presets.size())
				{
					bool temp = presets[i] == preset;
					if (temp) { break; }
					else { continue; }
				}
				ScaleSetupDialog::presets.push_back(preset);
				break;
			}
		}
		ScaleSetupDialog::configLoaded = true;
	}
}

void ScaleSetupDialog::drawScaleBar(BITMAPINFOHEADER header, unsigned char* pImagePixels)
{
		int width = header.biWidth;
		int height = ::abs(header.biHeight);

		CBitmap scaleDrawBitmap;
		scaleDrawBitmap.CreateBitmap(width, height, 1, header.biBitCount, pImagePixels);
		CBitmap* pOldBitmap = compatibleDC.SelectObject(&scaleDrawBitmap);
		
		CPen pen(PS_SOLID, 1, (((DWORD)(BYTE)(254)) << 24) | ScaleSetupDialog::clr);
		CPen* pOldPen = compatibleDC.SelectObject(&pen);

		int scaleBarMicrons = int(ScaleSetupDialog::micronsPerPixel*width*.20);
		int scaleBarPixels = int((1 / ScaleSetupDialog::micronsPerPixel)*scaleBarMicrons);

		for (int i = 0; i <= int(height*.05); i++)
		{
			compatibleDC.MoveTo(int(width - width*.025), int(height - height*.025) - i);
			compatibleDC.LineTo(int(width - width*.025) - scaleBarPixels, int(height - height*.025) - i);
		}

		CString scaleBarLabel;
		scaleBarLabel = (std::to_wstring(scaleBarMicrons).append(L"\u00b5m")).c_str();
		RECT ScaleBarLabelRect;
		RECT* pScaleBarLabelRect = &ScaleBarLabelRect;
		*pScaleBarLabelRect = { 0, int(height - height*.075), int(width - width*.035) - scaleBarPixels, int(height - height*.025) };

		CFont font;
		font.CreateFontA(height*.05, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, "Microsoft Sans Serif");
		CFont* pOldFont = compatibleDC.SelectObject(&font);

		COLORREF oldColor = compatibleDC.SetTextColor(clr);

		compatibleDC.DrawText(scaleBarLabel, pScaleBarLabelRect, DT_RIGHT | DT_VCENTER);

		BITMAP tempBITMAP;
		BITMAP* pTempBITMAP = &tempBITMAP;
		scaleDrawBitmap.GetBitmap(pTempBITMAP);
		scaleDrawBitmap.GetBitmapBits(tempBITMAP.bmHeight*tempBITMAP.bmWidthBytes, pImagePixels);

		for (int* currPixel = (int*)pImagePixels; currPixel < (int*)pImagePixels+(tempBITMAP.bmHeight*tempBITMAP.bmWidthBytes/4); currPixel++)
		{
			*currPixel |= 0xFF000000;
		}

		compatibleDC.SetTextColor(oldColor);
		compatibleDC.SelectObject(pOldFont);
		compatibleDC.SelectObject(pOldPen);
		compatibleDC.SelectObject(pOldBitmap);
		scaleDrawBitmap.DeleteObject();
}

void  ScaleSetupDialog::createCompatibleDC(CDC* dc)
{
	ScaleSetupDialog::compatibleDC.CreateCompatibleDC(dc);
	compatibleDC.SetBkMode(TRANSPARENT);
}

std::vector<std::string> ScaleSetupDialog::presets;
std::map<unsigned int, std::map<unsigned int, std::map<std::string, double>>> ScaleSetupDialog::config;
unsigned int ScaleSetupDialog::cameraSerial = 0;
unsigned int ScaleSetupDialog::mode = 0;
std::string ScaleSetupDialog::preset = "";
double ScaleSetupDialog::micronsPerPixel = 1;
bool ScaleSetupDialog::configLoaded = false;
COLORREF ScaleSetupDialog::clr = 0x00000000;
bool ScaleSetupDialog::drawScale = false;
CDC ScaleSetupDialog::compatibleDC;
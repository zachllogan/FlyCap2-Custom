#pragma once
#include "Resource.h"


// MetadataLoadDialog dialog

class MetadataLoadDialog : public CDialog
{
	DECLARE_DYNAMIC(MetadataLoadDialog)

public:
	MetadataLoadDialog(std::string metaData, CString file, CWnd* pParent = nullptr);   // standard constructor
	virtual ~MetadataLoadDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_METADATA_LOAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString MetadataFor;
	CString Metadata;
};

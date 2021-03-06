#pragma once
#include "Resource.h"

// MetadataConfirmationDialog dialog

class MetadataConfirmationDialog : public CDialog
{
	DECLARE_DYNAMIC(MetadataConfirmationDialog)

public:
	MetadataConfirmationDialog(std::string metaData, CString file, CWnd* pParent = nullptr);   // standard constructor
	virtual ~MetadataConfirmationDialog();

	const int IDCANCELSAVE = 15;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_METADATA_CONFIRMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancelSave();
public:
	CString Metadata;
	CString MetadataFor;
};

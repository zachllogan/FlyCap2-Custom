// MetadataLoadDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MetadataLoadDialog.h"
#include "afxdialogex.h"


// MetadataLoadDialog dialog

IMPLEMENT_DYNAMIC(MetadataLoadDialog, CDialog)

MetadataLoadDialog::MetadataLoadDialog(std::string metaData, CString file, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_METADATA_LOAD, pParent)
	, Metadata(_T(""))
	, MetadataFor(_T(""))
{
	Metadata = metaData.c_str();
	MetadataFor = file;
}

MetadataLoadDialog::~MetadataLoadDialog()
{
}

void MetadataLoadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_META_DATA_FOR_TEXT, MetadataFor);
	DDX_Text(pDX, IDC_EDIT_METADATA, Metadata);
}


BEGIN_MESSAGE_MAP(MetadataLoadDialog, CDialog)
END_MESSAGE_MAP()


// MetadataLoadDialog message handlers

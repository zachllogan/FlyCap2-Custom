// MetadataConfirmationDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MetadataConfirmationDialog.h"
#include "afxdialogex.h"


// MetadataConfirmationDialog dialog

IMPLEMENT_DYNAMIC(MetadataConfirmationDialog, CDialog)

MetadataConfirmationDialog::MetadataConfirmationDialog(std::string metaData, CString file, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_METADATA_CONFIRMATION, pParent)
	, Metadata(_T(""))
	, MetadataFor(_T(""))
{
	Metadata = metaData.c_str();
	MetadataFor = file;
}

MetadataConfirmationDialog::~MetadataConfirmationDialog()
{
}

void MetadataConfirmationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_METADATA, Metadata);
	DDX_Text(pDX, IDC_META_DATA_FOR_TEXT, MetadataFor);
}


BEGIN_MESSAGE_MAP(MetadataConfirmationDialog, CDialog)
	ON_BN_CLICKED(15, &MetadataConfirmationDialog::OnBnClickedCancelSave)
END_MESSAGE_MAP()


// MetadataConfirmationDialog message handlers


void MetadataConfirmationDialog::OnBnClickedCancelSave()
{
	this->EndDialog(IDCANCELSAVE);
}

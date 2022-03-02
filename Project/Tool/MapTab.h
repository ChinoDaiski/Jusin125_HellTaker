#pragma once
#include "afxwin.h"
#include "Include.h"
#include "BackGround.h"

// CMapTab ��ȭ �����Դϴ�.

class CMapTab : public CDialogEx
{
	DECLARE_DYNAMIC(CMapTab)

public:
	CMapTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

private:
	CComboBox m_MapComboBox;

private:
	// value

	// control
	map<CString, CImage*>		m_MapPngImage;
	CObj*		m_pBackGround = nullptr;

	// general
	afx_msg void OnMapComboBox();
	virtual BOOL OnInitDialog();

	void		Load_MapPreview();
	afx_msg void OnSaveButton();
	afx_msg void OnLoadButton();
};

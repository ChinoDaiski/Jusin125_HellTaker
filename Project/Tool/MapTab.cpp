// MapTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTab.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MyForm.h"
#include "ToolView.h"

#include "ObjMgr.h"

// CMapTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTab, CDialogEx)

CMapTab::CMapTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAPTAB, pParent)
{
	
}

CMapTab::~CMapTab()
{
}

void CMapTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_MapComboBox);
}


BEGIN_MESSAGE_MAP(CMapTab, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMapTab::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMapTab::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMapTab::OnMapComboBox)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTab::OnSaveButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTab::OnLoadButton)
END_MESSAGE_MAP()


// CMapTab �޽��� ó�����Դϴ�.


void CMapTab::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CMapTab::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnCancel();
}


void CMapTab::OnMapComboBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	Invalidate(FALSE);

	UpdateData(FALSE);
}


BOOL CMapTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pBackGround = CObjMgr::GetInstance()->Get_Terrain();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	TCHAR		szFullPath[MAX_PATH] = L"";

	for (int i = 0; i < 8; ++i)
	{
		wsprintf(szFullPath, L"%s%d", L"é��", i);
		m_MapComboBox.AddString(szFullPath);
	}

	Load_MapPreview();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMapTab::Load_MapPreview()
{
	// �˻��� ��� �� ����
	// Ư�� Ȯ���ڸ� ���� ������ �˻��ϰ� ������ '���/*.jpg' ������ ���
	CString tpath = _T("../Texture/BackGround/*.png");

	// �˻� Ŭ����
	CFileFind finder;

	// CFileFind�� ����, ���͸��� �����ϸ� TRUE �� ��ȯ��
	BOOL bWorking = finder.FindFile(tpath);

	CString fileName;
	CString DirName;

	while (bWorking)
	{
		//���� ���� or ���� �� �����ϸ�ٸ� TRUE ��ȯ
		bWorking = finder.FindNextFile();

		//������ �̸�
		CString _fileName = finder.GetFileName();

		// �������� �������� ����������� ����
		if (_fileName == _T("Thumbs.db")) continue;

		fileName = finder.GetFileTitle();

		auto	iter = m_MapPngImage.find(fileName);

		if (iter == m_MapPngImage.end())
		{
			CImage*		pPngImage = new CImage;
			pPngImage->Load(finder.GetFilePath());

			m_MapPngImage.emplace(fileName, pPngImage);
		}
	}
}

void CMapTab::OnSaveButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog	Dlg(FALSE,	// true�� ��� ���� ���, false �� ��� �ٸ� �̸����� ���� ���
		L"dat", // default ���� Ȯ���, ���� �� Ȯ���ڸ��� ��������� ������ ���� ������ Ȯ���ڸ��� ����ϰ� ������
		L"*.dat", // ��ȭ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б����� üũ�ڽ� ����), OFN_OVERWRITEPROMPT(�ߺ� ���� ���� �� ���޽��� ���� �ɼ�)
		L"Data File(*.dat)|*.dat||",	// ��ȭ ���ڿ� ǥ�õ� ���� ����, �޺��ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||
		this); // �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";

	// ���� ������Ʈ�� �ִ� ���丮 ��θ� ������ �Լ�
	GetCurrentDirectory(MAX_PATH, szPath);

	// ��ü ��ο��� �� ������ ��θ� �߶󳻴� �Լ�
	// ��� �� �� ������ ��ΰ� ���ϸ��̸� �� ���ϸ��� ������ ��θ� ����, ���� ���ϸ��� ������ ������ �������� �߶󳽴�.
	PathRemoveFileSpec(szPath);

	// data���� ��θ� �̾����
	lstrcat(szPath, L"\\Data");

	// ��ȭ���ڸ� ������ �� ���̴� �⺻ ��� ����, ���� ����� ��Ȳ
	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : ��ȭ ���ڸ� ����, IDOK ���� ����
	if (IDOK == Dlg.DoModal())
	{
		// GetPathName ���õ� ��θ� ��ȯ
		CString	strFind = Dlg.GetPathName();
		const TCHAR*	pGetPath = strFind.GetString();

		if (dynamic_cast<CBackGround*>(m_pBackGround)->SaveData())
			return;
	}
}

void CMapTab::OnLoadButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog	Dlg(FALSE,	// true�� ��� ���� ���, false �� ��� �ٸ� �̸����� ���� ���
		L"dat", // default ���� Ȯ���, ���� �� Ȯ���ڸ��� ��������� ������ ���� ������ Ȯ���ڸ��� ����ϰ� ������
		L"*.dat", // ��ȭ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б����� üũ�ڽ� ����), OFN_OVERWRITEPROMPT(�ߺ� ���� ���� �� ���޽��� ���� �ɼ�)
		L"Data File(*.dat)|*.dat||",	// ��ȭ ���ڿ� ǥ�õ� ���� ����, �޺��ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||
		this); // �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";

	// ���� ������Ʈ�� �ִ� ���丮 ��θ� ������ �Լ�
	GetCurrentDirectory(MAX_PATH, szPath);

	// ��ü ��ο��� �� ������ ��θ� �߶󳻴� �Լ�
	// ��� �� �� ������ ��ΰ� ���ϸ��̸� �� ���ϸ��� ������ ��θ� ����, ���� ���ϸ��� ������ ������ �������� �߶󳽴�.
	PathRemoveFileSpec(szPath);

	// data���� ��θ� �̾����
	lstrcat(szPath, L"\\Data");

	// ��ȭ���ڸ� ������ �� ���̴� �⺻ ��� ����, ���� ����� ��Ȳ
	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : ��ȭ ���ڸ� ����, IDOK ���� ����
	if (IDOK == Dlg.DoModal())
	{
		// GetPathName ���õ� ��θ� ��ȯ
		CString	strFind = Dlg.GetPathName();
		const TCHAR*	pGetPath = strFind.GetString();

		if (dynamic_cast<CBackGround*>(m_pBackGround)->LoadData())
			return;
	}
}
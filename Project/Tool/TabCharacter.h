#pragma once


// CTabCharacter 대화 상자입니다.

class CTabCharacter : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCharacter)

public:
	CTabCharacter(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabCharacter();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABCHARACTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

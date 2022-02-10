#pragma once


// CTabBrick 대화 상자입니다.

class CTabBrick : public CDialogEx
{
	DECLARE_DYNAMIC(CTabBrick)

public:
	CTabBrick(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabBrick();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABBRICK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

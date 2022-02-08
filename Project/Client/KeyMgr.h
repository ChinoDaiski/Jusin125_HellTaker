#pragma once

#include "Include.h"

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool		Key_Pressing(int iKey);
	bool		Key_Down(int iKey);
	bool		Key_Up(int iKey);

private:
	bool		m_bKeyState[VK_MAX];
};


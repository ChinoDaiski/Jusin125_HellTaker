#include "stdafx.h"
#include "Obj.h"
#include "TimeMgr.h"

D3DXVECTOR3 CObj::m_vScroll{};

CObj::CObj()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	ZeroMemory(&m_tFrame, sizeof(FRAME));

	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
}


CObj::~CObj()
{
}

void CObj::MoveFrame(void)
{
	// TODO : 1.3f 상수부분 변수로 변경할 것
	m_tFrame.fFrame += m_tFrame.fMax * (1.3f) * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;
}

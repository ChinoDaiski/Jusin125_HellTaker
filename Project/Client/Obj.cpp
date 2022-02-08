#include "stdafx.h"
#include "Obj.h"
#include "TimeMgr.h"

D3DXVECTOR3 CObj::m_vScroll{};

CObj::CObj()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	ZeroMemory(&m_tFrame, sizeof(FRAME));
	m_tFrame.fFrameSpeed = 1.3f;

	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
}


CObj::~CObj()
{
	// empty
}

void CObj::MoveFrame(void)
{
	m_tFrame.fFrame += m_tFrame.fMax * (m_tFrame.fFrameSpeed) * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;
}

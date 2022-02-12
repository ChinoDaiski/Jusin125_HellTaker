#include "stdafx.h"
#include "Obj.h"
#include "TimeMgr.h"

D3DXVECTOR3 CObj::m_vScroll{};

CObj::CObj()
	: m_bDead(false), m_iHp(10), m_ObjIndex(0)
	, m_Dir(DIR_END), m_GridState(GRID_END) 
	, m_fDistance(0.f), m_fAngle(0.f), moving(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	ZeroMemory(&m_tFrame, sizeof(FRAME));
	m_tFrame.fFrameSpeed = 1.3f;		// Default FrameSpeed

	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);

	m_vFlag = D3DXVECTOR3(0.f, 0.f, 0.f);
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

void CObj::Moving()
{
	m_tInfo.vDir = m_vFlag - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float		fDot = D3DXVec3Dot(&m_tInfo.vLook, &m_tInfo.vDir);

	m_fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < m_vFlag.y)
		m_fAngle = 2.f * D3DX_PI - m_fAngle;

	float	fWidth = m_vFlag.x - m_tInfo.vPos.x;
	float	fHeight = m_vFlag.y - m_tInfo.vPos.y;

	// 현재 거리 계산
	m_fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	if (10.f >= m_fDistance)
	{
		m_fDistance = 0.f;
		m_tInfo.vPos = m_vFlag;
		moving = false;
	}
	else
	{
		m_tInfo.vPos.x += m_fSpeed * cosf(m_fAngle) * CTimeMgr::GetInstance()->Get_TimeDelta();
		m_tInfo.vPos.y -= m_fSpeed * sinf(m_fAngle) * CTimeMgr::GetInstance()->Get_TimeDelta();
	}
}
#include "stdafx.h"
#include "Transition.h"

#include "ObjMgr.h"
#include "TimeMgr.h"

CTransition::CTransition()
	: m_fTimeDelta(0.f)
{
	// empty
}

CTransition::~CTransition()
{
	Release();
}

HRESULT CTransition::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Transition/transition%d.png", L"Transition", L"Idle", 29)))
		return S_FALSE;

	m_wstrObjKey = L"Transition";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 29.f, 0.4f };

	return S_OK;
}

void CTransition::Late_Update(void)
{
	if(16 != (int)m_tFrame.fFrame)
		MoveFrame();
	else
	{
		m_fTimeDelta += 4.5f * CTimeMgr::GetInstance()->Get_TimeDelta();

		if (4.f <= m_fTimeDelta)
		{
			m_tFrame.fFrame += 1.f;
			m_fTimeDelta = 0.f;
		}
	}

	// 프레임이 끝나면 이펙트 객체 삭제
	if (m_tFrame.fMax - 0.5f < m_tFrame.fFrame)
		m_bDead = true;
}
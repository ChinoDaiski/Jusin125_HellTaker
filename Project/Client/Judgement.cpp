#include "stdafx.h"
#include "Judgement.h"
#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

CJudgement::CJudgement()
{
	// empty
}

CJudgement::~CJudgement()
{
	Release();
}

HRESULT CJudgement::Initialize(void)
{
	// Idle
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Judgement/Idle/Idle%d.png", L"Judgement", L"Idle", 12)))
		return S_FALSE;

	// Jump
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Judgement/Jump/Jump%d.png", L"Judgement", L"Jump", 9)))
		return S_FALSE;

	m_wstrObjKey = L"Judgement";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	Create_LoveSign();
	Set_Jump();

	return S_OK;
}

int CJudgement::Update(void)
{
	if (m_Jump && (0 == m_tFrame.fFrame))
		m_tInfo.vPos.y += 450.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	D3DXMATRIX	matTrans, matScale;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	D3DXMatrixScaling(&matScale, MAPSIZEX, MAPSIZEY, 1.f);

	m_tInfo.matWorld = matScale * matTrans;

	return OBJ_NOEVENT;
}

void CJudgement::Late_Update(void)
{
	// Jump Frame
	if (m_Jump)
	{
		if (m_tInfo.vPos.y >= 500)
		{
			// Jump Frame End
			if (m_tFrame.fFrame > 8.f)
			{
				m_Jump = false;
				m_tFrame.fFrame = 0.f;
				m_tFrame = { 0.f, 12.f };
				m_wstrStateKey = L"Idle";
			}
			else
				MoveFrame();
		}
	}
	// Idle Frame
	else
		MoveFrame();
}

void CJudgement::Set_Jump()
{
	m_Jump = true;
	m_tFrame = { 0.f, 9.f };
	m_wstrStateKey = L"Jump";
}

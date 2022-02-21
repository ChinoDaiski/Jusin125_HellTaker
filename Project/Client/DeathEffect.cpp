#include "stdafx.h"
#include "DeathEffect.h"
#include "DeathBackGround.h"

#include "ObjMgr.h"

CDeathEffect::CDeathEffect()
	: m_pDeathBackGround(nullptr)
{
	// empty
}

CDeathEffect::~CDeathEffect()
{
	Release();
}

void CDeathEffect::Create_DeathBackGround()
{
	m_pDeathBackGround = new CDeathBackGround;
	m_pDeathBackGround->Initialize();
	m_pDeathBackGround->Set_Pos(D3DXVECTOR3{ WINCX >> 1, WINCY >> 1, 0.f });

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, m_pDeathBackGround);
}

HRESULT CDeathEffect::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Death/death%d.png", L"Death", L"Idle", 18)))
		return S_FALSE;

	m_wstrObjKey = L"Death";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 18.f, 0.4f };

	Create_DeathBackGround();

	return S_OK;
}

int CDeathEffect::Update(void)
{
	if (true == m_bDead)
	{
		m_pDeathBackGround->Set_Dead(true);
		return OBJ_DEAD;
	}

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

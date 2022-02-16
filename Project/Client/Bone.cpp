#include "stdafx.h"
#include "Bone.h"

#include "TimeMgr.h"

CBone::CBone()
{
	// empty
}

CBone::~CBone()
{
	Release();
}

HRESULT CBone::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/MapObject/Monster/Effect/Bone/bone%d.png", L"Bone", L"Idle", 7)))
		return S_FALSE;

	m_wstrObjKey = L"Bone";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 270.f;

	// 랜덤한 그림
	m_tFrame = { (float)(rand()%7), 7.f };

	m_fPower = float(rand()%30+80);
	m_fTime = 0.f;

	m_fAngle = D3DXToRadian(rand() % 150 + 30);

	return S_OK;
}

int CBone::Update(void)
{
	Moving();

	if (true == m_bDead)
		return OBJ_DEAD;

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

void CBone::Late_Update(void)
{
	// empty
}

void CBone::Moving()
{
	// 포물선 공식
	//	y = 파워 * 시간 - (중력 * 시간의 제곱) / 2

	float fY = 0.f;

	m_tInfo.vPos.x += m_fSpeed * cosf(m_fAngle) * CTimeMgr::GetInstance()->Get_TimeDelta();
	m_tInfo.vPos.y -= ((m_fPower * m_fTime) - ((9.8f * m_fTime * m_fTime) / 2.f)) * CTimeMgr::GetInstance()->Get_TimeDelta();

	m_fTime += 0.12f;

	if (m_tInfo.vPos.y >= WINCY)
	{
		m_fTime = 0.f;
		m_bDead = true;
	}
}

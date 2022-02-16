#include "stdafx.h"
#include "Shine.h"

#include "ObjMgr.h"
#include "TimeMgr.h"

CShine::CShine()
{
	// empty
}

CShine::~CShine()
{
	Release();
}

HRESULT CShine::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Evil/Effect/Shine/Shine%d.png", L"Shine", L"Idle", 1)))
		return S_FALSE;

	m_wstrObjKey = L"Shine";
	m_wstrStateKey = L"Idle";

	m_tFrame = { 0.f, 1.f, 0.5f };

	m_fRandom = (rand() % 2 + 1.f);

	moving = true;
	m_fSpeed = 120.f;
	m_fDeadCount = 0.f;

	return S_OK;
}

int CShine::Update(void)
{
	Move();

	m_fDeadCount += 5.f * 0.5f * CTimeMgr::GetInstance()->Get_TimeDelta();
	// 5.f * 0.5f == 스피드

	if (m_fDeadCount >= 6.f)
		m_bDead = true;

	if (true == m_bDead)
		return OBJ_DEAD;

	D3DXMATRIX	matTrans, matScale;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	D3DXMatrixScaling(&matScale, m_fRandom * MAPSIZEX, m_fRandom * MAPSIZEY, 1.f);

	m_tInfo.matWorld = matScale * matTrans;

	return OBJ_NOEVENT;
}

void CShine::Late_Update(void)
{
	// empty
}

void CShine::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	if (nullptr == pTexInfo)
		return;

	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	if (true == m_bPink)
	{
		CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
			nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
			nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
			D3DCOLOR_ARGB(140, 252, 139, 151)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지
	}
	else
	{
		CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
			nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
			nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
			D3DCOLOR_ARGB(200, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지
	}
}

void CShine::Move()
{
	if (true == m_bPink)
		PinkMove();
	else
	{
		if (true == moving)
			Moving();
		else
			m_bDead = true;
	}
}

void CShine::PinkMove()
{
	m_fSpeed = 5.f;

	m_tInfo.vDir = m_vFlag - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float		fDot = D3DXVec3Dot(&m_tInfo.vLook, &m_tInfo.vDir);

	m_fAngle = acosf(fDot) - D3DXToRadian(180.f);

	if (m_tInfo.vPos.y < m_vFlag.y)
		m_fAngle = 2.f * D3DX_PI - m_fAngle;

	m_tInfo.vPos.x += m_fSpeed * cosf(m_fAngle) * CTimeMgr::GetInstance()->Get_TimeDelta();
	m_tInfo.vPos.y -= m_fSpeed * sinf(m_fAngle) * CTimeMgr::GetInstance()->Get_TimeDelta();
}

#include "stdafx.h"
#include "Monster.h"
#include "Device.h"
#include "TextureMgr.h"

CMonster::CMonster()
{
	// empty
}

CMonster::~CMonster()
{
	Release();
}

HRESULT CMonster::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/MapObject/Monster/Hit/hit%d.png", L"Monster", L"Hit", 6)))
		return S_FALSE;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/MapObject/Monster/Idle/idle%d.png", L"Monster", L"Idle", 12)))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(80.f, 130.f, 0.f);
	m_wstrObjKey = L"Monster";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f, 1.4f };

	return S_OK;
}

int CMonster::Update(void)
{
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

void CMonster::Late_Update(void)
{
	// Hit Frame
	if (m_Hit)
	{
		// Hit Frame End
		if (m_tFrame.fFrame > 5.f)
		{
			m_Hit = false;
			m_tFrame.fFrame = 0.f;
			m_tFrame = { 0.f, 12.f, 1.4f };
			m_wstrStateKey = L"Idle";
		}
		else
			MoveFrame();
	}
	// Idle Frame
	else 
		MoveFrame();

}

void CMonster::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	if (nullptr == pTexInfo)
		return;

	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
		nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
		nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지
}

void CMonster::Release(void)
{
	// empty
}

void CMonster::Set_Hit()
{
	m_Hit = true;
	m_tFrame = { 0.f, 6.f, 2.f };
	m_wstrStateKey = L"Hit";
}

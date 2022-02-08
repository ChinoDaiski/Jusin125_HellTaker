#include "stdafx.h"
#include "Player.h"
#include "Device.h"
#include "TextureMgr.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	m_tInfo.vPos = D3DXVECTOR3(65.f, 34.f, 0.f);
	m_wstrObjKey = L"Player";
	m_wstrStateKey = L"Dash";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 11.f };

	return S_OK;
}

int CPlayer::Update(void)
{
	D3DXMATRIX	matTrans;
	
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matTrans;
	
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	MoveFrame();
}

void CPlayer::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	if (nullptr == pTexInfo)
		return;

	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	// 행렬을 장치를 이용하여 모든 정점에 곱해주는 함수
	CDevice::GetInstance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
		nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
		nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지
}

void CPlayer::Release(void)
{
	
}

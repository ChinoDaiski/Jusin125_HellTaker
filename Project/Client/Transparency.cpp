#include "stdafx.h"
#include "Transparency.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Device.h"
#include "TextureMgr.h"


CTransparency::CTransparency()
{
}


CTransparency::~CTransparency()
{
}

HRESULT CTransparency::Initialize(void)
{
	m_fTransparency = 255.f;
	m_iRunningTime = 4;
	m_fDeltaTime = 0.f;

	return E_NOTIMPL;
}

int CTransparency::Update(void)
{
	m_fTransparency -= CTimeMgr::GetInstance()->Get_TimeDelta() * (255 / m_iRunningTime);

	if (0 > m_fTransparency)
		CSceneMgr::GetInstance()->Change_SceneMgr(CSceneMgr::ID::STAGE);

	return 0;
}

void CTransparency::Late_Update(void)
{
}

void CTransparency::Render(void)
{
	const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Scene", L"Logo", 1);

	if (nullptr == pTexInfo)
		return;

	float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	D3DXMATRIX		matWorld, matScale, matTrans;
	RECT	rc{};

	// :: 함수 : 글로벌 전역함수 호출구문, 같은 이름의 멤버와 구분하기 위해 사용
	// 현재 클라이언트 영역의 rect 정보를 얻어오는 함수
	::GetClientRect(g_hWnd, &rc);

	// 최소화된 창사이즈의 비율값을 만들어내자.
	//float fX = WINCX / fCenterX * 0.5;
	//float fY = WINCY / fCenterY * 0.5;

	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixScaling(&matScale, 0.4f, 0.4f, 1.f);
	D3DXMatrixTranslation(&matTrans, WINCX >> 1, WINCY >> 1, 0.f);

	matWorld = matScale * matTrans;

	//matWorld._11 *= fX;
	//matWorld._21 *= fX;
	//matWorld._31 *= fX;
	//matWorld._41 *= fX;

	//matWorld._12 *= fY;
	//matWorld._22 *= fY;
	//matWorld._32 *= fY;
	//matWorld._42 *= fY;

	// 행렬을 장치를 이용하여 모든 정점에 곱해주는 함수
	CDevice::GetInstance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
		nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
		nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
		D3DCOLOR_ARGB((int)m_fTransparency, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지
}

void CTransparency::Release(void)
{
}

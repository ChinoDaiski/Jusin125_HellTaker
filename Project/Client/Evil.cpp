#include "stdafx.h"
#include "Evil.h"
#include "Device.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"

#include "LoveSign.h"
#include "LoveBomb.h"
#include "Shine.h"
#include "Heart.h"

CEvil::CEvil()
	: m_pLoveSign(nullptr), m_pLoveBomb(nullptr)
	, m_fDeadCount(0.f), m_White(false)
{
	// empty
}

CEvil::~CEvil()
{
	// empty
}

HRESULT CEvil::Initialize(void)
{
	return S_OK;
}

int CEvil::Update(void)
{
	if (true == m_White)
		m_fDeadCount += 4.f * 0.5f * CTimeMgr::GetInstance()->Get_TimeDelta();
	// 4.f * 0.5f == 스피드

	if (m_fDeadCount >= 6.f)
		m_bDead = true;

	if (true == m_bDead)
	{
		Create_LoveBomb();
		return OBJ_DEAD;
	}

	m_pLoveSign->Set_Pos(m_tInfo.vPos - D3DXVECTOR3{ 30.f, 30.f, 0.f });

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

void CEvil::Late_Update(void)
{
	MoveFrame();
}

void CEvil::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str(), L"Idle", (int)m_tFrame.fFrame);

	if (nullptr == pTexInfo)
		return;

	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	if (true == m_White)
	{
		CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
			nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
			nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
			D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지
	}
	else
	{
		CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
			nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
			nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
			D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지
	}
}

void CEvil::Release(void)
{
	// empty
}

void CEvil::Create_LoveSign()
{
	m_pLoveSign = new CLoveSign;
	m_pLoveSign->Initialize();
	m_pLoveSign->Set_Pos(m_tInfo.vPos - D3DXVECTOR3{ 30.f, 30.f, 0.f });

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, m_pLoveSign);
}

void CEvil::Create_LoveBomb()
{
	m_pLoveBomb = new CLoveBomb;
	m_pLoveBomb->Initialize();
	m_pLoveBomb->Set_Pos(m_tInfo.vPos);

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, m_pLoveBomb);
}

void CEvil::Create_Shine()
{
	CObj* pShine = new CShine;
	pShine->Initialize();
	pShine->Set_Pos(m_tInfo.vPos - D3DXVECTOR3{ 30.f, 0.f, 0.f });

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pShine);
}

void CEvil::Create_Heart()
{
	CObj* pHeart = new CHeart;
	pHeart->Initialize();
	pHeart->Set_Pos(m_tInfo.vPos + D3DXVECTOR3{ 30.f, 0.f, 0.f });

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pHeart);
}

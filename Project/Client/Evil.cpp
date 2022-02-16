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

#include "Player.h"

CEvil::CEvil()
	: m_pLoveSign(nullptr), m_pLoveBomb(nullptr)
	, m_fDeadCount(0.f), m_White(false)
{
	m_pPlayer = CObjMgr::GetInstance()->Get_Player();
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
		ClearMotion();

	if (true == m_bDead)
	{
		// 이펙트 생성
		Create_LoveBomb();

		for (int i = 0; i < 20; ++i)
			Create_Shine(true);

		for (int i = 0; i < 40; ++i)
			Create_Heart();
		
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

void CEvil::ClearMotion()
{
	if (0.f == m_fDeadCount)
	{
		m_pLoveSign->Set_Damage();

		for (int i = 0; i < 30; ++i)
			Create_Shine();
	}

	m_fDeadCount += 4.f * 0.5f * CTimeMgr::GetInstance()->Get_TimeDelta();		// 4.f * 0.5f == 스피드

	if (m_fDeadCount >= 5.4f)
		dynamic_cast<CPlayer*>(m_pPlayer)->Set_Crush(true);

	if (m_fDeadCount >= 6.f)
		m_bDead = true;
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
	D3DXVECTOR3 random;
	float fDistance;
	
	while (true)
	{
		random = m_tInfo.vPos - D3DXVECTOR3{ rand() % 300 - 150.f, rand() % 300 - 150.f, 0.f };

		float	fWidth = m_tInfo.vPos.x - random.x;
		float	fHeight = m_tInfo.vPos.y - random.y;

		// 현재 거리 계산
		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (fDistance >= 70.f && fDistance <= 140.f)
			break;
	}

	CObj* pShine = new CShine;
	pShine->Initialize();
	pShine->Set_Flag(m_tInfo.vPos);
	pShine->Set_Pos(random);

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pShine);
}

void CEvil::Create_Shine(bool _pink)
{
	D3DXVECTOR3 random;
	float fDistance;

	while (true)
	{
		random = m_tInfo.vPos - D3DXVECTOR3{ rand() % 300 - 150.f, rand() % 300 - 150.f, 0.f };

		float	fWidth = m_tInfo.vPos.x - random.x;
		float	fHeight = m_tInfo.vPos.y - random.y;

		// 현재 거리 계산
		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (fDistance >= 70.f && fDistance <= 140.f)
			break;
	}

	CObj* pShine = new CShine;
	pShine->Initialize();
	pShine->Set_Flag(m_tInfo.vPos);
	pShine->Set_Pos(random);
	dynamic_cast<CShine*>(pShine)->Set_Pink(_pink);

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pShine);
}

void CEvil::Create_Heart()
{
	D3DXVECTOR3 random;
	float fDistance;

	while (true)
	{
		random = m_tInfo.vPos - D3DXVECTOR3{ rand() % 300 - 150.f, rand() % 300 - 150.f, 0.f };

		float	fWidth = m_tInfo.vPos.x - random.x;
		float	fHeight = m_tInfo.vPos.y - random.y;

		// 현재 거리 계산
		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (fDistance >= 70.f && fDistance <= 200.f)
			break;
	}

	CObj* pHeart = new CHeart;
	pHeart->Initialize();
	pHeart->Set_Flag(m_tInfo.vPos);
	pHeart->Set_Pos(random);

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pHeart);
}

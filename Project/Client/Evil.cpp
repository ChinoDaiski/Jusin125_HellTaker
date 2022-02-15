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
	// 4.f * 0.5f == ���ǵ�

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
		CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// �ؽ�ó �İ�ü �ּ�
			nullptr,	// ����� �̹��� ������ ���� rect ����ü �ּҰ�, null�� ��� �̹����� 0, 0�� �������� ���
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹��� �߽��࿡ ���� vec3 ����ü �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
			nullptr,	// ����� �̹����� ��ġ�� �����ϴ� vec3 ����ü �ּҰ�, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
			D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����
	}
	else
	{
		CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// �ؽ�ó �İ�ü �ּ�
			nullptr,	// ����� �̹��� ������ ���� rect ����ü �ּҰ�, null�� ��� �̹����� 0, 0�� �������� ���
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹��� �߽��࿡ ���� vec3 ����ü �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
			nullptr,	// ����� �̹����� ��ġ�� �����ϴ� vec3 ����ü �ּҰ�, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
			D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����
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

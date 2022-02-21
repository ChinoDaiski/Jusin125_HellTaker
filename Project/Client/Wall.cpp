#include "stdafx.h"
#include "Wall.h"

#include "Device.h"
#include "TextureMgr.h"
#include "ObjMgr.h"

#include "MoveEffect.h"

CWall::CWall()
	: m_iOption(0), moveCount(0)
	, m_effect(0)
{
	// empty
}

CWall::~CWall()
{
	Release();
}

HRESULT CWall::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/MapObject/Wall/wall%d.png", L"Wall", L"Idle", 12)))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(190.f, 130.f, 0.f);
	m_wstrObjKey = L"Wall";
	m_fSpeed = 800.f;

	// m_tFrame = { 0.f, 12.f };

	return S_OK;
}

int CWall::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	if (true == moving)
	{
		if (0 == m_effect)
		{
			Create_MoveEffect();
			++m_effect;
		}

		Moving();

		if (false == moving)
			m_effect = 0;
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

void CWall::Late_Update(void)
{
	// empty
}

void CWall::Render(void)
{
	// �ɼ� ���� ���� �������� �ٸ��� ��
	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str(), L"Idle", m_iOption);

	if (nullptr == pTexInfo)
		return;

	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// �ؽ�ó �İ�ü �ּ�
		nullptr,	// ����� �̹��� ������ ���� rect ����ü �ּҰ�, null�� ��� �̹����� 0, 0�� �������� ���
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹��� �߽��࿡ ���� vec3 ����ü �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
		nullptr,	// ����� �̹����� ��ġ�� �����ϴ� vec3 ����ü �ּҰ�, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����
}

void CWall::Release(void)
{
	// empty
}

void CWall::Create_MoveEffect()
{
	CObj*	pEffect = new CMoveEffect;
	pEffect->Initialize();

	switch (moveCount)
	{
	case 0:
		pEffect->Set_ObjKey(L"MoveCase0");
		++moveCount;
		break;
	case 1:
		pEffect->Set_ObjKey(L"MoveCase1");
		++moveCount;
		break;
	case 2:
		pEffect->Set_ObjKey(L"MoveCase2");
		moveCount = 0;
		break;
	}

	pEffect->Set_Pos(m_tInfo.vPos);

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pEffect);
}

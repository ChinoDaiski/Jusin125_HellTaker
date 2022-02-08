#include "stdafx.h"
#include "Chest.h"
#include "Device.h"
#include "TextureMgr.h"

CChest::CChest()
{
	// empty
}

CChest::~CChest()
{
	Release();
}

HRESULT CChest::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_SINGLE, L"../Texture/MapObject/Chest/chest0.png", L"Chest")))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(400.f, 130.f, 0.f);
	m_wstrObjKey = L"Chest";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 0.f, 0.f };

	return S_OK;
}

int CChest::Update(void)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matTrans;

	return OBJ_NOEVENT;
}

void CChest::Late_Update(void)
{
	// empty
}

void CChest::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Chest");

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

void CChest::Release(void)
{
	// empty
}

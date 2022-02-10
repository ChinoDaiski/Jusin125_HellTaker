#include "stdafx.h"
#include "Fire.h"
#include "Device.h"
#include "TextureMgr.h"

CFire::CFire()
{
	// empty
}

CFire::~CFire()
{
	Release();
}

HRESULT CFire::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/MapObject/FlameBase/Fire/fire%d.png", L"Fire", L"Idle", 12)))
		return S_FALSE;

	m_wstrObjKey = L"Fire";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	return S_OK;
}

int CFire::Update(void)
{
	D3DXMATRIX	matTrans, matScale;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	D3DXMatrixScaling(&matScale, MAPSIZEX*0.58f, MAPSIZEY*0.58f, 1.f);

	m_tInfo.matWorld = matScale * matTrans;

	return OBJ_NOEVENT;
}

void CFire::Late_Update(void)
{
	MoveFrame();
}

void CFire::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str(), L"Idle", (int)m_tFrame.fFrame);

	if (nullptr == pTexInfo)
		return;

	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// �ؽ�ó �İ�ü �ּ�
		nullptr,	// ����� �̹��� ������ ���� rect ����ü �ּҰ�, null�� ��� �̹����� 0, 0�� �������� ���
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹��� �߽��࿡ ���� vec3 ����ü �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
		nullptr,	// ����� �̹����� ��ġ�� �����ϴ� vec3 ����ü �ּҰ�, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
		D3DCOLOR_ARGB(255, 255, 230, 140)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����
}

void CFire::Release(void)
{
	// empty
}

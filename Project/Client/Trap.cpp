#include "stdafx.h"
#include "Trap.h"
#include "Device.h"
#include "TextureMgr.h"

CTrap::CTrap()
{
	// empty
}

CTrap::~CTrap()
{
	Release();
}

HRESULT CTrap::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/MapObject/Trap/Off/off%d.png", L"Off", L"Idle", 1)))
		return S_FALSE;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/MapObject/Trap/On/on%d.png", L"On", L"Idle", 6)))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(500.f, 130.f, 0.f);
	m_wstrObjKey = L"Off";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 6.f, 2.4f };

	return S_OK;
}

int CTrap::Update(void)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matTrans;

	return OBJ_NOEVENT;
}

void CTrap::Late_Update(void)
{
	if (m_Active)
	{
		m_wstrObjKey = L"On";
		MoveFrame();
	}
}

void CTrap::Render(void)
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
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����
}

void CTrap::Release(void)
{
	// empty
}

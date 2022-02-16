#include "stdafx.h"
#include "Trap.h"
#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

CTrap::CTrap()
	: m_Active(STOP)
{
	// empty
}

CTrap::~CTrap()
{
	Release();
}

HRESULT CTrap::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/MapObject/Trap/trap%d.png", L"Trap", L"Idle", 7)))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(500.f, 130.f, 0.f);
	m_wstrObjKey = L"Trap";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 7.f, 2.4f };

	return S_OK;
}

int CTrap::Update(void)
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

void CTrap::Late_Update(void)
{
	Active_Trap();
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

void CTrap::Active_Trap()
{
	switch (m_Active)
	{
	case ON:
		m_tFrame.fFrame += m_tFrame.fMax * (m_tFrame.fFrameSpeed) * CTimeMgr::GetInstance()->Get_TimeDelta();

		if (m_tFrame.fFrame > m_tFrame.fMax)
		{
			m_Active = STOP;
			m_tFrame.fFrame = m_tFrame.fMax - 1;
		}
		break;
	case OFF:
		m_tFrame.fFrame -= m_tFrame.fMax * (m_tFrame.fFrameSpeed) * CTimeMgr::GetInstance()->Get_TimeDelta();

		if (m_tFrame.fFrame < 1.f)
		{
			m_Active = STOP;
			m_tFrame.fFrame = 0.f;
		}
		break;
	case ON_READY:
		m_tFrame = { 0.f, 7.f, 2.4f };
		m_Active = ON;
		break;
	case OFF_READY:
		m_tFrame = { 6.f, 7.f, 2.4f };
		m_Active = OFF;
		break;
	case ON_KEEP:
		m_tFrame.fFrame = 6.f;
		break;
	}

}
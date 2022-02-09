#include "stdafx.h"
#include "Monster.h"
#include "Device.h"
#include "TextureMgr.h"

CMonster::CMonster()
{
	// empty
}

CMonster::~CMonster()
{
	Release();
}

HRESULT CMonster::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/MapObject/Monster/Hit/hit%d.png", L"Monster", L"Hit", 6)))
		return S_FALSE;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/MapObject/Monster/Idle/idle%d.png", L"Monster", L"Idle", 12)))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(80.f, 130.f, 0.f);
	m_wstrObjKey = L"Monster";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f, 1.4f };

	return S_OK;
}

int CMonster::Update(void)
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

void CMonster::Late_Update(void)
{
	// Hit Frame
	if (m_Hit)
	{
		// Hit Frame End
		if (m_tFrame.fFrame > 5.f)
		{
			m_Hit = false;
			m_tFrame.fFrame = 0.f;
			m_tFrame = { 0.f, 12.f, 1.4f };
			m_wstrStateKey = L"Idle";
		}
		else
			MoveFrame();
	}
	// Idle Frame
	else 
		MoveFrame();

}

void CMonster::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

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

void CMonster::Release(void)
{
	// empty
}

void CMonster::Set_Hit()
{
	m_Hit = true;
	m_tFrame = { 0.f, 6.f, 2.f };
	m_wstrStateKey = L"Hit";
}

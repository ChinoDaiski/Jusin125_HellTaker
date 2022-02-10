#include "stdafx.h"
#include "Grid.h"

#include "Device.h"
#include "TextureMgr.h"

CGrid::CGrid()
	: m_iIndex(0), m_bOnObject(false)
{
	// empty
}

CGrid::~CGrid()
{
	Release();
}

HRESULT CGrid::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_SINGLE, L"../Texture/BackGround/Layer/Layer.png", L"Layer")))
		return S_FALSE;

	m_tInfo.vPos = { 0.f, 0.f, 0.f };
	m_wstrObjKey = L"Layer";
	m_fSpeed = 100.f;

	m_GridState = CAN_MOVE;

	return S_OK;
}

int CGrid::Update(void)
{
	D3DXMATRIX	matTrans, matScale;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	float fX = MAPSIZEX * ((1920.f / 19.f) / 100.f);
	float fY = MAPSIZEY * ((1080.f / 11.f) / 100.f);
	D3DXMatrixScaling(&matScale, fX, fY, 1.f);

	m_tInfo.matWorld = matScale * matTrans;

	return OBJ_NOEVENT;
}

void CGrid::Late_Update(void)
{
	// empty
}

void CGrid::Render(void)
{
	TCHAR	szBuf[MIN_STR]{};

	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str());

	if (nullptr == pTexInfo)
		return;

	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// �ؽ�ó �İ�ü �ּ�
		nullptr,	// ����� �̹��� ������ ���� rect ����ü �ּҰ�, null�� ��� �̹����� 0, 0�� �������� ���
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹��� �߽��࿡ ���� vec3 ����ü �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
		nullptr,	// ����� �̹����� ��ġ�� �����ϴ� vec3 ����ü �ּҰ�, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
		D3DCOLOR_ARGB(150, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����

	// Ÿ�� �ε��� ���
	swprintf_s(szBuf, L"%d", m_iIndex);
	// SETTRANSFORM�� ������ ����
	CDevice::GetInstance()->Get_Font()->DrawTextW(CDevice::GetInstance()->Get_Sprite(),
		szBuf,
		lstrlen(szBuf),
		NULL,
		0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CGrid::Release(void)
{
	// empty
}

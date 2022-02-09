#include "stdafx.h"
#include "Transparency.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Device.h"
#include "TextureMgr.h"


CTransparency::CTransparency()
{
}


CTransparency::~CTransparency()
{
}

HRESULT CTransparency::Initialize(void)
{
	m_fTransparency = 255.f;
	m_iRunningTime = 4;
	m_fDeltaTime = 0.f;

	return E_NOTIMPL;
}

int CTransparency::Update(void)
{
	m_fTransparency -= CTimeMgr::GetInstance()->Get_TimeDelta() * (255 / m_iRunningTime);

	if (0 > m_fTransparency)
		CSceneMgr::GetInstance()->Change_SceneMgr(CSceneMgr::ID::STAGE);

	return 0;
}

void CTransparency::Late_Update(void)
{
}

void CTransparency::Render(void)
{
	const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Scene", L"Logo", 1);

	if (nullptr == pTexInfo)
		return;

	float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	D3DXMATRIX		matWorld, matScale, matTrans;
	RECT	rc{};

	// :: �Լ� : �۷ι� �����Լ� ȣ�ⱸ��, ���� �̸��� ����� �����ϱ� ���� ���
	// ���� Ŭ���̾�Ʈ ������ rect ������ ������ �Լ�
	::GetClientRect(g_hWnd, &rc);

	// �ּ�ȭ�� â�������� �������� ������.
	//float fX = WINCX / fCenterX * 0.5;
	//float fY = WINCY / fCenterY * 0.5;

	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixScaling(&matScale, 0.4f, 0.4f, 1.f);
	D3DXMatrixTranslation(&matTrans, WINCX >> 1, WINCY >> 1, 0.f);

	matWorld = matScale * matTrans;

	//matWorld._11 *= fX;
	//matWorld._21 *= fX;
	//matWorld._31 *= fX;
	//matWorld._41 *= fX;

	//matWorld._12 *= fY;
	//matWorld._22 *= fY;
	//matWorld._32 *= fY;
	//matWorld._42 *= fY;

	// ����� ��ġ�� �̿��Ͽ� ��� ������ �����ִ� �Լ�
	CDevice::GetInstance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// �ؽ�ó �İ�ü �ּ�
		nullptr,	// ����� �̹��� ������ ���� rect ����ü �ּҰ�, null�� ��� �̹����� 0, 0�� �������� ���
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹��� �߽��࿡ ���� vec3 ����ü �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
		nullptr,	// ����� �̹����� ��ġ�� �����ϴ� vec3 ����ü �ּҰ�, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
		D3DCOLOR_ARGB((int)m_fTransparency, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����
}

void CTransparency::Release(void)
{
}

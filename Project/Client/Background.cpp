#include "stdafx.h"
#include "Background.h"
#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

CBackground::CBackground()
{
}


CBackground::~CBackground()
{
}

HRESULT CBackground::Initialize(void)
{
	m_fEnlarge = 1.f;

	switch (m_eID)
	{
	case CSceneMgr::LOGO:
		m_tFrame.fMax = 0;
		m_tFrame.fFrame = 0;
		break;
	case CSceneMgr::STAGE:
		m_tFrame.fMax = 14;
		m_tFrame.fFrame = 0;
		break;
	case CSceneMgr::BOSS:
		break;
	case CSceneMgr::LOADING:
		break;
	case CSceneMgr::END:
		break;
	default:
		break;
	}

	return E_NOTIMPL;
}

int CBackground::Update(void)
{
	if (CSceneMgr::LOGO == m_eID)
		m_fEnlarge += (CTimeMgr::GetInstance()->Get_TimeDelta() * 0.01);

	MoveFrame();

	return 0;
}

void CBackground::Late_Update(void)
{
}

void CBackground::Render(void)
{
	const TEXINFO*		pTexInfo = nullptr;
	
	switch (m_eID)
	{
	case CSceneMgr::LOGO:
		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Scene", L"Logo", m_tFrame.fFrame);
		break;
	case CSceneMgr::STAGE:
		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Scene", L"Background", m_tFrame.fFrame);
		break;
	case CSceneMgr::BOSS:
		break;
	case CSceneMgr::LOADING:
		break;
	case CSceneMgr::END:
		break;
	default:
		break;
	}

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
	float fX = WINCX / fCenterX * 0.5;
	float fY = WINCY / fCenterY * 0.5;

	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixScaling(&matScale, m_fEnlarge, m_fEnlarge, 1.f);
	D3DXMatrixTranslation(&matTrans, fCenterX, fCenterY, 0.f);

	matWorld = matScale * matTrans;

	matWorld._11 *= fX;
	matWorld._21 *= fX;
	matWorld._31 *= fX;
	matWorld._41 *= fX;

	matWorld._12 *= fY;
	matWorld._22 *= fY;
	matWorld._32 *= fY;
	matWorld._42 *= fY;

	// ����� ��ġ�� �̿��Ͽ� ��� ������ �����ִ� �Լ�
	CDevice::GetInstance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// �ؽ�ó �İ�ü �ּ�
		nullptr,	// ����� �̹��� ������ ���� rect ����ü �ּҰ�, null�� ��� �̹����� 0, 0�� �������� ���
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹��� �߽��࿡ ���� vec3 ����ü �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
		nullptr,	// ����� �̹����� ��ġ�� �����ϴ� vec3 ����ü �ּҰ�, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����
}

void CBackground::Release(void)
{
}

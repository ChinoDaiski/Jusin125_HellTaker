#include "stdafx.h"
#include "Character.h"
#include "TextureMgr.h"
#include "Device.h"


CCharacter::CCharacter()
{
}


CCharacter::~CCharacter()
{
}

HRESULT CCharacter::Initialize(void)
{

	return E_NOTIMPL;
}

int CCharacter::Update(void)
{
	return 0;
}

void CCharacter::Late_Update(void)
{
}

void CCharacter::Render(void)
{
	const TEXINFO*	pTexInfo = nullptr; 

	switch (m_eID)
	{
	case CCharacter::Baal:
		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Stage", L"Character", 0);
		break;

	case CCharacter::End:
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
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����
}

void CCharacter::Release(void)
{
}

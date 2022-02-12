#include "stdafx.h"
#include "Azazel.h"
#include "Device.h"
#include "TextureMgr.h"

CAzazel::CAzazel()
{
	// empty
}

CAzazel::~CAzazel()
{
	Release();
}

HRESULT CAzazel::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Azazel/azazel%d.png", L"Azazel", L"Idle", 12)))
		return S_FALSE;

	m_wstrObjKey = L"Azazel";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	Create_LoveSign();

	return S_OK;
}

int CAzazel::Update(void)
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

void CAzazel::Late_Update(void)
{
	MoveFrame();
}

void CAzazel::Render(void)
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

void CAzazel::Release(void)
{
	// empty
}

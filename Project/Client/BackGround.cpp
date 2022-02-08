#include "stdafx.h"
#include "BackGround.h"

#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

CBackGround::CBackGround()
{
	// empty
}

CBackGround::~CBackGround()
{
	Release();
}

HRESULT CBackGround::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/BackGround/chapter%d.png", L"BackGround", L"Idle", 8)))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(WINCX>>1, WINCY>>1, 0.f);
	m_wstrObjKey = L"BackGround";
	m_fSpeed = 100.f;

	// m_tFrame = { 6.f, 8.f };
	m_tFrame = { 7.f, 8.f };


	return S_OK;
}

int CBackGround::Update(void)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matTrans;

	D3DXVECTOR3	vMouse = ::Get_Mouse();

	if (10.f > vMouse.x)
		m_vScroll.x += 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (WINCX - 10 < vMouse.x)
		m_vScroll.x -= 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (10.f > vMouse.y)
		m_vScroll.y += 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (WINCY - 10 - (920/4) < vMouse.y)
		m_vScroll.y -= 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();


	return OBJ_NOEVENT;
}

void CBackGround::Late_Update(void)
{
	// empty
}

void CBackGround::Render(void)
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

void CBackGround::Release(void)
{
	// empty
}

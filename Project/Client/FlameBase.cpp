#include "stdafx.h"
#include "FlameBase.h"
#include "Device.h"
#include "TextureMgr.h"
#include "ObjMgr.h"

#include "Fire.h"

CFlameBase::CFlameBase()
{
	// empty
}

CFlameBase::~CFlameBase()
{
	Release();
}

HRESULT CFlameBase::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/MapObject/FlameBase/flamebase%d.png", L"FlameBase", L"Idle", 2)))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(760.f, 540.f, 0.f);
	m_wstrObjKey = L"FlameBase";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 2.f };

	Create_Fire();

	return S_OK;
}

int CFlameBase::Update(void)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matTrans;

	return OBJ_NOEVENT;
}

void CFlameBase::Late_Update(void)
{
	// empty
}

void CFlameBase::Render(void)
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

void CFlameBase::Release(void)
{
	// empty
}

void CFlameBase::Create_Fire(void)
{
	CObj*		pObj = new CFire;

	if (nullptr != pObj)
		pObj->Initialize();

	pObj->Set_Pos(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - 27, 0.f));
	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pObj);
}

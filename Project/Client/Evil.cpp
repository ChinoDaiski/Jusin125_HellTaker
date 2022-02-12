#include "stdafx.h"
#include "Evil.h"
#include "Device.h"
#include "TextureMgr.h"
#include "ObjMgr.h"

#include "LoveSign.h"

CEvil::CEvil()
	: m_pLoveSign(nullptr)
{
	// empty
}

CEvil::~CEvil()
{
	// empty
}

HRESULT CEvil::Initialize(void)
{
	return S_OK;
}

int CEvil::Update(void)
{
	m_pLoveSign->Set_Pos(m_tInfo.vPos - D3DXVECTOR3{ 30.f, 30.f, 0.f });

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

void CEvil::Late_Update(void)
{
	MoveFrame();
}

void CEvil::Render(void)
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

void CEvil::Release(void)
{
	// empty
}

void CEvil::Create_LoveSign()
{
	m_pLoveSign = new CLoveSign;
	m_pLoveSign->Initialize();
	m_pLoveSign->Set_Pos(m_tInfo.vPos - D3DXVECTOR3{ 30.f, 30.f, 0.f });

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, m_pLoveSign);
}

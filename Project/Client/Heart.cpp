#include "stdafx.h"
#include "Heart.h"

#include "ObjMgr.h"
#include "TimeMgr.h"

CHeart::CHeart()
{
	// empty
}

CHeart::~CHeart()
{
	// empty
}

HRESULT CHeart::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Evil/Effect/Heart/Heart%d.png", L"Heart", L"Idle", 1)))
		return S_FALSE;

	m_wstrObjKey = L"Heart";
	m_wstrStateKey = L"Idle";

	m_tFrame = { 0.f, 1.f, 1.3f };

	m_fRandom = (rand() % 3 + 1.f);

	moving = true;
	m_fSpeed = 5.f;
	m_fDeadCount = 0.f;

	return S_OK;
}

int CHeart::Update(void)
{
	Moving();

	m_fDeadCount += 5.f * 0.5f * CTimeMgr::GetInstance()->Get_TimeDelta();
	// 5.f * 0.5f == ���ǵ�

	if (m_fDeadCount >= 6.f)
		m_bDead = true;

	if (true == m_bDead)
		return OBJ_DEAD;

	D3DXMATRIX	matTrans, matScale;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	D3DXMatrixScaling(&matScale, m_fRandom * MAPSIZEX, m_fRandom * MAPSIZEY, 1.f);
	m_tInfo.matWorld = matScale * matTrans;

	return OBJ_NOEVENT;
}

void CHeart::Late_Update(void)
{
	// empty
}

void CHeart::Render(void)
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
		D3DCOLOR_ARGB(120, 232, 0, 69)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����
}

void CHeart::Moving()
{
	m_tInfo.vDir = m_vFlag - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float		fDot = D3DXVec3Dot(&m_tInfo.vLook, &m_tInfo.vDir);

	m_fAngle = acosf(fDot) - D3DXToRadian(180.f);

	if (m_tInfo.vPos.y < m_vFlag.y)
		m_fAngle = 2.f * D3DX_PI - m_fAngle;

	m_tInfo.vPos.x += m_fSpeed * cosf(m_fAngle) * CTimeMgr::GetInstance()->Get_TimeDelta();
	m_tInfo.vPos.y -= m_fSpeed * sinf(m_fAngle) * CTimeMgr::GetInstance()->Get_TimeDelta();
}

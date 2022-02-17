#include "stdafx.h"
#include "Cerberus.h"
#include "Device.h"
#include "TextureMgr.h"

CCerberus::CCerberus()
{
	CObj::m_iChapterNum = 2;
}

CCerberus::~CCerberus()
{
	Release();
}

HRESULT CCerberus::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Cerberus/cerberus%d.png", L"Cerberus", L"Idle", 12)))
		return S_FALSE;

	m_wstrObjKey = L"Cerberus";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	Create_LoveSign();

	return S_OK;
}

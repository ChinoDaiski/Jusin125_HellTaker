#include "stdafx.h"
#include "Zdrada.h"
#include "Device.h"
#include "TextureMgr.h"

CZdrada::CZdrada()
{
	CObj::m_iChapterNum = 4;
}

CZdrada::~CZdrada()
{
	Release();
}

HRESULT CZdrada::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Zdrada/zdrada%d.png", L"Zdrada", L"Idle", 12)))
		return S_FALSE;

	m_wstrObjKey = L"Zdrada";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	Create_LoveSign();

	return S_OK;
}
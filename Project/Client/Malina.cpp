#include "stdafx.h"
#include "Malina.h"
#include "Device.h"
#include "TextureMgr.h"

CMalina::CMalina()
{
	CObj::m_iChapterNum = 3;
}

CMalina::~CMalina()
{
	Release();
}

HRESULT CMalina::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Malina/malina%d.png", L"Malina", L"Idle", 12)))
		return S_FALSE;

	m_wstrObjKey = L"Malina";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	Create_LoveSign();

	return S_OK;
}
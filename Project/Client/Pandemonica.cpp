#include "stdafx.h"
#include "Pandemonica.h"
#include "Device.h"
#include "TextureMgr.h"

CPandemonica::CPandemonica()
{
	CObj::m_iChapterNum = 0;
}

CPandemonica::~CPandemonica()
{
	Release();
}

HRESULT CPandemonica::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Pandemonica/pandemonica%d.png", L"Pandemonica", L"Idle", 12)))
		return S_FALSE;

	m_wstrObjKey = L"Pandemonica";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	Create_LoveSign();

	return S_OK;
}
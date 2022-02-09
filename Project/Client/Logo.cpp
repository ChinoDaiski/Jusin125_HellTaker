#include "stdafx.h"
#include "Logo.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Background.h"
#include "Transparency.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
}

HRESULT CLogo::Ready_Scene()
{
	/*if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
	{
		MSG_BOX(L"Texture txt Load Failed");
		return E_FAIL;
	}*/

	// 로고 배경 
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEXTUREID::TEX_MULTI, L"../Texture/Stage/Scene/Logo/Logo%d.png", L"Scene", L"Logo", 2))) {
		MSG_BOX(L"Texture Logo Load Failed");
		return E_FAIL;
	}

	CObj* pBackground = new CBackground;
	pBackground->Initialize();
	dynamic_cast<CBackground*>(pBackground)->Set_SceneID(CSceneMgr::ID::LOGO);
	CObjMgr::GetInstance()->Add_Object(CObjMgr::ID::BACK, pBackground);

	CObj* pTransparency = new CTransparency;
	pTransparency->Initialize();
	//dynamic_cast<CTransparency*>(pTransparency)->Set_SceneID(CSceneMgr::ID::LOGO);
	CObjMgr::GetInstance()->Add_Object(CObjMgr::ID::BACK, pTransparency);

	return S_OK;
}

void CLogo::Update_Scene()
{
	CObjMgr::GetInstance()->Update();
}

void CLogo::Late_Update_Scene()
{
	CObjMgr::GetInstance()->Late_Update();
}

void CLogo::Render_Scene()
{
	CObjMgr::GetInstance()->Render();
}

void CLogo::Release_Scene()
{
	CObjMgr::GetInstance()->Release();
}

CLogo* CLogo::Create(void)
{
	CLogo*		pInstance = new CLogo;

	if (FAILED(pInstance->Ready_Scene()))
		return nullptr;

	return pInstance;
}

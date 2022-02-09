#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "MyTerrain.h"
#include "Player.h"
#include "Background.h"

CStage::CStage()
{
}


CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	/*if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Stage/Terrain/Tile/Tile%d.png",
		L"Terrain",
		L"Tile",
		36)))
	{
		MSG_BOX(L"Tile Texture Insert Failed");
		return E_FAIL;
	}*/

	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/JSU_ImgPath.txt")))
	{
		MSG_BOX(L"Texture txt Load Failed");
		return E_FAIL;
	}

	CObj* pObj = new CBackground;
	dynamic_cast<CBackground*>(pObj)->Set_SceneID(CSceneMgr::ID::STAGE);

	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::ID::BACK, pObj);
	
	return S_OK;
}

void CStage::Update_Scene()
{
	CObjMgr::GetInstance()->Update();
}

void CStage::Late_Update_Scene()
{
	CObjMgr::GetInstance()->Late_Update();
}

void CStage::Render_Scene()
{
	CObjMgr::GetInstance()->Render();
}

void CStage::Release_Scene()
{
	
}

CStage* CStage::Create(void)
{
	CStage*		pInstance = new CStage;

	if (FAILED(pInstance->Ready_Scene()))
		return nullptr;

	return pInstance;
}

#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "MyTerrain.h"

#include "Player.h"
#include "Azazel.h"
#include "Cerberus.h"
#include "Justice.h"
#include "Lucifer.h"
#include "Malina.h"
#include "Modeus.h"
#include "Pandemonica.h"
#include "Zdrada.h"

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

	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
	{
		MSG_BOX(L"Texture txt Load Failed");
		return E_FAIL;
	}


	CObj*		pObj = new CMyTerrain;

	if(nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TERRAIN, pObj);

	pObj = new CPlayer;

	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::PLAYER, pObj);

	// ������. Azazel
	pObj = new CAzazel;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// �ɸ����ν�. Cerberus
	pObj = new CCerberus;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
	
	// ����Ƽ��. Justice
	pObj = new CJustice;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// �����. Lucifer
	pObj = new CLucifer;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// ������. Malina
	pObj = new CMalina;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// �𵥿콺. Modeus
	pObj = new CModeus;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// �ǵ����ī. Pandemonica
	pObj = new CPandemonica;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// �����. Zdrada
	pObj = new CZdrada;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

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

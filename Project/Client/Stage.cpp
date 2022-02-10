#include "stdafx.h"
#include "Stage.h"

#include "TextureMgr.h"
#include "ObjMgr.h"
#include "MyTerrain.h"
#include "BackGround.h"

#include "Player.h"

// Evil
#include "Azazel.h"
#include "Cerberus.h"
#include "Justice.h"
#include "Lucifer.h"
#include "Malina.h"
#include "Modeus.h"
#include "Pandemonica.h"
#include "Zdrada.h"
#include "Judgement.h"

// MapObj
#include "Monster.h"
#include "Wall.h"
#include "Key.h"
#include "Chest.h"
#include "Trap.h"
#include "FlameBase.h"

CStage::CStage()
{
	// empty
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	CObj*		pObj = new CBackGround;

	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TERRAIN, pObj);

	pObj = new CPlayer;

	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::PLAYER, pObj);

	// 아자젤. Azazel
	pObj = new CAzazel;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// 케르베로스. Cerberus
	pObj = new CCerberus;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
	
	// 저스티스. Justice
	pObj = new CJustice;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// 루시퍼. Lucifer
	pObj = new CLucifer;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// 말리나. Malina
	pObj = new CMalina;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// 모데우스. Modeus
	pObj = new CModeus;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// 판데모니카. Pandemonica
	pObj = new CPandemonica;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// 즈드라다. Zdrada
	pObj = new CZdrada;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// 저지먼트. Judgement
	pObj = new CJudgement;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// 몬스터. Monster
	pObj = new CMonster;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::MONSTER, pObj);

	// 벽. Wall
	pObj = new CWall;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

	// 키. Key
	pObj = new CKey;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVENT_OBJ, pObj);

	// 상자. Chest
	pObj = new CChest;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVENT_OBJ, pObj);

	// 트랩. Trap
	pObj = new CTrap;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TRAP, pObj);

	// 플레임베이스. FlameBase
	pObj = new CFlameBase;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

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
	// empty
}

CStage* CStage::Create(void)
{
	CStage*		pInstance = new CStage;

	if (FAILED(pInstance->Ready_Scene()))
		return nullptr;

	return pInstance;
}
#include "stdafx.h"
#include "Stage.h"

#include "TextureMgr.h"
#include "ObjMgr.h"
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
	: m_chapter(ZERO)
{
	CObj* pBackGround = new CBackGround;

	if (nullptr != pBackGround)
		pBackGround->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TERRAIN, pBackGround);

	m_pBackGround = CObjMgr::GetInstance()->Get_Terrain();

	// 플레이어 생성
	CObj*		pPlayer = new CPlayer;

	if (nullptr != pPlayer)
		pPlayer->Initialize();
	CObjMgr::GetInstance()->Add_Object(CObjMgr::PLAYER, pPlayer);

	m_pPlayer = CObjMgr::GetInstance()->Get_Player();
	dynamic_cast<CPlayer*>(m_pPlayer)->Set_GroundPtr(m_pBackGround);
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	// 챕터 초기화
	Init_Chapter();
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

void CStage::Change_NextChapter()
{
	CObjMgr::GetInstance()->Delete_ID(CObjMgr::MONSTER);
	CObjMgr::GetInstance()->Delete_ID(CObjMgr::EVIL);
	
	switch (m_chapter)
	{
	case ZERO:
		m_chapter = ONE;
		break;
	case ONE:
		m_chapter = TWO;
		break;
	case TWO:
		m_chapter = THREE;
		break;
	case THREE:
		m_chapter = FOUR;
		break;
	case FOUR:
		m_chapter = FIVE;
		break;
	case FIVE:
		m_chapter = SIX;
		break;
	case SIX:
		m_chapter = SEVEN;
		break;
	case SEVEN:
		m_chapter = EIGHT;
		break;
	case EIGHT:
		m_chapter = EIGHT;
		break;
	case CHAPTER_END:
		// TODO : 엔딩 씬(Ending Scene)?
		break;
	}
}

void CStage::Init_Chapter()
{
	m_pBackGround->Release();
	dynamic_cast<CPlayer*>(m_pPlayer)->Set_GroundPtr(m_pBackGround);
	dynamic_cast<CBackGround*>(m_pBackGround)->Select_Chapter(m_chapter);

	switch (m_chapter)
	{
	case ZERO:
		Init_ChapterZERO();
		break;
	case ONE:
		Init_ChapterONE();
		break;
	case TWO:
		Init_ChapterTWO();
		break;
	case THREE:
		Init_ChapterTHREE();
		break;
	case FOUR:
		Init_ChapterFOUR();
		break;
	case FIVE:
		Init_ChapterFIVE();
		break;
	case SIX:
		Init_ChapterSIX();
		break;
	case SEVEN:
		Init_ChapterSeven();
		break;
	case EIGHT:
		// TODO : BOSS_ROOM
		Init_ChapterEIGHT();
		break;
	case CHAPTER_END:
		// TODO : 엔딩 씬(Ending Scene)?
		break;
	}
}

void CStage::Init_ChapterZERO()
{
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));
	m_pPlayer->Set_ObjIndex(15);

	// 판데모니카. Pandemonica
	CObj* pObj = new CPandemonica;
	if (nullptr != pObj)
	{
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(61));
		pObj->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(61, ON_OBJECT);
		pObj->Set_ObjIndex(61);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// 몬스터. Monster
	pObj = new CMonster;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(22));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(22, ON_OBJECT);
		pObj->Set_ObjIndex(22);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::MONSTER, pObj);

	// 몬스터. Monster
	pObj = new CMonster;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(30));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(30, ON_OBJECT);
		pObj->Set_ObjIndex(30);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::MONSTER, pObj);

	// 몬스터. Monster
	pObj = new CMonster;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(32));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(32, ON_OBJECT);
		pObj->Set_ObjIndex(32);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::MONSTER, pObj);

	// 플레임베이스
	pObj = new CFlameBase;
	if (nullptr != pObj)
	{
		D3DXVECTOR3 tmp = dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(36);
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(36, CANT_MOVE);
		pObj->Set_ObjIndex(36);

		pObj->Initialize();
		pObj->Set_Pos(tmp);
		tmp -= D3DXVECTOR3{ 0.f, 20.f, 0.f };
		dynamic_cast<CFlameBase*>(pObj)->Get_Frie()->Set_Pos(tmp);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

	// 플레임베이스
	pObj = new CFlameBase;
	if (nullptr != pObj)
	{
		D3DXVECTOR3 tmp = dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(10);
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(10, CANT_MOVE);
		pObj->Set_ObjIndex(10);

		pObj->Initialize();
		pObj->Set_Pos(tmp);
		tmp -= D3DXVECTOR3{ 0.f, 20.f, 0.f };
		dynamic_cast<CFlameBase*>(pObj)->Get_Frie()->Set_Pos(tmp);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

	// 플레임베이스
	pObj = new CFlameBase;
	if (nullptr != pObj)
	{
		D3DXVECTOR3 tmp = dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(4);
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(4, CANT_MOVE);
		pObj->Set_ObjIndex(4);

		pObj->Initialize();
		pObj->Set_Pos(tmp);
		tmp -= D3DXVECTOR3{ 0.f, 20.f, 0.f };
		dynamic_cast<CFlameBase*>(pObj)->Get_Frie()->Set_Pos(tmp);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

	// 플레임베이스
	pObj = new CFlameBase;
	if (nullptr != pObj)
	{
		D3DXVECTOR3 tmp = dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(43);
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(43, CANT_MOVE);
		pObj->Set_ObjIndex(43);

		pObj->Initialize();
		pObj->Set_Pos(tmp);
		tmp -= D3DXVECTOR3{ 0.f, 20.f, 0.f };
		dynamic_cast<CFlameBase*>(pObj)->Get_Frie()->Set_Pos(tmp);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);
}

void CStage::Init_ChapterONE()
{
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(55));
	m_pPlayer->Set_ObjIndex(55);

	// 모데우스. Modeus
	CObj* pObj = new CModeus;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(68));
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterTWO()
{
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));
	m_pPlayer->Set_ObjIndex(15);

	// 케르베로스. Cerberus
	CObj* pObj = new CCerberus;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(68));
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterTHREE()
{
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));
	m_pPlayer->Set_ObjIndex(15);

	// 말리나. Malina
	CObj* pObj = new CMalina;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterFOUR()
{
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));
	m_pPlayer->Set_ObjIndex(15);

	// 즈드라다. Zdrada
	CObj* pObj = new CZdrada;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterFIVE()
{
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));
	m_pPlayer->Set_ObjIndex(15);

	// 아자젤. Azazel
	CObj* pObj = new CAzazel;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterSIX()
{
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));
	m_pPlayer->Set_ObjIndex(15);

	// 저스티스. Justice
	CObj* pObj = new CJustice;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterSeven()
{
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));
	m_pPlayer->Set_ObjIndex(15);

	// 루시퍼. Lucifer
	CObj* pObj = new CLucifer;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterEIGHT()
{
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));
	m_pPlayer->Set_ObjIndex(15);

	// 저지먼트. Judgement
	CObj* pObj = new CJudgement;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

// 기타 오브젝트 임시 보관용
/*
CObj* pObj = nullptr;

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

*/
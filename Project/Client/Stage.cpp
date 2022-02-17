#include "stdafx.h"
#include "Stage.h"

#include "TextureMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "BackGround.h"

#include "Player.h"
#include "DeathEffect.h"

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
	: m_chapter(ZERO), m_pDeath(nullptr)
	, m_fTimer(0.f)
{
	// 백그라운드 생성
	CObj* pBackGround = new CBackGround;

	if (nullptr != pBackGround)
		pBackGround->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TERRAIN, pBackGround);

	m_pBackGround = CObjMgr::GetInstance()->Get_Terrain();

	// 플레이어 생성
	m_pPlayer = new CPlayer;

	if (nullptr != m_pPlayer)
		m_pPlayer->Initialize();
	CObjMgr::GetInstance()->Add_Object(CObjMgr::PLAYER, m_pPlayer);

	dynamic_cast<CPlayer*>(m_pPlayer)->Set_GroundPtr(m_pBackGround);

	// 챕터 Hp 초기화
	Init_ChapterHp();
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
	// 골 인덱스인지 확인
	if (g_iGoalIndex == m_pPlayer->Get_ObjIndex())
		Goal_Arrive();
	else
		Player_Death();

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
	CObjMgr::GetInstance()->Delete_ID(CObjMgr::WALL);
	CObjMgr::GetInstance()->Delete_ID(CObjMgr::EFFECT);
	CObjMgr::GetInstance()->Delete_ID(CObjMgr::EVENT_OBJ);
	CObjMgr::GetInstance()->Delete_ID(CObjMgr::TRAP);

	dynamic_cast<CPlayer*>(m_pPlayer)->Set_StateKey(L"Idle");
	m_pPlayer->Set_fFrame(FRAME(0.f, 12.f));

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

void CStage::Init_ChapterHp()
{
	m_ChapterHp[0] = 10;
	m_ChapterHp[1] = 10;
	m_ChapterHp[2] = 10;
	m_ChapterHp[3] = 10;
	m_ChapterHp[4] = 10;
	m_ChapterHp[5] = 10;
	m_ChapterHp[6] = 10;
	m_ChapterHp[7] = 10;
	m_ChapterHp[8] = 10;
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
	// 골 인덱스 60
	g_iGoalIndex = 60;

	m_pPlayer->Set_Hp(m_ChapterHp[0]);
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));
	m_pPlayer->Set_ObjIndex(15);
	m_pPlayer->Set_Flag(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));

	// 판데모니카. Pandemonica
	CObj* pEvil = new CPandemonica;
	if (nullptr != pEvil)
	{
		pEvil->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(61));
		pEvil->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(61, ON_OBJECT);
		pEvil->Set_ObjIndex(61);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pEvil);

	// 몬스터. Monster
	CObj* pObj = new CMonster;
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

	// Wall
	pObj = new CWall;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(47));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(47, ON_OBJECT);
		pObj->Set_ObjIndex(47);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

	// Wall
	pObj = new CWall;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(50));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(50, ON_OBJECT);
		pObj->Set_ObjIndex(50);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

	// Wall
	pObj = new CWall;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(56));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(56, ON_OBJECT);
		pObj->Set_ObjIndex(56);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

	// Wall
	pObj = new CWall;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(58));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(58, ON_OBJECT);
		pObj->Set_ObjIndex(58);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

}

void CStage::Init_ChapterONE()
{
	// 골 인덱스 59
	g_iGoalIndex = 59;

	m_pPlayer->Set_Hp(m_ChapterHp[1]);
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(55));
	m_pPlayer->Set_ObjIndex(55);
	m_pPlayer->Set_Flag(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(55));

	// 모데우스. Modeus
	CObj* pEvil = new CModeus;
	if (nullptr != pEvil)
	{
		pEvil->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(68));
		pEvil->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(68, ON_OBJECT);
		pEvil->Set_ObjIndex(68);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pEvil);

	// 몬스터. Monster
	CObj* pObj = new CMonster;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(29));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(29, ON_OBJECT);
		pObj->Set_ObjIndex(29);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::MONSTER, pObj);

	// 몬스터. Monster
	pObj = new CMonster;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(60));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(60, ON_OBJECT);
		pObj->Set_ObjIndex(60);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::MONSTER, pObj);

	// 몬스터. Monster
	pObj = new CMonster;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(70));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(70, ON_OBJECT);
		pObj->Set_ObjIndex(70);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::MONSTER, pObj);

	

	// Wall
	pObj = new CWall;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(41));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(41, ON_OBJECT);
		pObj->Set_ObjIndex(41);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

	// Wall
	pObj = new CWall;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(42));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(42, ON_OBJECT);
		pObj->Set_ObjIndex(42);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

	// Wall
	pObj = new CWall;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(43));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(43, ON_OBJECT);
		pObj->Set_ObjIndex(43);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);
	// Trap
	pObj = new CTrap;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(31));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(31, ON_TRAP);
		pObj->Set_ObjIndex(31);
		dynamic_cast<CTrap*>(pObj)->Set_Active(CTrap::ON_KEEP);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TRAP, pObj);

	// Trap
	pObj = new CTrap;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(32));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(32, ON_TRAP);
		pObj->Set_ObjIndex(32);
		dynamic_cast<CTrap*>(pObj)->Set_Active(CTrap::ON_KEEP);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TRAP, pObj);

	// Trap
	pObj = new CTrap;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(38));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(38, ON_TRAP);
		pObj->Set_ObjIndex(38);
		dynamic_cast<CTrap*>(pObj)->Set_Active(CTrap::ON_KEEP);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TRAP, pObj);

	// Trap
	pObj = new CTrap;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(41));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(41, ON_TRAP);
		pObj->Set_ObjIndex(41);
		dynamic_cast<CTrap*>(pObj)->Set_Active(CTrap::ON_KEEP);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TRAP, pObj);

	// Trap
	pObj = new CTrap;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(42));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(42, ON_TRAP);
		pObj->Set_ObjIndex(42);
		dynamic_cast<CTrap*>(pObj)->Set_Active(CTrap::ON_KEEP);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TRAP, pObj);

	// Trap
	pObj = new CTrap;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(51));
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(51, ON_TRAP);
		pObj->Set_ObjIndex(51);
		dynamic_cast<CTrap*>(pObj)->Set_Active(CTrap::ON_KEEP);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TRAP, pObj);
}

void CStage::Init_ChapterTWO()
{
	// 골 인덱스 17
	g_iGoalIndex = 17;

	m_pPlayer->Set_Hp(m_ChapterHp[2]);
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(38));
	m_pPlayer->Set_ObjIndex(38);
	m_pPlayer->Set_Flag(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(38));

	// 케르베로스 1. Cerberus
	CObj* pEvil = new CCerberus;
	if (nullptr != pEvil)
	{
		pEvil->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(14));
		pEvil->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(14, ON_OBJECT);
		pEvil->Set_ObjIndex(14);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pEvil);

	// 케르베로스 2. Cerberus
	pEvil = new CCerberus;
	if (nullptr != pEvil)
	{
		pEvil->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));
		pEvil->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(15, ON_OBJECT);
		pEvil->Set_ObjIndex(15);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pEvil);

	// 케르베로스 3. Cerberus
	pEvil = new CCerberus;
	if (nullptr != pEvil)
	{
		pEvil->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(16));
		pEvil->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(16, ON_OBJECT);
		pEvil->Set_ObjIndex(16);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pEvil);
}

void CStage::Init_ChapterTHREE()
{
	// 골 인덱스 37
	g_iGoalIndex = 37;

	m_pPlayer->Set_Hp(m_ChapterHp[3]);
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(13));
	m_pPlayer->Set_ObjIndex(13);
	m_pPlayer->Set_Flag(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(13));

	// 말리나. Malina
	CObj* pEvil = new CMalina;
	if (nullptr != pEvil)
	{
		pEvil->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(38));
		pEvil->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(38, ON_OBJECT);
		pEvil->Set_ObjIndex(38);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pEvil);
}

void CStage::Init_ChapterFOUR()
{
	// 골 인덱스 12
	g_iGoalIndex = 12;

	m_pPlayer->Set_Hp(m_ChapterHp[4]);
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(25));
	m_pPlayer->Set_ObjIndex(25);
	m_pPlayer->Set_Flag(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(25));


	// 즈드라다. Zdrada
	CObj* pEvil = new CZdrada;
	if (nullptr != pEvil)
	{
		pEvil->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(13));
		pEvil->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(13, ON_OBJECT);
		pEvil->Set_ObjIndex(13);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pEvil);
}

void CStage::Init_ChapterFIVE()
{
	// 골 인덱스 77
	g_iGoalIndex = 77;

	m_pPlayer->Set_Hp(m_ChapterHp[5]);
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(12));
	m_pPlayer->Set_ObjIndex(12);
	m_pPlayer->Set_Flag(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(12));

	// 아자젤. Azazel
	CObj* pEvil = new CAzazel;
	if (nullptr != pEvil)
	{
		pEvil->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(78));
		pEvil->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(78, ON_OBJECT);
		pEvil->Set_ObjIndex(78);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pEvil);
}

void CStage::Init_ChapterSIX()
{
	// 골 인덱스 13
	g_iGoalIndex = 13;

	m_pPlayer->Set_Hp(m_ChapterHp[6]);
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(46));
	m_pPlayer->Set_ObjIndex(46);
	m_pPlayer->Set_Flag(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(46));

	// 저스티스. Justice
	CObj* pEvil = new CJustice;
	if (nullptr != pEvil)
	{
		pEvil->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(12));
		pEvil->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(12, ON_OBJECT);
		pEvil->Set_ObjIndex(12);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pEvil);
}

void CStage::Init_ChapterSeven()
{
	// 골 인덱스 13
	g_iGoalIndex = 27;

	m_pPlayer->Set_Hp(m_ChapterHp[6]);
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(126));
	m_pPlayer->Set_ObjIndex(126);
	m_pPlayer->Set_Flag(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(126));

	// 루시퍼. Lucifer
	CObj* pEvil = new CLucifer;
	if (nullptr != pEvil)
	{
		pEvil->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(5));
		pEvil->Initialize();
		dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(5, ON_OBJECT);
		pEvil->Set_ObjIndex(5);
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pEvil);
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

void CStage::Create_DeathEffect()
{
	m_pDeath = new CDeathEffect;
	m_pDeath->Set_Pos(D3DXVECTOR3{ m_pPlayer->Get_Info().vPos.x, m_pPlayer->Get_Info().vPos.y - 200, 0.f });
	m_pDeath->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, m_pDeath);
}

void CStage::Goal_Arrive()
{
	// TODO : 대화문 추가, 선택완료시 플레이어 클리어 모션

	CObjMgr::GetInstance()->Set_EvilWhite(true);

	if (L"Idle" == dynamic_cast<CPlayer*>(m_pPlayer)->Get_StateKey())
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->Set_StateKey(L"Clear");
		m_pPlayer->Set_fFrame(FRAME(0.f, 19.f, 0.7f));
	}

	// 다음 챕터로 전환.
	// TODO : 추후 씬체인지간 렌더링되는 UI 추가할 것.
	if (14.f <= m_pPlayer->Get_Frame().fFrame)
	{
		m_fTimer += 4.5f * CTimeMgr::GetInstance()->Get_TimeDelta();

		if (m_fTimer >= 7.f)
		{
			Change_NextChapter();
			Init_Chapter();
			m_fTimer = 0.f;
			CObjMgr::GetInstance()->Set_EvilWhite(false);
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Crush(false);
		}
	}
}

void CStage::Player_Death()
{
	if (true == m_pPlayer->Get_Dead())
	{
		// 죽을 때 이펙트 처리
		if (nullptr == m_pDeath)
		{
			if (m_fTimer <= 4.f)
				m_fTimer += 4.5f * CTimeMgr::GetInstance()->Get_TimeDelta();
			else
			{
				CObjMgr::GetInstance()->Delete_ID(CObjMgr::MONSTER);
				CObjMgr::GetInstance()->Delete_ID(CObjMgr::EVIL);
				CObjMgr::GetInstance()->Delete_ID(CObjMgr::WALL);
				CObjMgr::GetInstance()->Delete_ID(CObjMgr::EFFECT);

				Create_DeathEffect();

				// 임시로 안 보이게 위치 옮김
				m_pPlayer->Set_Pos(D3DXVECTOR3{ -500.f, -500.f, 0.f });
				m_pPlayer->Set_Flag(D3DXVECTOR3{ -500.f, -500.f, 0.f });
			}
		}
		else
		{
			// 이펙트 끝난 후 스테이지 초기화
			if (true == m_pDeath->Get_Dead())
			{
				// 이펙트 삭제 후 널포인터 지정 (다시 죽을 것을 대비해 초기화)
				m_pDeath = nullptr;

				m_pPlayer->Set_Dead(false);
				Init_Chapter();

				m_fTimer = 0.f;
			}
		}
	}
}

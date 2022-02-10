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

	// �÷��̾� ����
	CObj*		pPlayer = new CPlayer;

	if (nullptr != pPlayer)
		pPlayer->Initialize();
	CObjMgr::GetInstance()->Add_Object(CObjMgr::PLAYER, pPlayer);

	m_pPlayer = CObjMgr::GetInstance()->Get_Player();
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	// é�� �ʱ�ȭ
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
		// TODO : ���� ��(Ending Scene)?
		break;
	}
}

void CStage::Init_Chapter()
{
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
		Init_ChapterEIGHT();
		break;
	case CHAPTER_END:
		// TODO : ���� ��(Ending Scene)?
		break;
	}

	m_pBackGround->Release();
	dynamic_cast<CBackGround*>(m_pBackGround)->Select_Chapter(m_chapter);

}

void CStage::Init_ChapterZERO()
{
	m_pPlayer->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(15));

	// �ǵ����ī. Pandemonica
	CObj* pObj = new CPandemonica;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(61));
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);

	// ����. Monster
	pObj = new CMonster;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(22));
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::MONSTER, pObj);

	// ����. Monster
	pObj = new CMonster;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(30));
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::MONSTER, pObj);

	// ����. Monster
	pObj = new CMonster;
	if (nullptr != pObj)
	{
		pObj->Initialize();
		pObj->Set_Pos(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(32));
	}

	CObjMgr::GetInstance()->Add_Object(CObjMgr::MONSTER, pObj);
}

void CStage::Init_ChapterONE()
{
	// �𵥿콺. Modeus
	CObj* pObj = new CModeus;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterTWO()
{
	// �ɸ����ν�. Cerberus
	CObj* pObj = new CCerberus;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterTHREE()
{
	// ������. Malina
	CObj* pObj = new CMalina;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterFOUR()
{
	// �����. Zdrada
	CObj* pObj = new CZdrada;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterFIVE()
{
	// ������. Azazel
	CObj* pObj = new CAzazel;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterSIX()
{
	// ����Ƽ��. Justice
	CObj* pObj = new CJustice;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterSeven()
{
	// �����. Lucifer
	CObj* pObj = new CLucifer;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

void CStage::Init_ChapterEIGHT()
{
	// ������Ʈ. Judgement
	CObj* pObj = new CJudgement;
	if (nullptr != pObj)
		pObj->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EVIL, pObj);
}

// ��Ÿ ������Ʈ �ӽ� ������
/*
CObj* pObj = nullptr;

// ��. Wall
pObj = new CWall;
if (nullptr != pObj)
pObj->Initialize();

CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

// Ű. Key
pObj = new CKey;
if (nullptr != pObj)
pObj->Initialize();

CObjMgr::GetInstance()->Add_Object(CObjMgr::EVENT_OBJ, pObj);

// ����. Chest
pObj = new CChest;
if (nullptr != pObj)
pObj->Initialize();

CObjMgr::GetInstance()->Add_Object(CObjMgr::EVENT_OBJ, pObj);

// Ʈ��. Trap
pObj = new CTrap;
if (nullptr != pObj)
pObj->Initialize();

CObjMgr::GetInstance()->Add_Object(CObjMgr::TRAP, pObj);

// �÷��Ӻ��̽�. FlameBase
pObj = new CFlameBase;
if (nullptr != pObj)
pObj->Initialize();

CObjMgr::GetInstance()->Add_Object(CObjMgr::WALL, pObj);

*/
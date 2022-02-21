#pragma once

#include "Scene.h"
#include "Obj.h"

class CStage : public CScene
{
private:
	CStage();
	~CStage();

public:
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Late_Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;

public:
	static CStage*		Create(void);

private:
	void	Change_NextChapter();

	void	Init_ChapterHp();
	void	Init_Chapter();
	void	Init_ChapterZERO();
	void	Init_ChapterONE();
	void	Init_ChapterTWO();
	void	Init_ChapterTHREE();
	void	Init_ChapterFOUR();
	void	Init_ChapterFIVE();
	void	Init_ChapterSIX();
	void	Init_ChapterSeven();
	void	Init_ChapterEIGHT();

	void	Create_DeathEffect();
	void	Create_Transition();

	void	Goal_Arrive();		// 목적지 도착
	void	Player_Death();		// 체력 소모로 인한 플레이어 사망

private:
	CObj*	m_pPlayer;		// 플레이어
	CObj*	m_pBackGround;	// 백그라운드 보관
	CObj*	m_pDeath;		// 데스 이펙트
	CHAPTER	m_chapter;		// 챕터 저장

	int		m_ChapterHp[9];	// 챕터별(0~8) 플레이어의 Hp 맥스 저장

	float	m_fTimer;		// 타이머 (딜레이용)

};


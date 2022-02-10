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

private:
	CObj*	m_pPlayer;		// 플레이어
	CObj*	m_pBackGround;	// 백그라운드 보관
	CHAPTER	m_chapter;		// 챕터 저장
};


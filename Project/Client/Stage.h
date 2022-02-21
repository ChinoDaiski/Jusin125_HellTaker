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

	void	Goal_Arrive();		// ������ ����
	void	Player_Death();		// ü�� �Ҹ�� ���� �÷��̾� ���

private:
	CObj*	m_pPlayer;		// �÷��̾�
	CObj*	m_pBackGround;	// ��׶��� ����
	CObj*	m_pDeath;		// ���� ����Ʈ
	CHAPTER	m_chapter;		// é�� ����

	int		m_ChapterHp[9];	// é�ͺ�(0~8) �÷��̾��� Hp �ƽ� ����

	float	m_fTimer;		// Ÿ�̸� (�����̿�)

};


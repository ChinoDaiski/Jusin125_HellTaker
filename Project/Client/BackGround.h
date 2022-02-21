#pragma once
#include "Obj.h"
#include "Grid.h"
#include "ObjMgr.h"

class CBackGround : public CObj
{
public:
	CBackGround();
	virtual ~CBackGround();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	void	Create_Grid(void);
	void	Map_Init(void);
	
	void	Part1_ChapterInit();
	void	Part2_ChapterInit();
	void	Part3_ChapterInit();

public:
	GRID_INFO&	Get_GridInfo() { return m_GridInfo; }
	void		Set_GridInfo(GRID_INFO _GridInfo) { m_GridInfo = _GridInfo; }

	void		Select_Chapter(CHAPTER _chapter);

	D3DXVECTOR3	Find_IndexPos(int _index);			// �Ű����� �ε����� ���� �ε����� ���� �׸����� vPos ��ȯ
	GRID_STATE	Find_IndexBlock(int _index);		// �Ű����� �ε����� ���� �ε����� ���� �׸����� GRID_STATE �Ӽ� ��ȯ
	void		Set_GridState(int _index, GRID_STATE _gridState);

	void		Set_Vive(bool _vive) { m_bVibration = _vive; }

	void		Picking(D3DXVECTOR3 _pos);

private:
	vector<CObj*>	vecGrid;
	CObj*	m_pGrid; 

	CHAPTER		m_Chapter;		// é�� ��ȣ. switch~case ���
	GRID_INFO	m_GridInfo;		// Grid ���ڸ� é�Ϳ� ���� �����Ͽ� ��� ����

	bool		m_bVibration;	// �÷��̾� �ǰݽ� ȭ�� ���� ȿ��
	int			m_iViveCount;	// ���� ī��Ʈ
};


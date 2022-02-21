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

	D3DXVECTOR3	Find_IndexPos(int _index);			// 매개변수 인덱스와 같은 인덱스를 가진 그리드의 vPos 반환
	GRID_STATE	Find_IndexBlock(int _index);		// 매개변수 인덱스와 같은 인덱스를 가진 그리드의 GRID_STATE 속성 반환
	void		Set_GridState(int _index, GRID_STATE _gridState);

	void		Set_Vive(bool _vive) { m_bVibration = _vive; }

	void		Picking(D3DXVECTOR3 _pos);

private:
	vector<CObj*>	vecGrid;
	CObj*	m_pGrid; 

	CHAPTER		m_Chapter;		// 챕터 번호. switch~case 사용
	GRID_INFO	m_GridInfo;		// Grid 격자를 챕터에 따라 변경하여 출력 위함

	bool		m_bVibration;	// 플레이어 피격시 화면 진동 효과
	int			m_iViveCount;	// 진동 카운트
};


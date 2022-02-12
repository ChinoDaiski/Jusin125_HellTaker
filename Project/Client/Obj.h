#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual HRESULT		Initialize(void)PURE;
	virtual int			Update(void)PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(void)PURE;
	virtual void		Release(void)PURE;

	virtual void		Moving();			// 이동 자연스럽게 하기

public:
	const wstring& GetObjKey(void) const { return m_wstrObjKey; }
	void			Set_ObjKey(wstring _ObjKey) { m_wstrObjKey = _ObjKey; }
	void			MoveFrame(void);

public:
	void			Set_Damage(void) {
		--m_iHp;
		if (m_iHp <= 0)
			m_bDead = true;
	}

	void			Set_fFrame(FRAME _fFrame) { m_tFrame = _fFrame; }

	void			Set_Pos(D3DXVECTOR3 _vecPos) { m_tInfo.vPos = _vecPos; }
	INFO&			Get_Info() { return m_tInfo; }

	void			Set_ObjIndex(int _index) { m_ObjIndex = _index; }
	int				Get_ObjIndex() { return m_ObjIndex; }

	void		Set_GridState(GRID_STATE _gridstate) { m_GridState = _gridstate; }
	GRID_STATE	Get_GridState() { return m_GridState; }

	DIR				Get_Dir() { return m_Dir; }

	D3DXVECTOR3		Get_Flag() { return m_vFlag; }
	void			Set_Flag(D3DXVECTOR3 _vFlag) { m_vFlag = _vFlag; }

	void			Set_moving(bool _moving) { moving = _moving; }

protected:
	static D3DXVECTOR3			m_vScroll;		// 스크롤
	INFO		m_tInfo;						// 객체의 좌표 정보
	FRAME		m_tFrame;						// 객체 스프라이트 프레임

	bool		m_bInit = false;		// 얜 머지
	bool		moving;					// 움직이는 상태면 true
	
	wstring		m_wstrObjKey = L"";		// 객체의 렌더링 모습 상태
	float		m_fSpeed = 0.f;			// Speed

	bool		m_bDead;				// m_iHp 가 0 이하면 true
	int			m_iHp;					// 객체의 체력/목숨

	int			m_ObjIndex;				// 객체가 위치한 인덱스
	DIR			m_Dir;					// 오브젝트 방향

	GRID_STATE	m_GridState;			// 격자의 속성

	D3DXVECTOR3	m_vFlag;				// 가야할 곳의 위치 저장
	float		m_fDistance;			// m_Flag 와의 거리
	float		m_fAngle;				// 가야할 곳과의 각도
};


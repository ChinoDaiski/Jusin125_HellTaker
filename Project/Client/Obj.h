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

public:
	const wstring& GetObjKey(void) const { return m_wstrObjKey; }
	void			MoveFrame(void);

public:
	void			Set_Damage(void) {
		--m_iHp;
		if (m_iHp <= 0)
			m_bDead = true;
	}

	void			Set_Pos(D3DXVECTOR3 _vecPos) { m_tInfo.vPos = _vecPos; }
	INFO&			Get_Info() { return m_tInfo; }

	void			Set_ObjIndex(int _index) { m_ObjIndex = _index; }
	bool			Get_Block() { return m_bBlock; }

protected:
	static D3DXVECTOR3			m_vScroll;		// 스크롤
	INFO		m_tInfo;						// 객체의 좌표 정보
	FRAME		m_tFrame;						// 객체 스프라이트 프레임

	bool		m_bInit = false;		// 얜 머지
	
	wstring		m_wstrObjKey = L"";		// 객체의 렌더링 모습 상태
	float		m_fSpeed = 0.f;			// Speed

	bool		m_bDead;				// m_iHp 가 0 이하면 true
	int			m_iHp;					// 객체의 체력/목숨

	int			m_ObjIndex;				// 객체가 위치한 인덱스
	DIR			m_Dir;					// 오브젝트 방향

	bool		m_bBlock;				// 객체의 장애물 판단 (true면 장애물)
};


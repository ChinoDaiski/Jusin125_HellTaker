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


protected:
	static D3DXVECTOR3			m_vScroll;
	INFO		m_tInfo;
	FRAME		m_tFrame;

	bool		m_bInit = false;
	
	wstring		m_wstrObjKey = L"";
	float		m_fSpeed = 0.f;

	bool		m_bDead;
	int			m_iHp;

	int			m_iIndexPos;
};


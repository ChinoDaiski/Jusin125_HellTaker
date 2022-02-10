#pragma once
#include "Obj.h"
#include "BackGround.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void		Set_GroundPtr(CObj* pObj) { m_pBackGround = pObj; };

private:
	void		Key_Input(void);		// 방향키 입력

private:
	wstring			m_wstrStateKey = L"";
	CObj*			m_pBackGround;
};


#pragma once
#include "Obj.h"
class CGameButton : public CObj {
public:
	CGameButton();
	virtual ~CGameButton();

public:
	virtual HRESULT		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(void) override;
	virtual void		Render(void) override;
	virtual void		Release(void) override;

private:
	int		m_iOption;		// 기본 : 0, 선택 시 : 1
};


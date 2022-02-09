#pragma once
#include "Obj.h"
class CTransparency : public CObj {
public:
	CTransparency();
	virtual ~CTransparency();

public:
	virtual HRESULT		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(void) override;
	virtual void		Render(void) override;
	virtual void		Release(void) override;

private:
	int					m_iRunningTime;
	float				m_fDeltaTime;
	float				m_fTransparency;
};


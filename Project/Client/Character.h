#pragma once
#include "Obj.h"
class CCharacter : public CObj {
public:
	CCharacter();
	virtual ~CCharacter();

public:
	enum ID { Baal, End };

public:
	virtual HRESULT		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(void) override;
	virtual void		Render(void) override;
	virtual void		Release(void) override;

private:
	ID			m_eID;
};


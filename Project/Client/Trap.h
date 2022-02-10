#pragma once
#include "Obj.h"

class CTrap : public CObj
{
	enum ACTIVE { ON, OFF, ON_READY, OFF_READY, STOP };

public:
	CTrap();
	virtual ~CTrap();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	ACTIVE		Get_Active() { return m_Active; }
	void		Set_Active(ACTIVE _active) { m_Active = _active; }

private:
	void	Active_Trap();

private:
	ACTIVE		m_Active;		// -1 == ON, 0 == REVERSE, 1 == ON_READY, 2 == OFF 
};


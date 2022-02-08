#pragma once
#include "Obj.h"

class CTrap : public CObj
{
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
	bool	Get_Active() { return m_Active; }
	void	Set_Active(bool _active) { m_Active = _active; }

private:
	bool	m_Active = true;		// true �̸� ���ð� �ö��(Up), false �̸� ������(Down)
};


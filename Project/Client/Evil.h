#pragma once
#include "Obj.h"

class CEvil : public CObj
{
public:
	CEvil();
	virtual ~CEvil();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

protected:
	void		Create_LoveSign();

private:
	CObj*	m_pLoveSign;
};
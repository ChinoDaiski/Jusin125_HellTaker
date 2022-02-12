#pragma once
#include "Evil.h"

class CAzazel : public CEvil
{
public:
	CAzazel();
	virtual ~CAzazel();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(void);
	virtual void Release(void);

};


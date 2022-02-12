#pragma once
#include "Evil.h"

class CCerberus : public CEvil
{
public:
	CCerberus();
	virtual ~CCerberus();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(void);
	virtual void Release(void);

};


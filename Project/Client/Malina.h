#pragma once
#include "Evil.h"

class CMalina : public CEvil
{
public:
	CMalina();
	virtual ~CMalina();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(void);
	virtual void Release(void);

};


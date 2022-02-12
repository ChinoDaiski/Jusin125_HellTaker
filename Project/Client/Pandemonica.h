#pragma once
#include "Evil.h"

class CPandemonica : public CEvil
{
public:
	CPandemonica();
	virtual ~CPandemonica();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(void);
	virtual void Release(void);

};


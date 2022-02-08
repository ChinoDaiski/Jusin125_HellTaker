#pragma once
#include "Obj.h"

class CPandemonica : public CObj
{
public:
	CPandemonica();
	virtual ~CPandemonica();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};


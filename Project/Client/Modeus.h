#pragma once
#include "Obj.h"

class CModeus : public CObj
{
public:
	CModeus();
	virtual ~CModeus();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};


#pragma once
#include "Effect.h"

class CDeathBackGround : public CEffect
{
public:
	CDeathBackGround();
	virtual ~CDeathBackGround();

public:
	virtual HRESULT Initialize(void) override;
	virtual void Late_Update(void) override;
};


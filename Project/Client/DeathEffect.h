#pragma once
#include "Effect.h"

class CDeathEffect : public CEffect
{
public:
	CDeathEffect();
	virtual ~CDeathEffect();

public:
	virtual HRESULT Initialize(void) override;
};


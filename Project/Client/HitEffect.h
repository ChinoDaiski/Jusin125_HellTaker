#pragma once
#include "Effect.h"

class CHitEffect : public CEffect
{
public:
	CHitEffect();
	virtual ~CHitEffect();

public:
	virtual HRESULT Initialize(void) override;
};


#pragma once
#include "Effect.h"

class CMoveEffect : public CEffect
{
public:
	CMoveEffect();
	virtual ~CMoveEffect();

public:
	virtual HRESULT Initialize(void) override;
};


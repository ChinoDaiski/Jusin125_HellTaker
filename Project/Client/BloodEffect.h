#pragma once
#include "Effect.h"

class CBloodEffect : public CEffect
{
public:
	CBloodEffect();
	virtual ~CBloodEffect();

public:
	virtual HRESULT Initialize(void) override;
};


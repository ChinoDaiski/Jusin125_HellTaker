#pragma once
#include "Effect.h"

class CLoveBomb : public CEffect
{
public:
	CLoveBomb();
	virtual ~CLoveBomb();

public:
	virtual HRESULT Initialize(void) override;
};


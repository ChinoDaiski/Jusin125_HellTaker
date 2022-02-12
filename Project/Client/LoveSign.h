#pragma once
#include "Effect.h"

class CLoveSign : public CEffect
{
public:
	CLoveSign();
	virtual ~CLoveSign();

public:
	virtual HRESULT Initialize(void) override;
	virtual void Late_Update(void) override;
};


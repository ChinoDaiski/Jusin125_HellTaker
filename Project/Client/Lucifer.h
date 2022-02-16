#pragma once
#include "Evil.h"

class CLucifer : public CEvil
{
public:
	CLucifer();
	virtual ~CLucifer();

public:
	virtual HRESULT Initialize(void) override;

};


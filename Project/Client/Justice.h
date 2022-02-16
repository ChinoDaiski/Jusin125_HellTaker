#pragma once
#include "Evil.h"

class CJustice : public CEvil
{
public:
	CJustice();
	virtual ~CJustice();

public:
	virtual HRESULT Initialize(void) override;
};


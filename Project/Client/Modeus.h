#pragma once
#include "Evil.h"

class CModeus : public CEvil
{
public:
	CModeus();
	virtual ~CModeus();

public:
	virtual HRESULT Initialize(void) override;
};


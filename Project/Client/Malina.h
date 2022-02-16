#pragma once
#include "Evil.h"

class CMalina : public CEvil
{
public:
	CMalina();
	virtual ~CMalina();

public:
	virtual HRESULT Initialize(void) override;
};


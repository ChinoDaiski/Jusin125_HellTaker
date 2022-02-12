#pragma once
#include "Evil.h"

class CPandemonica : public CEvil
{
public:
	CPandemonica();
	virtual ~CPandemonica();

public:
	virtual HRESULT Initialize(void) override;
};


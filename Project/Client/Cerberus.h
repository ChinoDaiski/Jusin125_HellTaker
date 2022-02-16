#pragma once
#include "Evil.h"

class CCerberus : public CEvil
{
public:
	CCerberus();
	virtual ~CCerberus();

public:
	virtual HRESULT Initialize(void) override;

};


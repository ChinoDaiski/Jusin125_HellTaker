#pragma once
#include "Evil.h"

class CAzazel : public CEvil
{
public:
	CAzazel();
	virtual ~CAzazel();

public:
	virtual HRESULT Initialize(void) override;
};


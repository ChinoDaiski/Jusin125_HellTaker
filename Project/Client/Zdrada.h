#pragma once
#include "Evil.h"

class CZdrada : public CEvil
{
public:
	CZdrada();
	virtual ~CZdrada();
public:
	virtual HRESULT Initialize(void) override;
};


#pragma once
#include "Evil.h"

class CZdrada : public CEvil
{
public:
	CZdrada();
	virtual ~CZdrada();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(void);
	virtual void Release(void);

};


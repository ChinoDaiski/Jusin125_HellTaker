#pragma once
#include "Obj.h"

class CZdrada : public CObj
{
public:
	CZdrada();
	virtual ~CZdrada();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};


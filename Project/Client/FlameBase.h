#pragma once
#include "Obj.h"

class CFlameBase : public CObj
{
public:
	CFlameBase();
	virtual ~CFlameBase();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	void	Create_Fire(void);
};


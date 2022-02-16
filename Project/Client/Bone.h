#pragma once
#include "Effect.h"

class CBone : public CEffect
{
public:
	CBone();
	virtual ~CBone();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Moving() override;

private:
	float	m_fPower;
	float	m_fTime;
};


#pragma once
#include "Effect.h"

class CDeathEffect : public CEffect
{
public:
	CDeathEffect();
	virtual ~CDeathEffect();

private:
	void	Create_DeathBackGround();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;

private:
	CObj*	m_pDeathBackGround;
};


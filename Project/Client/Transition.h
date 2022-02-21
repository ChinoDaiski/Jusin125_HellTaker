#pragma once
#include "Effect.h"

class CTransition : public CEffect
{
public:
	CTransition();
	virtual ~CTransition();

public:
	virtual HRESULT Initialize(void) override;
	virtual void Late_Update(void) override;

private:
	float	m_fTimeDelta;
};


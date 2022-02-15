#pragma once
#include "Effect.h"

class CHeart : public CEffect
{
public:
	CHeart();
	virtual ~CHeart();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	
	virtual void Moving() override;

private:
	// 난수값 저장
	float	m_fRandom;
	float	m_fDeadCount;
};


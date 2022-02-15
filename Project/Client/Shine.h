#pragma once
#include "Effect.h"

class CShine : public CEffect
{
public:
	CShine();
	virtual ~CShine();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;

public:
	void	Set_Pink(bool _pink) { m_bPink = _pink; }

private:
	bool	m_bPink = false;
};


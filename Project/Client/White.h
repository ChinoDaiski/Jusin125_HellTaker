#pragma once
#include "Evil.h"

class CWhite : public CEvil
{
public:
	CWhite();
	virtual ~CWhite();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;

private:
	int		m_trans;			// 투명도 관리
};


#pragma once
#include "Evil.h"

class CJudgement : public CEvil
{
public:
	CJudgement();
	virtual ~CJudgement();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void);
	virtual void Late_Update(void);

public:
	void	Set_Jump();

private:
	wstring		m_wstrStateKey = L"";

	bool	m_Jump = false;	// 점프 상태일 때 true
};


#pragma once
#include "Obj.h"

class CJudgement : public CObj
{
public:
	CJudgement();
	virtual ~CJudgement();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void	Set_Jump();

private:
	wstring		m_wstrStateKey = L"";

	bool	m_Jump = false;	// 점프 상태일 때 true
};


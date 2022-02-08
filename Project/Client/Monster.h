#pragma once
#include "Obj.h"

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void	Set_Hit();

private:
	wstring		m_wstrStateKey = L"";

	bool		m_Hit = false;		// 타격받을 때 true
};


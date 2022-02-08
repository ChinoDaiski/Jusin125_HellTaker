#pragma once
#include "Obj.h"

class CWall : public CObj
{
public:
	CWall();
	virtual ~CWall();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	int m_iOption;		// 벽의 종류 옵션
};


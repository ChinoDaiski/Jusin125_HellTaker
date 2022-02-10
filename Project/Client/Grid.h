#pragma once
#include "Obj.h"

class CGrid : public CObj
{
public:
	CGrid();
	virtual ~CGrid();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void	Set_Index(int _index) { m_iIndex = _index; }
	int		Get_Index() { return m_iIndex; }

private:
	int		m_iIndex;	// 격자 인덱스
};


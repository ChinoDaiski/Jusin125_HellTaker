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

	void	Set_OnObject(bool _check) { m_bOnObject = _check; }
	bool	Get_OnObject() { return m_bOnObject; }

private:
	int		m_iIndex;		// 격자 인덱스
	bool	m_bOnObject;	// 격자 위에 Object 가 있다면 true
};


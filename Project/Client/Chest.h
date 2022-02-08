#pragma once
#include "Obj.h"

class CChest : public CObj
{
public:
	CChest();
	virtual ~CChest();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void	Set_Open() { m_Open = true; }		// ���� �˻� �� Open => true

private:
	bool	m_Open = false;	// ������ ���� �Ǵ�
};


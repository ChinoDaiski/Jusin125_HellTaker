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
	void		Create_MoveEffect();

private:
	int m_iOption;		// ���� ���� �ɼ�

	int		moveCount;
	int		m_effect;
};


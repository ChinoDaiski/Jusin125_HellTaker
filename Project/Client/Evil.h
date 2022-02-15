#pragma once
#include "Obj.h"

class CEvil : public CObj
{
public:
	CEvil();
	virtual ~CEvil();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void		Set_White(bool _white) { m_White = _white; }

protected:
	void		ClearMotion();
	void		Create_LoveSign();
	void		Create_LoveBomb();
	void		Create_Shine();
	void		Create_Shine(bool _pink);
	void		Create_Heart();

private:
	CObj*	m_pLoveSign;
	CObj*	m_pLoveBomb;
	CObj*	m_pPlayer;	

	float	m_fDeadCount;		// �ױ� �� ����Ʈ ����
	bool	m_White;			// �ױ� �� �Ͼ�� ��������
};
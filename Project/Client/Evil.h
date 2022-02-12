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
	void		Create_LoveSign();
	void		Create_LoveBomb();

private:
	CObj*	m_pLoveSign;
	CObj*	m_pLoveBomb;

	float	m_fDeadCount;		// Á×±â Àü ÀÌÆåÆ® ´ë±â¿ë
	bool	m_White;			// Á×±â Àü ÇÏ¾á»ö ·»´õ¸µ¿ë
};
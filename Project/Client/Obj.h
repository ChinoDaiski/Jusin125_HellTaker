#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual HRESULT		Initialize(void)PURE;
	virtual int			Update(void)PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(void)PURE;
	virtual void		Release(void)PURE;

public:
	const wstring& GetObjKey(void) const { return m_wstrObjKey; }
	void			MoveFrame(void);

public:
	void			Set_Damage(void) {
		--m_iHp;
		if (m_iHp <= 0)
			m_bDead = true;
	}

	void			Set_Pos(D3DXVECTOR3 _vecPos) { m_tInfo.vPos = _vecPos; }
	INFO&			Get_Info() { return m_tInfo; }

	void			Set_ObjIndex(int _index) { m_ObjIndex = _index; }
	bool			Get_Block() { return m_bBlock; }

protected:
	static D3DXVECTOR3			m_vScroll;		// ��ũ��
	INFO		m_tInfo;						// ��ü�� ��ǥ ����
	FRAME		m_tFrame;						// ��ü ��������Ʈ ������

	bool		m_bInit = false;		// �� ����
	
	wstring		m_wstrObjKey = L"";		// ��ü�� ������ ��� ����
	float		m_fSpeed = 0.f;			// Speed

	bool		m_bDead;				// m_iHp �� 0 ���ϸ� true
	int			m_iHp;					// ��ü�� ü��/���

	int			m_ObjIndex;				// ��ü�� ��ġ�� �ε���
	DIR			m_Dir;					// ������Ʈ ����

	bool		m_bBlock;				// ��ü�� ��ֹ� �Ǵ� (true�� ��ֹ�)
};


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

	virtual void		Moving();			// �̵� �ڿ������� �ϱ�

public:
	const wstring& GetObjKey(void) const { return m_wstrObjKey; }
	void			Set_ObjKey(wstring _ObjKey) { m_wstrObjKey = _ObjKey; }
	void			MoveFrame(void);

public:
	void			Set_Damage(void) {
		--m_iHp;
		if (m_iHp <= 0)
			m_bDead = true;
	}

	void			Set_fFrame(FRAME _fFrame) { m_tFrame = _fFrame; }

	void			Set_Pos(D3DXVECTOR3 _vecPos) { m_tInfo.vPos = _vecPos; }
	INFO&			Get_Info() { return m_tInfo; }

	void			Set_ObjIndex(int _index) { m_ObjIndex = _index; }
	int				Get_ObjIndex() { return m_ObjIndex; }

	void		Set_GridState(GRID_STATE _gridstate) { m_GridState = _gridstate; }
	GRID_STATE	Get_GridState() { return m_GridState; }

	DIR				Get_Dir() { return m_Dir; }

	D3DXVECTOR3		Get_Flag() { return m_vFlag; }
	void			Set_Flag(D3DXVECTOR3 _vFlag) { m_vFlag = _vFlag; }

	void			Set_moving(bool _moving) { moving = _moving; }

protected:
	static D3DXVECTOR3			m_vScroll;		// ��ũ��
	INFO		m_tInfo;						// ��ü�� ��ǥ ����
	FRAME		m_tFrame;						// ��ü ��������Ʈ ������

	bool		m_bInit = false;		// �� ����
	bool		moving;					// �����̴� ���¸� true
	
	wstring		m_wstrObjKey = L"";		// ��ü�� ������ ��� ����
	float		m_fSpeed = 0.f;			// Speed

	bool		m_bDead;				// m_iHp �� 0 ���ϸ� true
	int			m_iHp;					// ��ü�� ü��/���

	int			m_ObjIndex;				// ��ü�� ��ġ�� �ε���
	DIR			m_Dir;					// ������Ʈ ����

	GRID_STATE	m_GridState;			// ������ �Ӽ�

	D3DXVECTOR3	m_vFlag;				// ������ ���� ��ġ ����
	float		m_fDistance;			// m_Flag ���� �Ÿ�
	float		m_fAngle;				// ������ ������ ����
};


#pragma once
#include "Obj.h"
#include "BackGround.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void		Set_GroundPtr(CObj* pObj) { m_pBackGround = pObj; };

private:
	void		Key_Input(void);				// ����Ű �Է�
	bool		DontMove(int _index);			// �ʵ��� ���� ���� �� �������� ����

	void		Create_HitEffect(D3DXVECTOR3 _pos);
	void		Create_MoveEffect(D3DXVECTOR3 _pos);

	void		Moving(void);		// �����̴� ���� ��

private:
	wstring			m_wstrStateKey = L"";
	CObj*			m_pBackGround;
	DIR				m_PreDir;		// ���� ����

	int				moveCount;		// MoveEffect ī��Ʈ (0~3 �ݺ�)
	bool			moving;			// �����̴� ���¸� true
};


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
	void		Set_StateKey(wstring _stateKey) { m_wstrStateKey = _stateKey; }
	wstring		Get_StateKey() { return m_wstrStateKey; }

	void		Set_Crush(bool _crush) { m_bCrush = _crush; }

private:
	void		Key_Input(void);				// ����Ű �Է�
	bool		CheckTile(int _index);			// �ʵ��� ���� ���� �� �������� ����
	void		ClearMotion();

	void		Create_HitEffect(D3DXVECTOR3 _pos);
	void		Create_MoveEffect(D3DXVECTOR3 _pos);

	void		Create_Bone();
	void		Create_Blood(D3DXVECTOR3 _pos);

	void		Synchro_Scroll();				// ��ũ�� ����ȭ

private:
	wstring			m_wstrStateKey = L"";
	CObj*			m_pBackGround;
	DIR				m_PreDir;		// ���� ����

	int				moveCount;				// MoveEffect ī��Ʈ (0~2 �ݺ�)
	int				bloodCount;				// BloodEffect ī��Ʈ (0~2 �ݺ�)

	bool			bleeding;				// Ʈ���� �°� ���� ��
	float			bleedingCount;			// ���� ���ӽð�
	int				bloodColor;				// ���� ��������

	bool			m_bCrush = false;		// Ŭ����� ����ġ�� ��ǿ�		
	float			m_fClearCount;			// Clear 3������ ��
};


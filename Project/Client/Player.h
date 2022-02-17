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
	void		Key_Input(void);				// 방향키 입력
	bool		CheckTile(int _index);			// 필드의 끝에 있을 때 움직이지 않음
	void		ClearMotion();

	void		Create_HitEffect(D3DXVECTOR3 _pos);
	void		Create_MoveEffect(D3DXVECTOR3 _pos);

	void		Create_Bone();
	void		Create_Blood(D3DXVECTOR3 _pos);

	void		Synchro_Scroll();				// 스크롤 동기화

private:
	wstring			m_wstrStateKey = L"";
	CObj*			m_pBackGround;
	DIR				m_PreDir;		// 이전 방향

	int				moveCount;				// MoveEffect 카운트 (0~2 반복)
	int				bloodCount;				// BloodEffect 카운트 (0~2 반복)

	bool			bleeding;				// 트랩에 맞고 출혈 중
	float			bleedingCount;			// 출혈 지속시간
	int				bloodColor;				// 출혈 렌더링용

	bool			m_bCrush = false;		// 클리어시 내리치는 모션용		
	float			m_fClearCount;			// Clear 3프레임 용
};


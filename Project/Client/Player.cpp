#include "stdafx.h"
#include "Player.h"

#include "Device.h"
#include "TextureMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

#include "BackGround.h"

#include "MoveEffect.h"
#include "HitEffect.h"
#include "BloodEffect.h"

#include "Bone.h"

CPlayer::CPlayer()
	: moveCount(0), bloodCount(0)
	, m_fClearCount(0.f)
	, bleeding(false), bleedingCount(0.f), bloodColor(70)
{
	// empty
}

CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	// Idle
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Player/Idle/idle%d.png", L"Player", L"Idle", 12)))
		return S_FALSE;

	// Kick
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Player/Attack/Kick/kick%d.png", L"Player", L"Kick", 13)))
		return S_FALSE;

	// Clear
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Player/Clear/clear%d.png", L"Player", L"Clear", 19)))
		return S_FALSE;

	// Move
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Player/Move/move%d.png", L"Player", L"Move", 6)))
		return S_FALSE;

	m_wstrObjKey = L"Player";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 800.f;

	m_tFrame = { 0.f, 12.f };

	m_Dir = DIR_RIGHT;
	m_PreDir = DIR_RIGHT;

	return S_OK;
}

int CPlayer::Update(void)
{
	// 키 입력
	if (m_iHp > 0 && L"Clear" != m_wstrStateKey)
		Key_Input();

	// 이동 or 죽음 처리
	if (true == moving)
	{
		Moving();
		m_fClearCount = 0.f;
	}
	else
	{
		if (m_iHp <= 0)
			m_bDead = true;
	}

	// 출혈중
	if (bleeding)
	{
		if (bleedingCount <= 4.f)
		{
			bleedingCount += 3.f * CTimeMgr::GetInstance()->Get_TimeDelta();
			
			if(bloodColor < 255)
				++bloodColor;
		}
		else
		{
			bleeding = false;
			bleedingCount = 0.f;
			bloodColor = 70;
		}
	}

	D3DXMATRIX	matTrans, matScale;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	if (DIR_RIGHT == m_Dir)
		D3DXMatrixScaling(&matScale, MAPSIZEX, MAPSIZEY, 1.f);
	else if (DIR_LEFT == m_Dir)
		D3DXMatrixScaling(&matScale, -MAPSIZEX, MAPSIZEY, 1.f);
	else
	{
		if (DIR_RIGHT == m_PreDir)
			D3DXMatrixScaling(&matScale, MAPSIZEX, MAPSIZEY, 1.f);
		else if (DIR_LEFT == m_PreDir)
			D3DXMatrixScaling(&matScale, -MAPSIZEX, MAPSIZEY, 1.f);
	}

	m_tInfo.matWorld = matScale * matTrans;
	
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (7 == CObj::m_iChapterNum)
		Synchro_Scroll();

	if(L"Idle" == m_wstrStateKey)
		MoveFrame();
	else if (L"Clear" == m_wstrStateKey)
		ClearMotion();
	else
	{
		MoveFrame();
		if (0.f == m_tFrame.fFrame)
		{
			m_wstrStateKey = L"Idle";
			m_tFrame = { 0.f, 12.f };
		}
	}
}

void CPlayer::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	if (nullptr == pTexInfo)
		return;

	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	// 행렬을 장치를 이용하여 모든 정점에 곱해주는 함수
	CDevice::GetInstance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	if (bleeding)
	{
		CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
			nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
			nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
			D3DCOLOR_ARGB(255, 255, bloodColor, bloodColor)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지
	}
	else
	{
		CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
			nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
			nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
			D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지
	}
}

void CPlayer::Release(void)
{
	// empty
}

void CPlayer::Key_Input(void)
{
	// 윗쪽 방향키. UP
	if (CKeyMgr::GetInstance()->Key_Down(VK_UP))
	{
		m_Dir = DIR_UP;

		if (CheckTile(m_ObjIndex -
			(dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jEnd_Index -
				dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jStart_Index)))
			return;

		Create_MoveEffect(m_tInfo.vPos);

		m_vFlag = dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos
		(m_ObjIndex - 
			(dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jEnd_Index - 
			dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jStart_Index));
		Set_ObjIndex(m_ObjIndex -
			(dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jEnd_Index -
			dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jStart_Index));

		--m_iHp;
		moving = true;
	}
	// 아래쪽 방향키. DOWN
	else if (CKeyMgr::GetInstance()->Key_Down(VK_DOWN))
	{
		m_Dir = DIR_DOWN;

		if (CheckTile(m_ObjIndex +
			(dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jEnd_Index -
				dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jStart_Index)))
			return;

		Create_MoveEffect(m_tInfo.vPos);

		m_vFlag = dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos
		(m_ObjIndex +
			(dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jEnd_Index -
				dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jStart_Index));
		Set_ObjIndex(m_ObjIndex +
			(dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jEnd_Index -
				dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jStart_Index));

		--m_iHp;
		moving = true;
	}
	// 왼쪽 방향키. LEFT
	else if (CKeyMgr::GetInstance()->Key_Down(VK_LEFT))
	{
		m_Dir = DIR_LEFT;
		m_PreDir = DIR_LEFT;

		if (CheckTile(m_ObjIndex - 1))
			return;

		Create_MoveEffect(m_tInfo.vPos);

		m_vFlag = dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(m_ObjIndex - 1);
		Set_ObjIndex(m_ObjIndex - 1);

		--m_iHp;
		moving = true;
	}
	// 오른쪽 방향키. RIGHT
	else if (CKeyMgr::GetInstance()->Key_Down(VK_RIGHT))
	{
		m_Dir = DIR_RIGHT;
		m_PreDir = DIR_RIGHT;

		if (CheckTile(m_ObjIndex + 1))
			return;

		Create_MoveEffect(m_tInfo.vPos);

		m_vFlag = dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(m_ObjIndex + 1);
		Set_ObjIndex(m_ObjIndex + 1);

		--m_iHp;
		moving = true;
	}

	// 피킹
	if (CKeyMgr::GetInstance()->Key_Down(VK_LBUTTON))
	{
		// 마우스 좌표 얻어오기
		D3DXVECTOR3 mouse = ::Get_Mouse();
		mouse.x -= CObj::m_vScroll.x;
		mouse.y -= CObj::m_vScroll.y;

		dynamic_cast<CBackGround*>(m_pBackGround)->Picking(mouse);
	}

	// 세이브
	if (CKeyMgr::GetInstance()->Key_Down('S'))
	{
		dynamic_cast<CBackGround*>(m_pBackGround)->SaveData();
	}

	// 로드
	if (CKeyMgr::GetInstance()->Key_Down('L'))
	{
		//dynamic_cast<CBackGround*>(m_pBackGround)->LoadData();
	}
}

bool CPlayer::CheckTile(int _index)
{
	// 갈 수 없는 타일인지 판단
	if (CANT_MOVE == dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexBlock(_index))
		return true;
	// 오브젝트가 위에 있는지 판단
	else if (ON_OBJECT == dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexBlock(_index))
	{
		for(int i = 0; i < 15; ++i)
			Create_Bone();

		m_wstrStateKey = L"Kick";
		m_tFrame = { 0.f, 13.f, 2.4f };

		D3DXVECTOR3 pushPos;
		int			pushIndex;

		// 좌
		if (DIR_LEFT == m_Dir)
		{
			Create_HitEffect(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(_index));
			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_Flag(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(_index - 1));
			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_moving(true);
			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_ObjIndex(_index - 1);
			dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(_index, CAN_MOVE);
			dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(_index - 1, ON_OBJECT);
		}
		// 우
		else if (DIR_RIGHT == m_Dir)
		{
			Create_HitEffect(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(_index));
			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_Flag(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(_index + 1));
			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_moving(true);
			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_ObjIndex(_index + 1);
			dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(_index, CAN_MOVE);
			dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(_index + 1, ON_OBJECT);
		}
		// 상
		else if (DIR_UP == m_Dir)
		{
			pushPos = dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(
				_index - (dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jEnd_Index -
					dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jStart_Index));

			pushIndex = _index - (dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jEnd_Index -
				dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jStart_Index);

			Create_HitEffect(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(_index));

			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_Flag(pushPos);
			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_moving(true);
			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_ObjIndex(pushIndex);

			dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(_index, CAN_MOVE);
			dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(pushIndex, ON_OBJECT);
		}
		// 하
		else if (DIR_DOWN == m_Dir)
		{
			pushPos = dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(
				_index + (dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jEnd_Index -
					dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jStart_Index));

			pushIndex = _index + (dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jEnd_Index -
				dynamic_cast<CBackGround*>(m_pBackGround)->Get_GridInfo().jStart_Index);

			Create_HitEffect(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(_index));

			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_Flag(pushPos);
			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_moving(true);
			CObjMgr::GetInstance()->Get_IndexObject(_index)->Set_ObjIndex(pushIndex);

			dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(_index, CAN_MOVE);
			dynamic_cast<CBackGround*>(m_pBackGround)->Set_GridState(pushIndex, ON_OBJECT);
		}

		return true;
	}
	// 트랩이 있는지 판단
	else if (ON_TRAP == dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexBlock(_index))
	{
		--m_iHp;

		dynamic_cast<CBackGround*>(m_pBackGround)->Set_Vive(true);
		Create_Blood(dynamic_cast<CBackGround*>(m_pBackGround)->Find_IndexPos(_index));	
		bleeding = true;
		bleedingCount = 0.f;
		bloodColor = 70;
	}

	m_tFrame = { 0.f, 6.f, 2.f };
	m_wstrStateKey = L"Move";

	return false;
}

void CPlayer::ClearMotion()
{
	// Clear 프레임 1단계
	if (m_tFrame.fFrame <= 5.f)
		MoveFrame();
	// Clear 프레임 2~3단계
	else if (true == m_bCrush)
	{
		// Clear 프레임 2단계
		if (m_tFrame.fFrame <= 11.f)
			MoveFrame();
		// Clear 프레임 3단계 준비
		else
			m_fClearCount += 5.f * 0.5f * CTimeMgr::GetInstance()->Get_TimeDelta();

		// Clear 프레임 3단계
		if (m_fClearCount >= 3.f)
		{
			if (m_tFrame.fFrame >= 17.5f)
				m_tFrame.fFrame = 14.f;

			MoveFrame();
		}
	}
}

void CPlayer::Create_HitEffect(D3DXVECTOR3 _pos)
{
	CObj*	pEffect = new CHitEffect;
	pEffect->Initialize();

	switch (m_PreDir)
	{
	case DIR_LEFT:
		pEffect->Set_ObjKey(L"BigLeft");
		break;
	case DIR_RIGHT:
		pEffect->Set_ObjKey(L"BigRight");
		break;
	}

	pEffect->Set_Pos(_pos);

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pEffect);
}

void CPlayer::Create_MoveEffect(D3DXVECTOR3 _pos)
{
	CObj*	pEffect = new CMoveEffect;
	pEffect->Initialize();

	switch (moveCount)
	{
	case 0:
		pEffect->Set_ObjKey(L"MoveCase0");
		++moveCount;
		break;
	case 1:
		pEffect->Set_ObjKey(L"MoveCase1");
		++moveCount;
		break;
	case 2:
		pEffect->Set_ObjKey(L"MoveCase2");
		moveCount = 0;
		break;
	}

	pEffect->Set_Pos(_pos);

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pEffect);
}

void CPlayer::Create_Bone()
{
	CObj*	pEffect = new CBone;
	pEffect->Initialize();
	pEffect->Set_Pos(m_tInfo.vPos);

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pEffect);
}

void CPlayer::Create_Blood(D3DXVECTOR3 _pos)
{
	CObj*	pEffect = new CBloodEffect;
	pEffect->Initialize();

	switch (bloodCount)
	{
	case 0:
		pEffect->Set_ObjKey(L"Blood0");
		++bloodCount;
		break;
	case 1:
		pEffect->Set_ObjKey(L"Blood1");
		++bloodCount;
		break;
	case 2:
		pEffect->Set_ObjKey(L"Blood2");
		bloodCount = 0;
		break;
	}

	pEffect->Set_Pos(_pos - D3DXVECTOR3{10.f, 45.f, 0.f});

	CObjMgr::GetInstance()->Add_Object(CObjMgr::EFFECT, pEffect);
}

void CPlayer::Synchro_Scroll()
{
	// 스크롤 락
	if (m_tInfo.vPos.y >= 887)
		return;
	else if (m_tInfo.vPos.y < 0)
		return;

	// 위 스크롤
	if (m_tInfo.vPos.y + m_vScroll.y < 570)
		m_vScroll.y += 370.f * CTimeMgr::GetInstance()->Get_TimeDelta();
	
	// 아래 스크롤
	if (m_tInfo.vPos.y + m_vScroll.y > 550)
		m_vScroll.y -= 370.f * CTimeMgr::GetInstance()->Get_TimeDelta();
}
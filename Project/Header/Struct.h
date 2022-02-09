#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;

	D3DXMATRIX		matWorld;

}INFO;

typedef	struct tagTexture
{
	// �ؽ�ó �İ�ü
	LPDIRECT3DTEXTURE9		pTexture;

	// �̹��� ������ �����ϱ� ���� ����ü
	D3DXIMAGE_INFO			tImgInfo;

}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vSize;

	BYTE			byOption;	// ���� �߿��� Ÿ�� �ɼ��� ���� ��ֹ� ������ �� ����
	BYTE			byDrawID;	// �� �� Ÿ�� �̹����ΰ�


}TILE;

typedef struct tagUnitData
{

#ifndef _AFX
	wstring		strName;

#else
	CString		strName;
#endif

	int			iAttack;
	int			iHp;
	BYTE		byJobIndex;
	BYTE		byItem;

}UNITDATA;

typedef struct tagTexturePath
{
	wstring			wstrObjKey = L"";
	wstring			wstrStateKey = L"";
	wstring			wstrPath = L"";
	int				iCount = 0;

}IMGPATH;

typedef struct tagFrame
{
	tagFrame() {}
	tagFrame(float _fFrame, float _fMax)
	: fFrame(_fFrame), fMax(_fMax), fFrameSpeed(1.3f) {}
	tagFrame(float _fFrame, float _fMax, float _frameSpeed)
	: fFrame(_fFrame), fMax(_fMax), fFrameSpeed(_frameSpeed) {}
	
	float		fFrame;			// ���� �ִϸ��̼� �ε���
	float		fMax;			// �ִ� �ε���
	float		fFrameSpeed;	// FrameSpeed. ������ �ӵ�����

}FRAME;

typedef struct tagGridInfo
{
	float	Width;			// Grid ����
	float	Height;			// Grid ����
	float	fCX;			// Grid ���� X
	float	fCY;			// Grid ���� Y

	int		iStart_Index;		// i �ε��� ���� ���ٰ�
	int		jStart_Index;		// j �ε��� ���� ���ٰ�
	int		iEnd_Index;			// i �ε��� ������ ���ٰ�
	int		jEnd_Index;			// j �ε��� ������ ���ٰ�
} GRID_INFO;
//==============================================================================
// �^�C�g��     :   OpenGL�p�����_���[�N���X
// �t�@�C����   :   rendererGL.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/04/19
//==============================================================================

//==============================================================================
// �X�V����: -2016/04/19 ��������
//           �E����J�n
//           -2016/05/13
//           �E�����_���[����V�[���̏����𕪗�
//==============================================================================

//==============================================================================
// �C���N���[�h�K�[�h
//==============================================================================
#pragma once

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "renderer.h"
#include "materialGL.h"

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================
#pragma comment( lib , "opengl32.lib" )		// OpenGL�p
#pragma comment( lib , "glu32.lib" )		// OpenGL�p

//==============================================================================
// �O���錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================
#define GL_FVF_XYZ				0x002				// ���_�f�[�^( XYZ���W���p )
#define GL_FVF_NORMAL			0x010				// �@��
#define GL_FVF_DIFFUSE			0x040				// �f�B�t���[�Y���_�F
#define GL_FVF_TEX_MASK			0xf00				// �e�N�X�`�����p����p�}�X�N�r�b�g
#define GL_FVF_TEX1				0x100				// 1�Ԗڂ̃e�N�X�`��

// OpenGL1.3����}���`�e�N�X�`�������p�\�炵���̂ŁA����p�Ɏc���Ă���
//#define GL_FVF_TEX0				0x000				// 0�Ԗڂ̃e�N�X�`��
//#define GL_FVF_TEX2				0x200				// 2�Ԗڂ̃e�N�X�`��
//#define GL_FVF_TEX3				0x300				// 3�Ԗڂ̃e�N�X�`��
//#define GL_FVF_TEX4				0x400				// 4�Ԗڂ̃e�N�X�`��
//#define GL_FVF_TEX5				0x500				// 5�Ԗڂ̃e�N�X�`��
//#define GL_FVF_TEX6				0x600				// 6�Ԗڂ̃e�N�X�`��
//#define GL_FVF_TEX7				0x700				// 7�Ԗڂ̃e�N�X�`��
//#define GL_FVF_TEX8				0x800				// 8�Ԗڂ̃e�N�X�`��

#define GL_FVF_VERTEX_2D	( GL_FVF_XYZ | GL_FVF_DIFFUSE | GL_FVF_TEX1 )						// 2D�p���_�t�H�[�}�b�g
#define GL_FVF_VERTEX_3D	( GL_FVF_XYZ | GL_FVF_DIFFUSE | GL_FVF_TEX1 | GL_FVF_NORMAL )		// 3D�p���_�t�H�[�}�b�g

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �N���X�錾
//==============================================================================
class CRendererGL : public CRenderer
{
	//---------------------------------------------------------------
	// [ �����o�֐� ]
	//---------------------------------------------------------------
public:
	CRendererGL();														// �R���X�g���N�^
	~CRendererGL();														// �f�X�g���N�^

	bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow );		// ������
	void Uninit( void );												// �I��
	void Update( void );												// �X�V
	void Draw( void );													// �`��

	bool BeginScene( void );											// �`��J�n
	void EndScene( void );												// �`��I��

	bool SwapBuffer( void );											// �o�b�N�o�b�t�@����ւ�����

	bool CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff );	// ���_�o�b�t�@��������
	bool CreateTexture( char* pSrcFile , CTexture** ppTexture );		// �e�N�X�`����������

	bool CreateModel(													// ���f���f�[�^��������
		char* pFileName,
		CMaterialBuffer** ppMaterials,
		DWORD* pNumMaterials,
		CModel** ppModelMesh );

	bool SetStreamSource(												// ���_�o�b�t�@�[��ݒ肷��
		UINT streamNumber,
		CVertexBuffer* pStreamData,
		UINT offsetByte,
		UINT stride );

	bool SetIndices( CIndexBuffer* pIndexData );						// �C���f�b�N�X�o�b�t�@�[�ݒ�

	bool SetFVF( unsigned long FVF );									// ���_�t�H�[�}�b�g�ݒ�

	bool DrawPrimitive(													// �v���~�e�B�u�`��
		PRIMITIVE_TYPE primitiveType,
		UINT startVertex,
		UINT primitiveCount );

	bool DrawIndexedPrimitive(											// �C���f�b�N�X�t���v���~�e�B�u�`��
		PRIMITIVE_TYPE primitiveType ,
		int baseVertexIndex ,
		UINT minIndex ,
		UINT numVertices ,
		UINT startIndex ,
		UINT primitiveCount );

	void Set2DCamera( void );											// 2D�J�����ݒ�( ��قǃJ�����N���X�Ɉړ��\�� )
	void Set3DCamera( void );											// 3D�J�����ݒ�( ��قǃJ�����N���X�Ɉړ��\�� )

	void* GetDevice( void ){ return ( void* )m_glrc; }					// �f�o�C�X�擾����

	//------------------------------------------------------------------
	// [ �����o�ϐ� ]
	//------------------------------------------------------------------
private:
	HDC     m_hdc;								// �f�o�C�X�R���e�L�X�g
	HGLRC   m_glrc;								// OpenGL�p�����_�����O�R���e�L�X�g�n���h��
	HWND    m_hWnd;								// �E�B���h�E�n���h��

	LPVertexBuffer m_pCurVertexBuffer;			// ���ݐݒ肳��Ă��钸�_�o�b�t�@�[
	LPIndexBuffer  m_pCurIndexBuffer;			// ���ݐݒ肳��Ă���C���f�b�N�X�o�b�t�@�[

	ULONG m_curFVF;								// ���ݐݒ肳��Ă��钸�_�t�H�[�}�b�g
	UINT m_stride;								// ���_�o�b�t�@�[�̃I�t�Z�b�g( Byte�P�� )
};

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================

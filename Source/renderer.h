//==============================================================================
// �^�C�g��     :   �����_���[�N���X
// �t�@�C����   :   renderer.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/04/18
//==============================================================================

//==============================================================================
// �X�V����: -2016/04/18 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�K�[�h
//==============================================================================
#pragma once

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "main.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "materialBuffer.h"
#include "texture.h"
#include "model.h"
#include "vertex2D.h"
#include "vertex3D.h"

//==============================================================================
// �}�N����`
//==============================================================================
typedef enum
{							/* ==�����_���[���ʎq== */
	RENDERER_TYPE_DX = 0,		// DirectX
	RENDERER_TYPE_GL,			// OpenGL
	RENDERER_TYPE_MAX,			// ���ʎq����

} RENDERER_TYPE;

enum PRIMITIVE_TYPE
{							/* ==�v���~�e�B�u�`��^�C�v== */
	PT_POINT_LIST = 0,			// �_���X�g
	PT_LINE_LIST,				// �����X�g
	PT_LINE_STRIP,				// ���X�g���b�v
	PT_TRIANGLE_LIST,			// �O�p�`���X�g
	PT_TRIANGLE_STRIP,			// �O�p�`�X�g���b�v
	PT_TRIANGLE_FAN,			// �O�p�`�t�@��
	PT_MAX,						// ����
};

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �N���X�錾
//==============================================================================
class CRenderer
{
	/* ===�����o�֐�=== */
public:
	CRenderer(){};			// �R���X�g���N�^
	~CRenderer(){};			// �f�X�g���N�^

	virtual bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow ) = 0;			// ����������
	virtual void Uninit( void ) = 0;													// �I������
	virtual void Update( void ) = 0;													// �X�V����
	virtual void Draw( void ) = 0;														// �`�揈��

	virtual bool BeginScene( void ) = 0;												// �`��J�n
	virtual void EndScene( void ) = 0;													// �`��I��

	virtual bool SwapBuffer( void ) = 0;												// �o�b�N�o�b�t�@�[�̓���ւ�

	virtual bool CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff ) = 0;		// ���_�o�b�t�@��������
	virtual bool CreateTexture( char* pSrcFile , CTexture** ppTexture ) = 0;			// �e�N�X�`����������

	virtual bool CreateModel(															// ���f���f�[�^��������
		char* pFileName,
		CMaterialBuffer** ppMaterials,
		DWORD* pNumMaterials,
		CModel** ppModelMesh ) = 0;

	virtual bool SetStreamSource(														// ���_�o�b�t�@�[��ݒ肷��
		UINT streamNumber,
		CVertexBuffer* pStreamData,
		UINT offsetByte,
		UINT stride ) = 0;

	virtual bool SetIndices( CIndexBuffer* pIndexData ) = 0;							// �C���f�b�N�X�o�b�t�@�[�ݒ�

	virtual bool SetFVF( unsigned long FVF ) = 0;										// ���_�t�H�[�}�b�g�ݒ�

	virtual bool DrawPrimitive(															// �v���~�e�B�u�`��
		PRIMITIVE_TYPE primitiveType,
		UINT startVertex,
		UINT primitiveCount ) = 0;

	virtual bool DrawIndexedPrimitive(													// �C���f�b�N�X�t���v���~�e�B�u�`��
		PRIMITIVE_TYPE primitiveType,
		int baseVertexIndex,
		UINT minIndex,
		UINT numVertices,
		UINT startIndex,
		UINT primitiveCount ) = 0;

	virtual void* GetDevice( void ) = 0;												// �f�o�C�X�擾

	static CRenderer* Create( RENDERER_TYPE type );

	RENDERER_TYPE GetRendererType( void ){ return m_type; }		// ��������Ă��郌���_���[�^�C�v�̎擾

	/* ===�����o�ϐ�=== */
protected:
	RENDERER_TYPE m_type;			// ��������Ă��郌���_���[�̃^�C�v

};

typedef CRenderer* LPRenderer;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================

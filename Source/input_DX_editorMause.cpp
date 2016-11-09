//==============================================================================
// �^�C�g��     :   DirectX�p�}�E�X���͏���
// �t�@�C����   :   input.DX.mause.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/03
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/03 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "input_DX_editorMause.h"
#include "debugProc.h"

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================

//==============================================================================
// �O���[�o���錾
//==============================================================================

//==============================================================================
// �ÓI�ϐ�
//==============================================================================


//==============================================================================
// �֐��� : CInputDXMause()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CInputEditorMause::CInputEditorMause()
{
}

//==============================================================================
// �֐��� : ~CInputDXMause()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CInputEditorMause::~CInputEditorMause()
{

}

//==============================================================================
// �֐��� : void Ray( D3DXVECTOR3* pNear , D3DXVECTOR3* pFar , D3DXVECTOR3* pDir )
// ����   : D3DXVECTOR3* pNear : �j�A�l�i�[��
//          D3DXVECTOR3* pFar  : �t�@�[�l�i�[��
//          D3DXVECTOR3* pDir  : ���C�����x�N�g���i�[��
// �߂�l : void
// ����   : ���C���΂�����
//==============================================================================
void CInputEditorMause::Ray( D3DXVECTOR3* pNear , D3DXVECTOR3* pFar , D3DXVECTOR3* pDir )
{
	// �p�����[�^�Z�o
	//D3DXVECTOR3 nearPos;
	//D3DXVECTOR3 farPos;
	//D3DXVECTOR3 ray;
	//D3DXVECTOR3 rayDir;
	//
	//CCameraGL* pCamera = GetManager()->GetCamera();
	//
	//D3DXMATRIX mtxProj = pCamera->GetMtxProj();
	//D3DXMATRIX mtxView = pCamera->GetMtxView();
	//
	//nearPos = GetPosToWorld( mtxProj , mtxView , 0.0f );
	//farPos  = GetPosToWorld( mtxProj , mtxView , 1.0f );
	//
	//ray = farPos - nearPos;
	//D3DXVec3Normalize( &rayDir , &ray );
	//
	//// �p�����[�^�i�[
	//if( pNear != NULL ) *pNear = nearPos;
	//if( pFar != NULL ) *pFar = farPos;
	//if( pDir != NULL ) *pDir = rayDir;

}

//==============================================================================
// �֐��� : bool TriangleIntersect( D3DXVECTOR3 Orig , D3DXVECTOR3 dir , D3DXVECTOR3 v0 , D3DXVECTOR3 v1 , D3DXVECTOR3 v2 , float *pRetT , float *pRetU , float *pRetV )
// ����   : 
// �߂�l : bool�^
// ����   : �O�p�`�̓����蔻�菈��
//==============================================================================
bool CInputEditorMause::TriangleIntersect( D3DXVECTOR3 Orig , D3DXVECTOR3 dir , D3DXVECTOR3 v0 , D3DXVECTOR3 v1 , D3DXVECTOR3 v2 , float *pRetT , float *pRetU , float *pRetV )
{
	D3DXVECTOR3 e1 , e2 , pvec , tvec , qvec;
	float det;
	float t , u , v;
	float inv_det;

	D3DXVec3Subtract( &e1 , &v1 , &v0 );
	D3DXVec3Subtract( &e2 , &v2 , &v0 );

	D3DXVec3Cross( &pvec , &dir , &e2 );
	det = D3DXVec3Dot( &e1 , &pvec );

	if( det > ( 1e-3 ) ) {

		D3DXVec3Subtract( &tvec , &Orig , &v0 );
		u = D3DXVec3Dot( &tvec , &pvec );
		if( u < 0.0f || u > det ) return false;

		D3DXVec3Cross( &qvec , &tvec , &e1 );

		v = D3DXVec3Dot( &dir , &qvec );
		if( v < 0.0 || u + v > det ) return false;
	}
	else if( det < -( 1e-3 ) ) {
		D3DXVec3Subtract( &tvec , &Orig , &v0 );

		u = D3DXVec3Dot( &tvec , &pvec );
		if( u > 0.0 || u < det ) return false;

		D3DXVec3Cross( &qvec , &tvec , &e1 );

		v = D3DXVec3Dot( &dir , &qvec );
		if( v > 0.0 || u + v < det ) return false;

	}
	else {
		return false;
	}

	inv_det = 1.0f / det;

	t = D3DXVec3Dot( &e2 , &qvec );
	t *= inv_det;
	u *= inv_det;
	v *= inv_det;

	if( pRetT ) *pRetT = t;
	if( pRetU ) *pRetU = u;
	if( pRetV ) *pRetV = v;

	return true;    //hit!!
}

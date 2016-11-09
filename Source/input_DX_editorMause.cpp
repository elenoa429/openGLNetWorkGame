//==============================================================================
// タイトル     :   DirectX用マウス入力処理
// ファイル名   :   input.DX.mause.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/03
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/03 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "input_DX_editorMause.h"
#include "debugProc.h"

//==============================================================================
// 列挙型宣言
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// プロトタイプ宣言
//==============================================================================

//==============================================================================
// グローバル宣言
//==============================================================================

//==============================================================================
// 静的変数
//==============================================================================


//==============================================================================
// 関数名 : CInputDXMause()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CInputEditorMause::CInputEditorMause()
{
}

//==============================================================================
// 関数名 : ~CInputDXMause()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CInputEditorMause::~CInputEditorMause()
{

}

//==============================================================================
// 関数名 : void Ray( D3DXVECTOR3* pNear , D3DXVECTOR3* pFar , D3DXVECTOR3* pDir )
// 引数   : D3DXVECTOR3* pNear : ニア値格納先
//          D3DXVECTOR3* pFar  : ファー値格納先
//          D3DXVECTOR3* pDir  : レイ方向ベクトル格納先
// 戻り値 : void
// 説明   : レイを飛ばす処理
//==============================================================================
void CInputEditorMause::Ray( D3DXVECTOR3* pNear , D3DXVECTOR3* pFar , D3DXVECTOR3* pDir )
{
	// パラメータ算出
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
	//// パラメータ格納
	//if( pNear != NULL ) *pNear = nearPos;
	//if( pFar != NULL ) *pFar = farPos;
	//if( pDir != NULL ) *pDir = rayDir;

}

//==============================================================================
// 関数名 : bool TriangleIntersect( D3DXVECTOR3 Orig , D3DXVECTOR3 dir , D3DXVECTOR3 v0 , D3DXVECTOR3 v1 , D3DXVECTOR3 v2 , float *pRetT , float *pRetU , float *pRetV )
// 引数   : 
// 戻り値 : bool型
// 説明   : 三角形の当たり判定処理
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

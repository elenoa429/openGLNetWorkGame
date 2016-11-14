//==============================================================================
// タイトル     :   モーション編集用モデル
// ファイル名   :   editorModel.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/09/06
//==============================================================================

//==============================================================================
// 更新履歴: -2016/09/06 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "editorModel.h"
#include "main.h"
#include <vector>

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================

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
// 関数名 : CMotionEditModel()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CMotionEditModel::CMotionEditModel()
{
	m_pos           = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot           = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_pModelManager = NULL;
	m_editModeIdx   = 0;

	m_pMotion       = NULL;

	MatrixIdentity( &m_mtxWorld );
}

//==============================================================================
// 関数名 : ~CMotionEditModel()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CMotionEditModel::~CMotionEditModel()
{

}

//==============================================================================
// 関数名 : CMotionEditModel* Create( void )
// 引数   : void
// 戻り値 : CMotionEditModel*型
// 説明   : 生成処理
//==============================================================================
CMotionEditModel* CMotionEditModel::Create( void )
{
	CMotionEditModel* newInstance = new CMotionEditModel;

	if( newInstance->Init() == false )
	{
		newInstance->Release();
		newInstance = NULL;
	}

	return newInstance;
}

//==============================================================================
// 関数名 : bool Init( void )
// 引数   : void
// 戻り値 : void
// 説明   : 初期化処理
//==============================================================================
bool CMotionEditModel::Init( void )
{
	// モデルワーク生成処理
	//m_pModelManager = CParentModelManagerGL::Create();
	//
	//if( m_pModelManager == NULL )
	//{
	//	return false;
	//}

	// モーション生成
	//m_pMotion = CMotionGL::Create( "data\\ANIMATION\\miku_01_01.anm" );
	//
	//if( m_pMotion == NULL )
	//{
	//	return false;
	//}

	return true;
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CMotionEditModel::Uninit( void )
{
	// モデル処理の解放
	if( m_pModelManager != NULL )
	{
		m_pModelManager->Release();
		m_pModelManager = NULL;
	}

	// モーション処理解放
	if( m_pMotion != NULL )
	{
		m_pMotion->Release();
		m_pMotion = NULL;
	}
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CMotionEditModel::Update( void )
{
	//---------------------------------------------------
	// [ キー入力状況取得 ]
	//---------------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isMoveForward = false;
	bool isMoveBack    = false;
	bool isMoveLeft    = false;
	bool isMoveRight   = false;
	bool isMoveUp      = false;
	bool isMoveDown    = false;
	bool isRotLeft     = false;
	bool isRotRight    = false;

	if( pInput != NULL )
	{
		isMoveForward = pInput->GetPress( DIK_W );
		isMoveBack    = pInput->GetPress( DIK_S );
		isMoveLeft    = pInput->GetPress( DIK_A );
		isMoveRight   = pInput->GetPress( DIK_D );
		isMoveUp      = pInput->GetPress( DIK_Q );
		isMoveDown    = pInput->GetPress( DIK_E );
		isRotLeft     = pInput->GetPress( DIK_Z );
		isRotRight    = pInput->GetPress( DIK_C );
	}

	//---------------------------------------------------
	// [ 移動処理 ]
	//---------------------------------------------------
	if( isMoveForward )		m_pos.z -= 1.0f;
	if( isMoveBack )		m_pos.z += 1.0f;
	if( isMoveLeft )		m_pos.x -= 1.0f;
	if( isMoveRight )		m_pos.x += 1.0f;
	if( isMoveUp )			m_pos.y += 1.0f;
	if( isMoveDown )		m_pos.y -= 1.0f;
	if( isRotLeft )			m_rot.y -= PI * 0.01f;
	if( isRotRight )		m_rot.y += PI * 0.01f;

	//---------------------------------------------------
	// [ モーション処理 ]
	//---------------------------------------------------
	//m_pMotion->Update();
	//m_pMotion->SetMotionData( m_pModelManager );
	//
	//m_pModelManager->Update();

}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CMotionEditModel::Draw( void )
{
	// ----------------------------------------------------------------------
	// [ ワールドマトリックスの生成処理 ]
	// ----------------------------------------------------------------------
	MATRIX mtxRot , mtxTrans;													// 行列用ワーク
	MatrixIdentity( &m_mtxWorld );												// 行列初期化

	MatrixRotationYawPitchRoll( &mtxRot , m_rot.y , m_rot.x , m_rot.z );		// 回転の行列を算出
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxRot );						// 回転行列の合成

	MatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );				// 位置の行列を算出
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxTrans );					// 位置行列の合成

	// モデルの描画
	//m_pModelManager->Draw( &m_mtxWorld );
}

//==============================================================================
// 関数名 : void EditIdx( void )
// 引数   : void
// 戻り値 : void
// 説明   : インデックス編集処理
//==============================================================================
void CMotionEditModel::EditIdx( void )
{
	// ----------------------------------------------------------------------
	// [ キー入力状況の取得 ]
	// ----------------------------------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isMoveIdxUp = false;
	bool isMoveIdxDown = false;

	if( pInput != NULL )
	{
		isMoveIdxUp = pInput->GetTrigger( DIK_UP );
		isMoveIdxDown = pInput->GetTrigger( DIK_DOWN );
	}

	// ----------------------------------------------------------------------
	// [ モデルインデックス操作 ]
	// ----------------------------------------------------------------------
	if( isMoveIdxUp )
	{
		m_editModeIdx--;

		if( m_editModeIdx < 0 )
		{
			m_editModeIdx = 0;
		}
	}

	if( isMoveIdxDown )
	{
		m_editModeIdx++;

		if( m_editModeIdx >= m_pModelManager->GetModelListSize() )
		{
			m_editModeIdx = ( m_pModelManager->GetModelListSize() - 1 );
		}
	}
}

//==============================================================================
// 関数名 : void EditPos( void )
// 引数   : void
// 戻り値 : void
// 説明   : モデルローカル座標編集処理
//==============================================================================
void CMotionEditModel::EditPos( void )
{
	// ----------------------------------------------------------------------
	// [ キー入力状況の取得 ]
	// ----------------------------------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isMovePosXUp = false;
	bool isMovePosXDown = false;
	bool isMovePosXReset = false;
	bool isMovePosYUp = false;
	bool isMovePosYDown = false;
	bool isMovePosYReset = false;
	bool isMovePosZUp = false;
	bool isMovePosZDown = false;
	bool isMovePosZReset = false;

	if( pInput != NULL )
	{
		//isMovePosXUp    = pInput->GetRepeat();
		//isMovePosXDown  = pInput->GetRepeat();
		//isMovePosXReset = pInput->GetTrigger();
		//isMovePosYUp    = pInput->GetRepeat();
		//isMovePosYDown  = pInput->GetRepeat();
		//isMovePosXReset = pInput->GetTrigger();
		//isMovePosZUp    = pInput->GetRepeat();
		//isMovePosZDown  = pInput->GetRepeat();
		//isMovePosXReset = pInput->GetTrigger();
	}

	// ----------------------------------------------------------------------
	// [ モデルローカル位置操作 ]
	// ----------------------------------------------------------------------

}

//==============================================================================
// 関数名 : void EditRot( void )
// 引数   : void
// 戻り値 : void
// 説明   : モデルローカル角度編集処理
//==============================================================================
void CMotionEditModel::EditRot( void )
{

}

//==============================================================================
// 関数名 : void ViewImfModel( void )
// 引数   : void
// 戻り値 : void
// 説明   : モデル情報表示処理
//==============================================================================
void CMotionEditModel::ViewImfModel( void )
{
	// ----------------------------------------------------------------------
	// [ 情報表示 ]
	// ----------------------------------------------------------------------
	//CDebugProc::Print( "[ MODEL ]\n" );
	//CDebugProc::Print( "Index : %d\n" , m_editModeIdx );

	//// モデル情報
	//CParentModelDX* pModel = m_pModelManager->GetModelData( m_editModeIdx );

	//if( pModel != NULL )
	//{
	//	D3DXVECTOR3 posData = pModel->GetPos();
	//	D3DXVECTOR3 rotData = pModel->GetRot();
	//	char* filePath = pModel->GetModelFilePath();

	//	if( filePath != NULL )
	//	{
	//		CDebugProc::Print( "Path  : %s\n" , filePath );
	//	}

	//	CDebugProc::Print( "Pos   : ( %3.3f ; %3.3f ; %3.3f )\n" , posData.x , posData.y , posData.z );
	//	CDebugProc::Print( "Rot   : ( %3.3f ; %3.3f ; %3.3f )\n" , rotData.x , rotData.y , rotData.z );
	//}
}

//==============================================================================
// 関数名 : void ViewImfMotion( void )
// 引数   : void
// 戻り値 : void
// 説明   : モーション情報表示処理
//==============================================================================
void CMotionEditModel::ViewImfMotion( void )
{
	// ----------------------------------------------------------------------
	// [ 情報表示 ]
	// ----------------------------------------------------------------------
	//CDebugProc::Print( "[ MOTION ]\n" );
}

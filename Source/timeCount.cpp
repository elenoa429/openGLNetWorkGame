//==============================================================================
// タイトル     :   時間計測・表示クラス
// ファイル名   :   timeCount.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/20
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/20 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "timeCount.h"

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
// 関数名 : CTimeCount()
// 引数   : void
// 戻り値 : void
// 説明   : コンストラクタ
//==============================================================================
CTimeCount::CTimeCount() : CScene( PRIORITY_TYPE_UI , OBJ_TYPE_UI )
{
	m_pos  = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot  = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_size = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_col  = COLOR_F32( 0.0f , 0.0f , 0.0f , 0.0f );

	m_pTexture         = NULL;
	m_ppNumber         = NULL;
	m_numPlace         = 0;
	m_time             = 0;
	m_timeCnt          = 0;
	m_timeDelay        = 0;
	m_isOutputLeftZero = true;
}

//==============================================================================
// 関数名 : ~CTimeCount()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CTimeCount::~CTimeCount()
{

}

//==============================================================================
// 関数名 : CTimeCount* Create( int numPlace , VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , char* texPath )
// 引数   : int numPlace     : 表示桁数
//          VECTOR3 pos  : 位置
//          VECTOR3 size : サイズ
//          int texDivW      : テクスチャ分割数( 横 )
//          int texDivH      : テクスチャ分割数( 縦 )
//          char* texPath    : テクスチャファイルパス
// 戻り値 : bool型 : 処理結果
// 説明   : 生成処理
//==============================================================================
CTimeCount* CTimeCount::Create( int numPlace , VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , char* texPath )
{
	CTimeCount* newInstance;
	newInstance = new CTimeCount;

	if( newInstance->Init( numPlace , pos , size , texDivW , texDivH , texPath ) == false )
	{
		newInstance->Release();
		newInstance = NULL;
	}

	return newInstance;
}

//==============================================================================
// 関数名 : bool Init( int numPlace , VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , char* texPath )
// 引数   : int numPlace     : 表示桁数
//          VECTOR3 pos  : 位置
//          VECTOR3 size : サイズ
//          int texDivW      : テクスチャ分割数( 横 )
//          int texDivH      : テクスチャ分割数( 縦 )
//          char* texPath    : テクスチャファイルパス
// 戻り値 : bool型 : 処理結果
// 説明   : 初期化処理
//==============================================================================
bool CTimeCount::Init( int numPlace , VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , char* texPath )
{
	// 座標情報の初期化
	m_pos = pos;
	m_rot = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_size = size;

	VECTOR3 halfSize = VECTOR3( m_size.x * 0.5f , m_size.y * 0.5f , m_size.z * 0.5f );

	// レンダラー取得
	CRenderer* pRenderer = GetManager()->GetRenderer();		// レンダラー処理を取得

	// テクスチャ読み込み処理
	pRenderer->CreateTexture( texPath , &m_pTexture );

	// 数字表示クラスの生成
	if( numPlace <= 0 )
	{
		return false;		// 数字が間違っているので、処理失敗
	}

	VECTOR3 setPos = pos;
	VECTOR3 setSize = size;

	setSize.x /= numPlace;							// 横に表示したいのでこうする。他の表示方法にしたいなら、個別設定で。
	setPos.x -= size.x * 0.5f;						// 初期位置を左端にセット

	m_ppNumber = new CNumber2D*[ numPlace ];		// 桁数だけワーク生成

	for( int i = 0 ; i < numPlace ; i++ )
	{
		m_ppNumber[ i ] = CNumber2D::Create( setPos , setSize , texDivW , texDivH , m_pTexture );		// 生成したデータ取得
		setPos.x += setSize.x;						// 右にずらしていく
	}

	m_numPlace = numPlace;

	return true;	// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CTimeCount::Uninit( void )
{
	// テクスチャの解放処理
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// 数字処理の解放
	if( m_ppNumber != NULL )
	{
		for( int i = 0 ; i < m_numPlace ; i++ )
		{
			if( m_ppNumber[ i ] != NULL )
			{
				m_ppNumber[ i ]->Release();
				m_ppNumber[ i ] = NULL;
			}
		}

		delete[] m_ppNumber;
		m_ppNumber = NULL;
	}
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CTimeCount::Update( void )
{
	//-----------------------------------------------
	// [ 時間計測 ]
	//-----------------------------------------------
	if( m_timeCnt == m_timeDelay )
	{
		m_time--;

		if( m_time < 0 ) m_time++;

		CTimeCount::PrintTime();

		m_timeCnt = 0;
	}

	m_timeCnt++;

	//-----------------------------------------------
	// [ 数字の更新処理 ]
	//-----------------------------------------------
	for( int i = 0 ; i < m_numPlace ; i++ )
	{
		if( m_ppNumber[ i ] != NULL )
		{
			m_ppNumber[ i ]->Update();
		}
	}
}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CTimeCount::Draw( void )
{
	bool output = m_isOutputLeftZero ? true : false;		// 有効桁が出現したか判定

	for( int i = 0 ; i < m_numPlace ; i++ )
	{
		if( m_ppNumber[ i ]->GetNum() != 0 || i == ( m_numPlace - 1 ) )
		{
			// 有効桁出現時or下一桁に到達により表示する
			output = true;
		}

		if( output )
		{
			if( m_ppNumber[ i ] != NULL )
			{
				m_ppNumber[ i ]->Draw();
			}
		}
	}
}

//==============================================================================
// 関数名 : void SetTime( int time , int delay )
// 引数   : int time  : 表示したい時刻
//          int delay : 時刻をずらすまでの時間
// 戻り値 : void
// 説明   : 時刻設定処理
//==============================================================================
void CTimeCount::SetTime( int time , int delay )
{
	m_time      = time;
	m_timeCnt   = 0;
	m_timeDelay = delay;

	// 時間の出力
	CTimeCount::PrintTime();
}


//==============================================================================
// 関数名 : void SetColor( COLOR_F32 col );
// 引数   : COLOR_F32 col : 設定色
// 戻り値 : void
// 説明   : 色設定処理
//==============================================================================
void CTimeCount::SetColor( COLOR_F32 col )
{
	m_col = col;

	for( int i = 0 ; i < m_numPlace ; i++ )
	{
		if( m_ppNumber[ i ] != NULL )
		{
			m_ppNumber[ i ]->SetCol( col );
		}
	}
}

//==============================================================================
// 関数名 : void PrintTime( void )
// 引数   : void
// 戻り値 : void
// 説明   : 時間を数字処理に出力する処理
//==============================================================================
void CTimeCount::PrintTime( void )
{
	int value = m_time;												// 入力数値

	if( value >= 0 )												// マイナス値は動作保証外のため処理しない
	{
		for( int i = m_numPlace - 1 ; i >= 0 ; i-- )				// 下位桁から入れ込む
		{
			int placeValue = value % 10;							// 一桁の値を取り出す

			if( m_ppNumber[ i ] != NULL )
			{
				m_ppNumber[ i ]->SetNum( placeValue );				// 一桁の値を設定
			}

			value /= 10;											// 桁下げ
		}
	}
}

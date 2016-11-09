//==============================================================================
// タイトル     :   DirectX用レンダラークラス
// ファイル名   :   rendererDX.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/04/18
//==============================================================================

//==============================================================================
// 更新履歴: -2016/04/18 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "rendererDX.h"
#include "sceneDX.h"

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
// 関数名 : CRendererDX()
// 引数   : void
// 戻り値 : void
// 説明   : コンストラクタ
//==============================================================================
CRendererDX::CRendererDX()
{
	m_pD3D       = NULL;
	m_pD3DDevice = NULL;
	m_pScene     = NULL;

	m_type       = RENDERER_TYPE_DX;	// DirectXで生成
}

//==============================================================================
// 関数名 : ~CRendererDX()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CRendererDX::~CRendererDX()
{
}

//==============================================================================
// 関数名 : bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
// 引数   : void
// 戻り値 : bool型 : 処理結果
// 説明   : 初期化処理
//==============================================================================
bool CRendererDX::Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
{
	/* ===変数の宣言・初期化=== */
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE        d3ddm;

	/* ===Direct3Dオブジェクトの生成=== */
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	if( m_pD3D == NULL )
	{
		return false;		// 生成失敗
	}
	
	/* ===ディスプレイモードの取得=== */
	if( FAILED( m_pD3D -> GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &d3ddm ) ) )
	{
		return false;		// 取得失敗
	}

	/* ===初期化設定=== */
	ZeroMemory( &d3dpp , sizeof( d3dpp ) );							// メモリ０埋め

																	/* ===DirectXの諸設定=== */
	d3dpp.BackBufferWidth            = ( UINT )SCREEN_WIDTH;			// | 画面幅
	d3dpp.BackBufferHeight           = ( UINT )SCREEN_HEIGHT;			// | 画面高さ
	d3dpp.BackBufferFormat           = d3ddm.Format;					// | バックバッファフォーマット
	d3dpp.BackBufferCount            = 1;								// | バックバッファ数
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;			// | バッファ切り替えタイミング
	d3dpp.EnableAutoDepthStencil     = TRUE;							// | 奥行判定
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D16;						// | デプスバッファの使用ビット数
	d3dpp.Windowed                   = bWindow;							// | フルスクリーン判定
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// | バッファの同期タイミング
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// | バッファの同期タイミング

	/* ===Direct3Dデバイスの生成=== */
	if( FAILED( m_pD3D -> CreateDevice(									/* ===生成一回目=== */
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,
							hWnd,
							D3DCREATE_HARDWARE_VERTEXPROCESSING,
							&d3dpp,
							&m_pD3DDevice ) )
	){
		if( FAILED( m_pD3D -> CreateDevice(							/* ===生成二回目=== */
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,
							hWnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&d3dpp,
							&m_pD3DDevice ) )
		){
			if( FAILED( m_pD3D -> CreateDevice(						/* ===生成三回目=== */
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_REF,
							hWnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&d3dpp,
							&m_pD3DDevice ) )
			){
				return false;	// 生成失敗
			}
		}
	}

	/* ==レンダーステートの初期設定== */
	m_pD3DDevice -> SetRenderState( D3DRS_CULLMODE , D3DCULL_CCW );					// カリング設定
	m_pD3DDevice -> SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );				// アルファブレンド設定
	m_pD3DDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );			// ソース側の設定
	m_pD3DDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );		// デスト側の設定

	/* ===サンプラーステートの初期設定=== */
	m_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_MINFILTER , D3DTEXF_LINEAR );		// テクスチャ縮小時の補間設定
	m_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_MAGFILTER , D3DTEXF_LINEAR );		// テクスチャ拡大時の補間設定
	m_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_ADDRESSU , D3DTADDRESS_WRAP );		// テクスチャＵ座標の設定
	m_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_ADDRESSV , D3DTADDRESS_WRAP );		// テクスチャＶ座標の設定

	/* ===テクスチャステージステートの設定=== */
	m_pD3DDevice -> SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_MODULATE );	// アルファ値合成設定
	m_pD3DDevice -> SetTextureStageState( 0 , D3DTSS_ALPHAARG1 , D3DTA_TEXTURE );	// 合成時の引数設定( 1 )
	m_pD3DDevice -> SetTextureStageState( 0 , D3DTSS_ALPHAARG2 , D3DTA_CURRENT );	// 合成時の引数設定( 2 )

	//---------------------------------------------
	// [ その他の処理 ]
	//---------------------------------------------
	m_pScene = new CSceneDX;

	if( m_pScene -> Init() == false )
	{
		return false;		// 処理失敗
	}

	return true;																	// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CRendererDX::Uninit( void )
{
	/* ===デバイスの解放=== */
	if( m_pD3DDevice != NULL )
	{
		m_pD3DDevice -> Release();
		m_pD3DDevice = NULL;
	}

	if( m_pD3D != NULL )
	{
		m_pD3D -> Release();
		m_pD3D = NULL;
	}

	/* ===その他の解放処理=== */
	if( m_pScene != NULL )
	{
		m_pScene -> Uninit();
		delete m_pScene;
		m_pScene = NULL;
	}

}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CRendererDX::Update( void )
{
	m_pScene -> Update();
}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CRendererDX::Draw( void )
{
	m_pScene -> Draw();
}

//==============================================================================
// 関数名 : bool BeginScene( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画開始処理
//==============================================================================
bool CRendererDX::BeginScene( void )
{
	/* ===画面の初期化=== */
	m_pD3DDevice -> Clear(								/* ===画面クリア=== */
		0,													// | 固定
		NULL,												// | 固定
		( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ),				// | クリア方式
		D3DCOLOR_RGBA( 0 , 0 , 0 , 0 ),						// | 画面初期化色
		1.0f,												// | 奥行？
		0 );												// | ステンシル？

	/* ===描画処理=== */
	HRESULT hr = m_pD3DDevice -> BeginScene();			// 描画開始処理
	return SUCCEEDED( hr ) ? true : false;				// 処理結果の返却
}

//==============================================================================
// 関数名 : void EndScene( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画終了処理
//==============================================================================
void CRendererDX::EndScene( void )
{
	m_pD3DDevice -> EndScene();						// 描画終了
}

//==============================================================================
// 関数名 : bool SwapBuffer( void )
// 引数   : void
// 戻り値 : bool型 : 処理結果
// 説明   : バックバッファーのスワップ処理
//==============================================================================
bool CRendererDX::SwapBuffer( void )
{
	HRESULT hr = m_pD3DDevice -> Present( NULL , NULL , NULL , NULL );		// バッファの切り替え
	return SUCCEEDED( hr ) ? true : false;									// 処理結果の返却
}

//==============================================================================
// 関数名 : bool CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff )
// 引数   : void
// 戻り値 : bool型 : 処理結果
// 説明   : 頂点バッファー生成処理
//==============================================================================
bool CRendererDX::CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff )
{
	HRESULT hr = m_pD3DDevice -> CreateVertexBuffer(					/* ===バッファ生成設定=== */
							sizeof( VERTEX_2D ) * size,						// | 確保するバッファーサイズ( Byte単位 )
							D3DUSAGE_WRITEONLY,								// | 使用方法
							FVF_VERTEX_2D,									// | 頂点フォーマット
							D3DPOOL_MANAGED,								// | リソースのバッファーの保持設定
							( LPDIRECT3DVERTEXBUFFER9* )ppVtxBuff,			// | 格納先アドレス
							NULL );											// | 影のハンドル？

	return SUCCEEDED( hr ) ? true : false;									// 処理結果の返却
}

//==============================================================================
// 関数名 : bool CreateTexture( char* pSrcFile , void** ppTexture )
// 引数   : void
// 戻り値 : bool型 : 処理結果
// 説明   : 頂点バッファー生成処理
//==============================================================================
bool CRendererDX::CreateTexture( char* pSrcFile , void** ppTexture )
{
	HRESULT hr = D3DXCreateTextureFromFile(					/* ===テクスチャ読み込み=== */
					m_pD3DDevice,								// デバイスポインタ
					pSrcFile,									// 読み込むテクスチャファイル名
					( LPDIRECT3DTEXTURE9* )ppTexture );			// テクスチャポインタ

	return SUCCEEDED( hr ) ? true : false;					// 処理結果の返却
}

//==============================================================================
// 関数名 : CRendererDX()
// 引数   : void
// 戻り値 : void
// 説明   : コンストラクタ
//==============================================================================

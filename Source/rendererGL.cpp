//==============================================================================
// タイトル     :   OpenGLX用レンダラークラス
// ファイル名   :   rendererGL.cpp
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
#include "rendererGL.h"
#include "texture.h"
#include "loader.h"
#include "vertexBufferGL.h"
#include "indexBufferGL.h"

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
// 関数名 : CRendererGL()
// 引数   : void
// 戻り値 : void
// 説明   : コンストラクタ
//==============================================================================
CRendererGL::CRendererGL()
{
	m_hdc    = NULL;
	m_glrc   = NULL;
	m_hWnd   = NULL;

	m_pCurVertexBuffer = NULL;
	m_curFVF = 0;
	m_stride = 0;

	m_type   = RENDERER_TYPE_GL;	// OpenGLで生成
}

//==============================================================================
// 関数名 : ~CRendererGL()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CRendererGL::~CRendererGL()
{
}

//==============================================================================
// 関数名 : bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
// 引数   : void
// 戻り値 : bool型 : 処理結果
// 説明   : 初期化処理
//==============================================================================
bool CRendererGL::Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
{
	/* ===デバイスコンテキストの取得=== */
	m_hWnd = hWnd;										// ウィンドウハンドルの保持
	m_hdc = GetDC( hWnd );								// デバイスコンテキストを取得

	/* ===ピクセルフォーマットの設定=== */
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,		//Flags
		PFD_TYPE_RGBA,		//The kind of framebuffer. RGBA or palette.
		32,					//Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,					//Number of bits for the depthbuffer
		8,					//Number of bits for the stencilbuffer
		0,					//Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int format = ChoosePixelFormat( m_hdc , &pfd );

	if( format == 0 )
	{
		ReleaseDC( hWnd, m_hdc );
		return false;
	}

	if( !SetPixelFormat( m_hdc , format , &pfd ) )
	{
		ReleaseDC( hWnd, m_hdc );
		return false;
	}

	/* ===レンダリングコンテキスト作成=== */
	m_glrc = wglCreateContext( m_hdc );

	if( !m_glrc )
	{
		ReleaseDC( hWnd, m_hdc );
		return false;
	}

	wglMakeCurrent( m_hdc, m_glrc );

	/* ===全初期化処理終了=== */
	return true;																	// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CRendererGL::Uninit( void )
{
	/* ===デバイスの解放=== */
	wglMakeCurrent( NULL , NULL );		// カレントコンテキストを無効にする
	wglDeleteContext( m_glrc );			// カレントコンテキストを削除
	ReleaseDC( m_hWnd , m_hdc );		// デバイスコンテキストの解放

	/* ===その他の解放処理=== */
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CRendererGL::Update( void )
{
}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CRendererGL::Draw( void )
{
}

//==============================================================================
// 関数名 : bool BeginScene( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画開始処理
//==============================================================================
bool CRendererGL::BeginScene( void )
{
	/* ===画面の初期化=== */
	wglMakeCurrent( m_hdc , m_glrc );							// 
	glClearColor( 0.6f , 0.6f , 1.0f , 1.0f );					// 画面クリア
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		// バックバッファークリア
	glClearDepth( 1.0f );										// デプスクリア？

	/* ===描画処理=== */
	return true;				// 処理結果の返却
}

//==============================================================================
// 関数名 : void EndScene( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画終了処理
//==============================================================================
void CRendererGL::EndScene( void )
{
	
}

//==============================================================================
// 関数名 : bool SwapBuffer( void )
// 引数   : void
// 戻り値 : bool型 : 処理結果
// 説明   : バックバッファーのスワップ処理
//==============================================================================
bool CRendererGL::SwapBuffer( void )
{
	glFlush();							// 
	SwapBuffers( m_hdc );				// バッファの切り替え
	wglMakeCurrent( NULL , NULL );		// 
	return true;						// 処理結果の返却
}

//==============================================================================
// 関数名 : bool CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff )
// 引数   : void
// 戻り値 : bool型 : 処理結果
// 説明   : 頂点バッファー生成処理
//==============================================================================
bool CRendererGL::CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff )
{
	CVertexBufferGL* pVtxBuf = NULL;

	// 生成処理
	pVtxBuf = new CVertexBufferGL;

	char* pBuff = new char[ size ];					// 1Byteの配列をサイズ分生成

	pVtxBuf->SetPrivateData( pBuff , size );		// データ設定

	*ppVtxBuff = pVtxBuf;							// ポインターセット

	return true;									// 処理結果の返却
}

//==============================================================================
// 関数名 : bool CreateTexture( char* pSrcFile , CTexture** ppTexture )
// 引数   : char* pSrcFile       : ファイル名
//          CTexture** ppTexture : テクスチャ処理へのダブルポインタ
// 戻り値 : bool型               : 処理結果
// 説明   : テクスチャ生成処理
//==============================================================================
bool CRendererGL::CreateTexture( char* pSrcFile , CTexture** ppTexture )
{
	wglMakeCurrent( m_hdc , m_glrc );

	CLoader* pLoader = new CLoader;		// ローダーの生成
	bool bResult = false;				// 処理結果用

	bResult = pLoader->TextuerLoad( pSrcFile , ppTexture );
	delete pLoader;
	pLoader = NULL;

	wglMakeCurrent( NULL , NULL );

	return bResult;						// 処理結果の返却
}

//==============================================================================
// 関数名 : bool CreateModel( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
// 引数   : char* pFileName               : ファイル名
//          CMaterialBuffer** ppMaterials : マテリアル用バッファーへのダブルポインタ
//          DWORD* pNumMaterials          : マテリアル数格納先ポインタ
//          CModel** ppModelMesh          : モデルデータへのダブルポインタ
// 戻り値 : bool型                        : 処理結果
// 説明   : モデルデータ生成処理
//==============================================================================
bool CRendererGL::CreateModel( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
{
	CLoader* pLoader = new CLoader;		// ローダーの生成
	bool bResult = false;				// 処理結果用

	bResult = pLoader->ModelLoad( pFileName , ppMaterials , pNumMaterials , ppModelMesh );
	delete pLoader;
	pLoader = NULL;

	return bResult;						// 処理結果の返却
}

//==============================================================================
// 関数名 : bool SetStreamSource( UINT streamNumber , CVertexBuffer* pStreamData , UINT offsetByte , UINT stride )
// 引数   : UINT streamNumber
//          CVertexBuffer* pStreamData
//          UINT offsetByte
//          UINT stride
// 戻り値 : bool型 : 処理結果
// 説明   : 頂点ストリーム設定処理
//==============================================================================
bool CRendererGL::SetStreamSource( UINT streamNumber , CVertexBuffer* pStreamData , UINT offsetByte , UINT stride )
{
	if( pStreamData == NULL )
	{
		return false;	// 頂点バッファーの値がおかしい
	}

	m_pCurVertexBuffer = pStreamData;		// 頂点バッファーをバインド
	m_stride           = stride;			// 次の頂点データまでのサイズを設定
	return true;
}

//==============================================================================
// 関数名 : bool SetIndices( CIndexBuffer* pIndexData )
// 引数   : CIndexBuffer* pIndexData : インデックスバッファーへのポインタ
// 戻り値 : bool型                   : 処理結果
// 説明   : インデックスバッファー設定処理
//==============================================================================
bool CRendererGL::SetIndices( CIndexBuffer* pIndexData )
{
	if( pIndexData == NULL )
	{
		return false;
	}

	m_pCurIndexBuffer = pIndexData;

	return true;
}

//==============================================================================
// 関数名 : bool SetFVF( ULONG FVF )
// 引数   : ULONG FVF : 頂点フォーマット
// 戻り値 : bool型    : 処理結果
// 説明   : 頂点フォーマット設定処理
//==============================================================================
bool CRendererGL::SetFVF( ULONG FVF )
{
	m_curFVF = FVF;
	return true;
}

//==============================================================================
// 関数名 : bool DrawPrimitive( PRIMITIVE_TYPE primitiveType , UINT startVertex , UINT primitiveCount )
// 引数   : PRIMITIVE_TYPE primitiveType  : 頂点描画タイプ
//          UINT startVertex              : 開始頂点の要素番号
//          UINT primitiveCount           : 描画プリミティブ数
// 戻り値 : bool型                        : 処理結果
// 説明   : プリミティブ描画処理
//==============================================================================
bool CRendererGL::DrawPrimitive( PRIMITIVE_TYPE primitiveType , UINT startVertex , UINT primitiveCount )
{
	CVertexBufferGL* pVtxBuf = dynamic_cast< CVertexBufferGL* >( m_pCurVertexBuffer );	// OpenGL用にダウンキャスト

	if( pVtxBuf == NULL )
	{
		return false;	// バッファーの不備により、描画失敗
	}

	// 描画モード取得
	GLenum mode;		// 描画モード

	switch( primitiveType )
	{
		case PT_POINT_LIST:
		{
			mode = GL_POINTS;
			break;
		}

		case PT_LINE_LIST:
		{
			mode = GL_LINES;
			break;
		}

		case PT_LINE_STRIP:
		{
			mode = GL_LINE_STRIP;
			break;
		}

		case PT_TRIANGLE_LIST:
		{
			mode = GL_TRIANGLES;
			break;
		}

		case PT_TRIANGLE_STRIP:
		{
			mode = GL_TRIANGLE_STRIP;
			break;
		}

		case PT_TRIANGLE_FAN:
		{
			mode = GL_TRIANGLE_FAN;
			break;
		}

		default:
		{
			return false;	// タイプ指定の不備により、描画失敗
		}
	}

	// 描画開始
	int primNum = primitiveCount;					// プリミティブ描画回数
	int idx = startVertex;							// 参照インデックス
	void* pVtxData = NULL;							// 頂点データへのポインタ
	
	pVtxBuf->GetPrivateData( &pVtxData , NULL );	// データ取得

	glBegin( mode );
	{
		for( int primCnt = 0 ; primCnt < primNum ; primCnt++ )
		{
			// 描画タイプに応じて処理を分岐
			switch( primitiveType )
			{
				case PT_POINT_LIST:
				{
					break;
				}

				case PT_LINE_LIST:
				{
					break;
				}

				case PT_LINE_STRIP:
				{
					break;
				}

				case PT_TRIANGLE_LIST:
				{
					break;
				}

				case PT_TRIANGLE_STRIP:
				{
					// 三角形ストリップ描画
					if( m_curFVF == GL_FVF_VERTEX_3D )
					{
						VERTEX_3D* pVtx = ( VERTEX_3D* )pVtxData;

						for( int i = 0 ; i < 3 ; i++ )
						{
							glTexCoord2f( pVtx[ i ].tex.x , pVtx[ i ].tex.y );

							COLOR_F32 col = COLOR_F32( pVtx[ i ].col );

							glColor4f( col.r , col.g , col.b , col.a );
							glNormal3f( pVtx[ i ].nor.x , pVtx[ i ].nor.y , pVtx[ i ].nor.z );
							glVertex3f( pVtx[ i ].pos.x , pVtx[ i ].pos.y , pVtx[ i ].pos.z );
						}

						pVtxData = ( char* )pVtxData + m_stride;		// ポインター参照位置をずらす
					}
					else if( m_curFVF == GL_FVF_VERTEX_2D )
					{
						VERTEX_2D* pVtx = ( VERTEX_2D* )pVtxData;
						
						for( int i = 0 ; i < 3 ; i++ )
						{
							glTexCoord2f( pVtx->tex.x , pVtx->tex.y );

							COLOR_F32 col = COLOR_F32( pVtx[ i ].col );

							glColor4f( col.r , col.g , col.b , col.a );
							glVertex3f( pVtx->pos.x , pVtx->pos.y , pVtx->pos.z );
						}

						pVtxData = ( VERTEX_2D* )pVtxData + m_stride;		// ポインター参照位置をずらす
					}

					break;
				}

				case PT_TRIANGLE_FAN:
				{
					break;
				}
			}
		}
	}
	glEnd();

	return true;
}

//==============================================================================
// 関数名 : bool DrawIndexedPrimitive( 
//                PRIMITIVE_TYPE primitiveType , int baseVertexIndex , UINT minIndex ,
//                UINT numVertices , UINT startIndex , UINT primitiveCount )]
//
// 引数   : PRIMITIVE_TYPE primitiveType  : 頂点描画タイプ
//          int baseVertexIndex           : 開始頂点の要素番号
//          UINT minIndex                 : 
//          UINT numVertices              : 
//          UINT startIndex               : 
//          UINT primitiveCount           : 描画プリミティブ数
// 戻り値 : bool型                        : 処理結果
// 説明   : インデックス付きプリミティブ描画処理
//==============================================================================
bool CRendererGL::DrawIndexedPrimitive( PRIMITIVE_TYPE primitiveType , int baseVertexIndex , UINT minIndex , UINT numVertices , UINT startIndex , UINT primitiveCount )
{
	LPVertexBufferGL pVtxBuf = dynamic_cast< LPVertexBufferGL >( m_pCurVertexBuffer );	// 頂点バッファーをOpenGL用にダウンキャスト

	if( pVtxBuf == NULL )
	{
		return false;	// バッファーの不備により、描画失敗
	}

	LPIndexBufferGL pIdxBuf = dynamic_cast< LPIndexBufferGL >( m_pCurIndexBuffer );		// インデックスバッファーをOpenGL用にダウンキャスト

	if( pIdxBuf == NULL )
	{
		return false;	// バッファーの不備により、描画失敗
	}

	// 描画モード取得
	GLenum mode;		// 描画モード

	switch( primitiveType )
	{
		case PT_POINT_LIST:
		{
			mode = GL_POINTS;
			break;
		}

		case PT_LINE_LIST:
		{
			mode = GL_LINES;
			break;
		}

		case PT_LINE_STRIP:
		{
			mode = GL_LINE_STRIP;
			break;
		}

		case PT_TRIANGLE_LIST:
		{
			mode = GL_TRIANGLES;
			break;
		}

		case PT_TRIANGLE_STRIP:
		{
			mode = GL_TRIANGLE_STRIP;
			break;
		}

		case PT_TRIANGLE_FAN:
		{
			mode = GL_TRIANGLE_FAN;
			break;
		}

		default:
		{
			return false;	// タイプ指定の不備により、描画失敗
		}
	}

	// 描画開始
	int primNum = primitiveCount;								// プリミティブ描画回数
	int idx = 0;												// 参照インデックス
	void* pVtxData = NULL;										// 頂点データへのポインタ
	WORD* pIdxData = NULL;										// インデックスデータへのポインタ

	pVtxBuf->GetPrivateData( &pVtxData , NULL );				// 頂点データ取得
	pIdxBuf->GetPrivateData( ( void** )&pIdxData , NULL );		// インデックスデータ取得

	glBegin( mode );
	{
		for( int primCnt = 0 ; primCnt < primNum ; primCnt++ )
		{
			// 描画タイプに応じて処理を分岐
			switch( primitiveType )
			{
				case PT_POINT_LIST:
				{
					break;
				}

				case PT_LINE_LIST:
				{
					break;
				}

				case PT_LINE_STRIP:
				{
					break;
				}

				case PT_TRIANGLE_LIST:
				{
					break;
				}

				case PT_TRIANGLE_STRIP:
				{
					// 三角形ストリップ描画
					if( m_curFVF == GL_FVF_VERTEX_3D )
					{
						VERTEX_3D* pVtx = ( VERTEX_3D* )pVtxData;

						for( int i = 0 ; i < 3 ; i++ )
						{
							glTexCoord2f( pVtx[ i ].tex.x , pVtx[ i ].tex.y );

							COLOR_F32 col = COLOR_F32( pVtx[ i ].col );

							glColor4f( col.r , col.g , col.b , col.a );
							glNormal3f( pVtx[ i ].nor.x , pVtx[ i ].nor.y , pVtx[ i ].nor.z );
							glVertex3f( pVtx[ i ].pos.x , pVtx[ i ].pos.y , pVtx[ i ].pos.z );
						}

						pVtxData = ( char* )pVtxData + m_stride;		// ポインター参照位置をずらす
					}
					else if( m_curFVF == GL_FVF_VERTEX_2D )
					{
						VERTEX_2D* pVtx = ( VERTEX_2D* )pVtxData;

						for( int i = 0 ; i < 3 ; i++ )
						{
							glTexCoord2f( pVtx->tex.x , pVtx->tex.y );

							COLOR_F32 col = COLOR_F32( pVtx[ i ].col );

							glColor4f( col.r , col.g , col.b , col.a );
							glVertex3f( pVtx->pos.x , pVtx->pos.y , pVtx->pos.z );
						}

						pVtxData = ( VERTEX_2D* )pVtxData + m_stride;		// ポインター参照位置をずらす
					}

					break;
				}

				case PT_TRIANGLE_FAN:
				{
					break;
				}
			}
		}
	}
	glEnd();

	return true;
}

//==============================================================================
// 関数名 : void Set2DCamera( void )
// 引数   : void
// 戻り値 : void
// 説明   : 2Dカメラ設定
//==============================================================================
void CRendererGL::Set2DCamera( void )
{
	/* ===カメラ設定( 2D )=== */
	glMatrixMode( GL_PROJECTION );												// 行列モード切替
	glLoadIdentity();															// 射影行列の初期化

	glMatrixMode( GL_MODELVIEW );												// 行列モード切替
	glLoadIdentity();															// ビュー行列の初期化
	glOrtho( 0 , SCREEN_WIDTH , SCREEN_HEIGHT , 0 , 0.0f , 1.0f );				// 平面設定

	glDisable( GL_DEPTH_TEST );													// ZバッファーOFF
}

//==============================================================================
// 関数名 : void Set3DCamera( void )
// 引数   : void
// 戻り値 : void
// 説明   : 3Dカメラ設定
//==============================================================================
void CRendererGL::Set3DCamera( void )
{
	/* ===カメラ設定( 3D )=== */
	glViewport( 0 , 0 , ( int )SCREEN_WIDTH , ( int )SCREEN_HEIGHT );			// ビューポートの設定

	glMatrixMode( GL_PROJECTION );												// 行列モード切替
	glLoadIdentity();															// 射影行列の初期化
	gluPerspective( 30.0f , SCREEN_WIDTH / SCREEN_HEIGHT , 1.0f , 10000.0f );	// 射影行列の設定

	glMatrixMode( GL_MODELVIEW );												// 行列モードを戻す
	glLoadIdentity();															// ビュー行列の初期化
	gluLookAt(  0.0f, 200.0f, 1200.0f,											// 視点
				0.0f, 0.0f, 0.0f,												// 注視点
				0.0f, 1.0f, 0.0f);												// 上方向ベクトル

	glEnable( GL_DEPTH_TEST );													// ZバッファーON
}

//==============================================================================
// 関数名 : CRendererGL()
// 引数   : void
// 戻り値 : void
// 説明   : コンストラクタ
//==============================================================================

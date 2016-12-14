//==============================================================================
// タイトル     :   OpenGL用レンダラークラス
// ファイル名   :   rendererGL.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/04/19
//==============================================================================

//==============================================================================
// 更新履歴: -2016/04/19 数藤凌哉
//           ・制作開始
//           -2016/05/13
//           ・レンダラーからシーンの処理を分離
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================
#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "renderer.h"
#include "materialGL.h"

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================
#pragma comment( lib , "opengl32.lib" )		// OpenGL用
#pragma comment( lib , "glu32.lib" )		// OpenGL用

//==============================================================================
// 前方宣言
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================
#define GL_FVF_XYZ				0x002				// 頂点データ( XYZ座標利用 )
#define GL_FVF_NORMAL			0x010				// 法線
#define GL_FVF_DIFFUSE			0x040				// ディフューズ頂点色
#define GL_FVF_TEX_MASK			0xf00				// テクスチャ利用判定用マスクビット
#define GL_FVF_TEX1				0x100				// 1番目のテクスチャ

// OpenGL1.3からマルチテクスチャが利用可能らしいので、それ用に残しておく
//#define GL_FVF_TEX0				0x000				// 0番目のテクスチャ
//#define GL_FVF_TEX2				0x200				// 2番目のテクスチャ
//#define GL_FVF_TEX3				0x300				// 3番目のテクスチャ
//#define GL_FVF_TEX4				0x400				// 4番目のテクスチャ
//#define GL_FVF_TEX5				0x500				// 5番目のテクスチャ
//#define GL_FVF_TEX6				0x600				// 6番目のテクスチャ
//#define GL_FVF_TEX7				0x700				// 7番目のテクスチャ
//#define GL_FVF_TEX8				0x800				// 8番目のテクスチャ

#define GL_FVF_VERTEX_2D	( GL_FVF_XYZ | GL_FVF_DIFFUSE | GL_FVF_TEX1 )						// 2D用頂点フォーマット
#define GL_FVF_VERTEX_3D	( GL_FVF_XYZ | GL_FVF_DIFFUSE | GL_FVF_TEX1 | GL_FVF_NORMAL )		// 3D用頂点フォーマット

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// クラス宣言
//==============================================================================
class CRendererGL : public CRenderer
{
	//---------------------------------------------------------------
	// [ メンバ関数 ]
	//---------------------------------------------------------------
public:
	CRendererGL();														// コンストラクタ
	~CRendererGL();														// デストラクタ

	bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow );		// 初期化
	void Uninit( void );												// 終了
	void Update( void );												// 更新
	void Draw( void );													// 描画

	bool BeginScene( void );											// 描画開始
	void EndScene( void );												// 描画終了

	bool SwapBuffer( void );											// バックバッファ入れ替え処理

	bool CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff );	// 頂点バッファ生成処理
	bool CreateTexture( char* pSrcFile , CTexture** ppTexture );		// テクスチャ生成処理

	bool CreateModel(													// モデルデータ生成処理
		char* pFileName,
		CMaterialBuffer** ppMaterials,
		DWORD* pNumMaterials,
		CModel** ppModelMesh );

	bool SetStreamSource(												// 頂点バッファーを設定する
		UINT streamNumber,
		CVertexBuffer* pStreamData,
		UINT offsetByte,
		UINT stride );

	bool SetIndices( CIndexBuffer* pIndexData );						// インデックスバッファー設定

	bool SetFVF( unsigned long FVF );									// 頂点フォーマット設定

	bool DrawPrimitive(													// プリミティブ描画
		PRIMITIVE_TYPE primitiveType,
		UINT startVertex,
		UINT primitiveCount );

	bool DrawIndexedPrimitive(											// インデックス付きプリミティブ描画
		PRIMITIVE_TYPE primitiveType ,
		int baseVertexIndex ,
		UINT minIndex ,
		UINT numVertices ,
		UINT startIndex ,
		UINT primitiveCount );

	void Set2DCamera( void );											// 2Dカメラ設定( 後ほどカメラクラスに移動予定 )
	void Set3DCamera( void );											// 3Dカメラ設定( 後ほどカメラクラスに移動予定 )

	void* GetDevice( void ){ return ( void* )m_glrc; }					// デバイス取得処理

	//------------------------------------------------------------------
	// [ メンバ変数 ]
	//------------------------------------------------------------------
private:
	HDC     m_hdc;								// デバイスコンテキスト
	HGLRC   m_glrc;								// OpenGL用レンダリングコンテキストハンドル
	HWND    m_hWnd;								// ウィンドウハンドル

	LPVertexBuffer m_pCurVertexBuffer;			// 現在設定されている頂点バッファー
	LPIndexBuffer  m_pCurIndexBuffer;			// 現在設定されているインデックスバッファー

	ULONG m_curFVF;								// 現在設定されている頂点フォーマット
	UINT m_stride;								// 頂点バッファーのオフセット( Byte単位 )
};

//==============================================================================
// プロトタイプ宣言
//==============================================================================

//==============================================================================
// タイトル     :   DirectX用レンダラークラス
// ファイル名   :   rendererDX.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/04/18
//==============================================================================

//==============================================================================
// 更新履歴: -2016/04/18 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#ifndef _RENDERER_DX_H_
#define _RENDERER_DX_H_

//==============================================================================
// インクルードファイル
//==============================================================================
#include "d3dx9.h"
#include "renderer.h"

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================
#pragma comment( lib , "d3d9.lib" )			// 描画処理に必要
#pragma comment( lib , "d3dx9.lib" )		// 上記の拡張ライブラリ
#pragma comment( lib , "dxguid.lib" )		// DirectXコンポーネント使用に必要
#pragma comment( lib , "dinput8.lib" )		// 入力処理用

//==============================================================================
// 前方宣言
//==============================================================================
class CSceneDX;

//==============================================================================
// マクロ定義
//==============================================================================
/* ===ポリゴン用=== */
#define FVF_VERTEX_2D		( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )				// 2Dポリゴンフォーマット
//#define FVF_VERTEX_3D		( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	// 3Dポリゴンフォーマット

//==============================================================================
// 構造体宣言
//==============================================================================
//typedef struct
//{							/* ==2Dポリゴンの構造体== */
//	D3DXVECTOR3 pos;			// 頂点座標
//	float rhw;					// 座標変換用関数
//	D3DCOLOR col;				// 頂点カラー
//	D3DXVECTOR2 tex;			// テクスチャ座標
//
//} VERTEX_2D;

//typedef struct
//{							/* ==3Dポリゴンの構造体== */
//	D3DXVECTOR3 pos;			// 頂点座標
//	D3DXVECTOR3 nor;			// 法線ベクトル
//	D3DCOLOR col;				// 頂点カラー
//	D3DXVECTOR2 tex;			// テクスチャ座標
//
//} VERTEX_3D;

//==============================================================================
// クラス宣言
//==============================================================================
class CRendererDX : public CRenderer
{
	/* ===メンバ関数=== */
public:
	CRendererDX();														// コンストラクタ
	~CRendererDX();														// デストラクタ

	bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow );		// 初期化
	void Uninit( void );												// 終了
	void Update( void );												// 更新
	void Draw( void );													// 描画

	bool BeginScene( void );											// 描画開始
	void EndScene( void );												// 描画終了

	bool SwapBuffer( void );											// バックバッファ入れ替え処理

	bool CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff );	// 頂点バッファ生成処理( 流石にクソすぎるので、あとで修正したい )
	bool CreateTexture( char* pSrcFile , void** ppTexture );			// テクスチャ生成処理( 流石にクソすぎるので、あとで修正したい )

	void* GetDevice( void ){ return ( void* )m_pD3DDevice; }			// デバイス取得処理( 流石にクソすぎるので、あとで修正したい )

	/* ===メンバ変数=== */
private:
	LPDIRECT3D9       m_pD3D;						// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;					// Direct3Dデバイスへのポインタ

	CSceneDX*         m_pScene;						// シーン処理へのポインタ
};

//==============================================================================
// プロトタイプ宣言
//==============================================================================

#endif
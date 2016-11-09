//==============================================================================
// タイトル     :   レンダラークラス
// ファイル名   :   renderer.h
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
#pragma once

//==============================================================================
// インクルードファイル
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
// マクロ定義
//==============================================================================
typedef enum
{							/* ==レンダラー識別子== */
	RENDERER_TYPE_DX = 0,		// DirectX
	RENDERER_TYPE_GL,			// OpenGL
	RENDERER_TYPE_MAX,			// 識別子総数

} RENDERER_TYPE;

enum PRIMITIVE_TYPE
{							/* ==プリミティブ描画タイプ== */
	PT_POINT_LIST = 0,			// 点リスト
	PT_LINE_LIST,				// 線リスト
	PT_LINE_STRIP,				// 線ストリップ
	PT_TRIANGLE_LIST,			// 三角形リスト
	PT_TRIANGLE_STRIP,			// 三角形ストリップ
	PT_TRIANGLE_FAN,			// 三角形ファン
	PT_MAX,						// 総数
};

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// クラス宣言
//==============================================================================
class CRenderer
{
	/* ===メンバ関数=== */
public:
	CRenderer(){};			// コンストラクタ
	~CRenderer(){};			// デストラクタ

	virtual bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow ) = 0;			// 初期化処理
	virtual void Uninit( void ) = 0;													// 終了処理
	virtual void Update( void ) = 0;													// 更新処理
	virtual void Draw( void ) = 0;														// 描画処理

	virtual bool BeginScene( void ) = 0;												// 描画開始
	virtual void EndScene( void ) = 0;													// 描画終了

	virtual bool SwapBuffer( void ) = 0;												// バックバッファーの入れ替え

	virtual bool CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff ) = 0;		// 頂点バッファ生成処理
	virtual bool CreateTexture( char* pSrcFile , CTexture** ppTexture ) = 0;			// テクスチャ生成処理

	virtual bool CreateModel(															// モデルデータ生成処理
		char* pFileName,
		CMaterialBuffer** ppMaterials,
		DWORD* pNumMaterials,
		CModel** ppModelMesh ) = 0;

	virtual bool SetStreamSource(														// 頂点バッファーを設定する
		UINT streamNumber,
		CVertexBuffer* pStreamData,
		UINT offsetByte,
		UINT stride ) = 0;

	virtual bool SetIndices( CIndexBuffer* pIndexData ) = 0;							// インデックスバッファー設定

	virtual bool SetFVF( unsigned long FVF ) = 0;										// 頂点フォーマット設定

	virtual bool DrawPrimitive(															// プリミティブ描画
		PRIMITIVE_TYPE primitiveType,
		UINT startVertex,
		UINT primitiveCount ) = 0;

	virtual bool DrawIndexedPrimitive(													// インデックス付きプリミティブ描画
		PRIMITIVE_TYPE primitiveType,
		int baseVertexIndex,
		UINT minIndex,
		UINT numVertices,
		UINT startIndex,
		UINT primitiveCount ) = 0;

	virtual void* GetDevice( void ) = 0;												// デバイス取得

	static CRenderer* Create( RENDERER_TYPE type );

	RENDERER_TYPE GetRendererType( void ){ return m_type; }		// 生成されているレンダラータイプの取得

	/* ===メンバ変数=== */
protected:
	RENDERER_TYPE m_type;			// 生成されているレンダラーのタイプ

};

typedef CRenderer* LPRenderer;

//==============================================================================
// プロトタイプ宣言
//==============================================================================

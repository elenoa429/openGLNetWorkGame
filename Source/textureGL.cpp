//==============================================================================
// タイトル     :   テクスチャ用クラス
// ファイル名   :   texture.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/05/02
//==============================================================================

//==============================================================================
// 更新履歴: -2016/05/02 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "textureGL.h"

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
// 関数名 : CTextureGL()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CTextureGL::CTextureGL()
{
	m_texName = 0;
	m_texType = 0;
}

//==============================================================================
// 関数名 : ~CTextureGL()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CTextureGL::~CTextureGL()
{

}

//==============================================================================
// 関数名 : CTextureGL* Create( int width , int height , GLuint texType , GLubyte* bits )
// 引数   : int width      : 
//          int height     : 
//          GLuint texType : 
//          GLubyte* bits  : 
// 戻り値 : CTextureGL*型
// 説明   : 生成処理
//==============================================================================
CTextureGL* CTextureGL::Create( int width , int height , GLuint texType , GLubyte* bits )
{
	CTextureGL* newInstance = new CTextureGL;					// インスタンス生成
	newInstance->Init( width , height , texType , bits );		// 初期化処理

	return newInstance;											// 生成したインスタンスへのポインタを返却
}

//==============================================================================
// 関数名 : void Init( int width , int height , GLuint texType , GLubyte* bits )
// 引数   : int width      : 幅
//          int height     : 高さ
//          GLuint texType : 生成テクスチャタイプ
//          GLubyte* bits  : テクスチャのビットデータ
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
void CTextureGL::Init( int width , int height , GLuint texType , GLubyte* bits )
{
	CTexture::Init( width , height );		// 基底クラスの初期化処理

	m_texType = texType;

	glEnable( GL_TEXTURE_2D );
	glGenTextures( 1 , &m_texName );
	glBindTexture( GL_TEXTURE_2D , m_texName );

	glPixelStorei( GL_UNPACK_ALIGNMENT , 1 );

	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT );

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		texType,
		m_width,
		m_height,
		0,
		texType,
		GL_UNSIGNED_BYTE,
		bits );
}

//==============================================================================
// 関数名 : void Release( void )
// 引数   : void
// 戻り値 : void
// 説明   : 解放処理
//==============================================================================
void CTextureGL::Release( void )
{
	glDeleteTextures( 1 , &m_texName );
}

//==============================================================================
// 関数名 : void Set( void )
// 引数   : void
// 戻り値 : void
// 説明   : 設定処理
//==============================================================================
void CTextureGL::Set( void )
{
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D , m_texName );
}

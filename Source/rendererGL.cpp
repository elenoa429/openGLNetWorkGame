//==============================================================================
// �^�C�g��     :   OpenGLX�p�����_���[�N���X
// �t�@�C����   :   rendererGL.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/04/18
//==============================================================================

//==============================================================================
// �X�V����: -2016/04/18 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "rendererGL.h"
#include "texture.h"
#include "loader.h"
#include "vertexBufferGL.h"
#include "indexBufferGL.h"

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
// �֐��� : CRendererGL()
// ����   : void
// �߂�l : void
// ����   : �R���X�g���N�^
//==============================================================================
CRendererGL::CRendererGL()
{
	m_hdc    = NULL;
	m_glrc   = NULL;
	m_hWnd   = NULL;

	m_pCurVertexBuffer = NULL;
	m_curFVF = 0;
	m_stride = 0;

	m_type   = RENDERER_TYPE_GL;	// OpenGL�Ő���
}

//==============================================================================
// �֐��� : ~CRendererGL()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CRendererGL::~CRendererGL()
{
}

//==============================================================================
// �֐��� : bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
// ����   : void
// �߂�l : bool�^ : ��������
// ����   : ����������
//==============================================================================
bool CRendererGL::Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
{
	/* ===�f�o�C�X�R���e�L�X�g�̎擾=== */
	m_hWnd = hWnd;										// �E�B���h�E�n���h���̕ێ�
	m_hdc = GetDC( hWnd );								// �f�o�C�X�R���e�L�X�g���擾

	/* ===�s�N�Z���t�H�[�}�b�g�̐ݒ�=== */
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

	/* ===�����_�����O�R���e�L�X�g�쐬=== */
	m_glrc = wglCreateContext( m_hdc );

	if( !m_glrc )
	{
		ReleaseDC( hWnd, m_hdc );
		return false;
	}

	wglMakeCurrent( m_hdc, m_glrc );

	/* ===�S�����������I��=== */
	return true;																	// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CRendererGL::Uninit( void )
{
	/* ===�f�o�C�X�̉��=== */
	wglMakeCurrent( NULL , NULL );		// �J�����g�R���e�L�X�g�𖳌��ɂ���
	wglDeleteContext( m_glrc );			// �J�����g�R���e�L�X�g���폜
	ReleaseDC( m_hWnd , m_hdc );		// �f�o�C�X�R���e�L�X�g�̉��

	/* ===���̑��̉������=== */
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CRendererGL::Update( void )
{
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CRendererGL::Draw( void )
{
}

//==============================================================================
// �֐��� : bool BeginScene( void )
// ����   : void
// �߂�l : void
// ����   : �`��J�n����
//==============================================================================
bool CRendererGL::BeginScene( void )
{
	/* ===��ʂ̏�����=== */
	wglMakeCurrent( m_hdc , m_glrc );							// 
	glClearColor( 0.6f , 0.6f , 1.0f , 1.0f );					// ��ʃN���A
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		// �o�b�N�o�b�t�@�[�N���A
	glClearDepth( 1.0f );										// �f�v�X�N���A�H

	/* ===�`�揈��=== */
	return true;				// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : void EndScene( void )
// ����   : void
// �߂�l : void
// ����   : �`��I������
//==============================================================================
void CRendererGL::EndScene( void )
{
	
}

//==============================================================================
// �֐��� : bool SwapBuffer( void )
// ����   : void
// �߂�l : bool�^ : ��������
// ����   : �o�b�N�o�b�t�@�[�̃X���b�v����
//==============================================================================
bool CRendererGL::SwapBuffer( void )
{
	glFlush();							// 
	SwapBuffers( m_hdc );				// �o�b�t�@�̐؂�ւ�
	wglMakeCurrent( NULL , NULL );		// 
	return true;						// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : bool CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff )
// ����   : void
// �߂�l : bool�^ : ��������
// ����   : ���_�o�b�t�@�[��������
//==============================================================================
bool CRendererGL::CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff )
{
	CVertexBufferGL* pVtxBuf = NULL;

	// ��������
	pVtxBuf = new CVertexBufferGL;

	char* pBuff = new char[ size ];					// 1Byte�̔z����T�C�Y������

	pVtxBuf->SetPrivateData( pBuff , size );		// �f�[�^�ݒ�

	*ppVtxBuff = pVtxBuf;							// �|�C���^�[�Z�b�g

	return true;									// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : bool CreateTexture( char* pSrcFile , CTexture** ppTexture )
// ����   : char* pSrcFile       : �t�@�C����
//          CTexture** ppTexture : �e�N�X�`�������ւ̃_�u���|�C���^
// �߂�l : bool�^               : ��������
// ����   : �e�N�X�`����������
//==============================================================================
bool CRendererGL::CreateTexture( char* pSrcFile , CTexture** ppTexture )
{
	wglMakeCurrent( m_hdc , m_glrc );

	CLoader* pLoader = new CLoader;		// ���[�_�[�̐���
	bool bResult = false;				// �������ʗp

	bResult = pLoader->TextuerLoad( pSrcFile , ppTexture );
	delete pLoader;
	pLoader = NULL;

	wglMakeCurrent( NULL , NULL );

	return bResult;						// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : bool CreateModel( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
// ����   : char* pFileName               : �t�@�C����
//          CMaterialBuffer** ppMaterials : �}�e���A���p�o�b�t�@�[�ւ̃_�u���|�C���^
//          DWORD* pNumMaterials          : �}�e���A�����i�[��|�C���^
//          CModel** ppModelMesh          : ���f���f�[�^�ւ̃_�u���|�C���^
// �߂�l : bool�^                        : ��������
// ����   : ���f���f�[�^��������
//==============================================================================
bool CRendererGL::CreateModel( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
{
	CLoader* pLoader = new CLoader;		// ���[�_�[�̐���
	bool bResult = false;				// �������ʗp

	bResult = pLoader->ModelLoad( pFileName , ppMaterials , pNumMaterials , ppModelMesh );
	delete pLoader;
	pLoader = NULL;

	return bResult;						// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : bool SetStreamSource( UINT streamNumber , CVertexBuffer* pStreamData , UINT offsetByte , UINT stride )
// ����   : UINT streamNumber
//          CVertexBuffer* pStreamData
//          UINT offsetByte
//          UINT stride
// �߂�l : bool�^ : ��������
// ����   : ���_�X�g���[���ݒ菈��
//==============================================================================
bool CRendererGL::SetStreamSource( UINT streamNumber , CVertexBuffer* pStreamData , UINT offsetByte , UINT stride )
{
	if( pStreamData == NULL )
	{
		return false;	// ���_�o�b�t�@�[�̒l����������
	}

	m_pCurVertexBuffer = pStreamData;		// ���_�o�b�t�@�[���o�C���h
	m_stride           = stride;			// ���̒��_�f�[�^�܂ł̃T�C�Y��ݒ�
	return true;
}

//==============================================================================
// �֐��� : bool SetIndices( CIndexBuffer* pIndexData )
// ����   : CIndexBuffer* pIndexData : �C���f�b�N�X�o�b�t�@�[�ւ̃|�C���^
// �߂�l : bool�^                   : ��������
// ����   : �C���f�b�N�X�o�b�t�@�[�ݒ菈��
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
// �֐��� : bool SetFVF( ULONG FVF )
// ����   : ULONG FVF : ���_�t�H�[�}�b�g
// �߂�l : bool�^    : ��������
// ����   : ���_�t�H�[�}�b�g�ݒ菈��
//==============================================================================
bool CRendererGL::SetFVF( ULONG FVF )
{
	m_curFVF = FVF;
	return true;
}

//==============================================================================
// �֐��� : bool DrawPrimitive( PRIMITIVE_TYPE primitiveType , UINT startVertex , UINT primitiveCount )
// ����   : PRIMITIVE_TYPE primitiveType  : ���_�`��^�C�v
//          UINT startVertex              : �J�n���_�̗v�f�ԍ�
//          UINT primitiveCount           : �`��v���~�e�B�u��
// �߂�l : bool�^                        : ��������
// ����   : �v���~�e�B�u�`�揈��
//==============================================================================
bool CRendererGL::DrawPrimitive( PRIMITIVE_TYPE primitiveType , UINT startVertex , UINT primitiveCount )
{
	CVertexBufferGL* pVtxBuf = dynamic_cast< CVertexBufferGL* >( m_pCurVertexBuffer );	// OpenGL�p�Ƀ_�E���L���X�g

	if( pVtxBuf == NULL )
	{
		return false;	// �o�b�t�@�[�̕s���ɂ��A�`�掸�s
	}

	// �`�惂�[�h�擾
	GLenum mode;		// �`�惂�[�h

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
			return false;	// �^�C�v�w��̕s���ɂ��A�`�掸�s
		}
	}

	// �`��J�n
	int primNum = primitiveCount;					// �v���~�e�B�u�`���
	int idx = startVertex;							// �Q�ƃC���f�b�N�X
	void* pVtxData = NULL;							// ���_�f�[�^�ւ̃|�C���^
	
	pVtxBuf->GetPrivateData( &pVtxData , NULL );	// �f�[�^�擾

	glBegin( mode );
	{
		for( int primCnt = 0 ; primCnt < primNum ; primCnt++ )
		{
			// �`��^�C�v�ɉ����ď����𕪊�
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
					// �O�p�`�X�g���b�v�`��
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

						pVtxData = ( char* )pVtxData + m_stride;		// �|�C���^�[�Q�ƈʒu�����炷
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

						pVtxData = ( VERTEX_2D* )pVtxData + m_stride;		// �|�C���^�[�Q�ƈʒu�����炷
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
// �֐��� : bool DrawIndexedPrimitive( 
//                PRIMITIVE_TYPE primitiveType , int baseVertexIndex , UINT minIndex ,
//                UINT numVertices , UINT startIndex , UINT primitiveCount )]
//
// ����   : PRIMITIVE_TYPE primitiveType  : ���_�`��^�C�v
//          int baseVertexIndex           : �J�n���_�̗v�f�ԍ�
//          UINT minIndex                 : 
//          UINT numVertices              : 
//          UINT startIndex               : 
//          UINT primitiveCount           : �`��v���~�e�B�u��
// �߂�l : bool�^                        : ��������
// ����   : �C���f�b�N�X�t���v���~�e�B�u�`�揈��
//==============================================================================
bool CRendererGL::DrawIndexedPrimitive( PRIMITIVE_TYPE primitiveType , int baseVertexIndex , UINT minIndex , UINT numVertices , UINT startIndex , UINT primitiveCount )
{
	LPVertexBufferGL pVtxBuf = dynamic_cast< LPVertexBufferGL >( m_pCurVertexBuffer );	// ���_�o�b�t�@�[��OpenGL�p�Ƀ_�E���L���X�g

	if( pVtxBuf == NULL )
	{
		return false;	// �o�b�t�@�[�̕s���ɂ��A�`�掸�s
	}

	LPIndexBufferGL pIdxBuf = dynamic_cast< LPIndexBufferGL >( m_pCurIndexBuffer );		// �C���f�b�N�X�o�b�t�@�[��OpenGL�p�Ƀ_�E���L���X�g

	if( pIdxBuf == NULL )
	{
		return false;	// �o�b�t�@�[�̕s���ɂ��A�`�掸�s
	}

	// �`�惂�[�h�擾
	GLenum mode;		// �`�惂�[�h

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
			return false;	// �^�C�v�w��̕s���ɂ��A�`�掸�s
		}
	}

	// �`��J�n
	int primNum = primitiveCount;								// �v���~�e�B�u�`���
	int idx = 0;												// �Q�ƃC���f�b�N�X
	void* pVtxData = NULL;										// ���_�f�[�^�ւ̃|�C���^
	WORD* pIdxData = NULL;										// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	pVtxBuf->GetPrivateData( &pVtxData , NULL );				// ���_�f�[�^�擾
	pIdxBuf->GetPrivateData( ( void** )&pIdxData , NULL );		// �C���f�b�N�X�f�[�^�擾

	glBegin( mode );
	{
		for( int primCnt = 0 ; primCnt < primNum ; primCnt++ )
		{
			// �`��^�C�v�ɉ����ď����𕪊�
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
					// �O�p�`�X�g���b�v�`��
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

						pVtxData = ( char* )pVtxData + m_stride;		// �|�C���^�[�Q�ƈʒu�����炷
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

						pVtxData = ( VERTEX_2D* )pVtxData + m_stride;		// �|�C���^�[�Q�ƈʒu�����炷
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
// �֐��� : void Set2DCamera( void )
// ����   : void
// �߂�l : void
// ����   : 2D�J�����ݒ�
//==============================================================================
void CRendererGL::Set2DCamera( void )
{
	/* ===�J�����ݒ�( 2D )=== */
	glMatrixMode( GL_PROJECTION );												// �s�񃂁[�h�ؑ�
	glLoadIdentity();															// �ˉe�s��̏�����

	glMatrixMode( GL_MODELVIEW );												// �s�񃂁[�h�ؑ�
	glLoadIdentity();															// �r���[�s��̏�����
	glOrtho( 0 , SCREEN_WIDTH , SCREEN_HEIGHT , 0 , 0.0f , 1.0f );				// ���ʐݒ�

	glDisable( GL_DEPTH_TEST );													// Z�o�b�t�@�[OFF
}

//==============================================================================
// �֐��� : void Set3DCamera( void )
// ����   : void
// �߂�l : void
// ����   : 3D�J�����ݒ�
//==============================================================================
void CRendererGL::Set3DCamera( void )
{
	/* ===�J�����ݒ�( 3D )=== */
	glViewport( 0 , 0 , ( int )SCREEN_WIDTH , ( int )SCREEN_HEIGHT );			// �r���[�|�[�g�̐ݒ�

	glMatrixMode( GL_PROJECTION );												// �s�񃂁[�h�ؑ�
	glLoadIdentity();															// �ˉe�s��̏�����
	gluPerspective( 30.0f , SCREEN_WIDTH / SCREEN_HEIGHT , 1.0f , 10000.0f );	// �ˉe�s��̐ݒ�

	glMatrixMode( GL_MODELVIEW );												// �s�񃂁[�h��߂�
	glLoadIdentity();															// �r���[�s��̏�����
	gluLookAt(  0.0f, 200.0f, 1200.0f,											// ���_
				0.0f, 0.0f, 0.0f,												// �����_
				0.0f, 1.0f, 0.0f);												// ������x�N�g��

	glEnable( GL_DEPTH_TEST );													// Z�o�b�t�@�[ON
}

//==============================================================================
// �֐��� : CRendererGL()
// ����   : void
// �߂�l : void
// ����   : �R���X�g���N�^
//==============================================================================

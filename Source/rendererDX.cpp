//==============================================================================
// �^�C�g��     :   DirectX�p�����_���[�N���X
// �t�@�C����   :   rendererDX.cpp
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
#include "rendererDX.h"
#include "sceneDX.h"

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
// �֐��� : CRendererDX()
// ����   : void
// �߂�l : void
// ����   : �R���X�g���N�^
//==============================================================================
CRendererDX::CRendererDX()
{
	m_pD3D       = NULL;
	m_pD3DDevice = NULL;
	m_pScene     = NULL;

	m_type       = RENDERER_TYPE_DX;	// DirectX�Ő���
}

//==============================================================================
// �֐��� : ~CRendererDX()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CRendererDX::~CRendererDX()
{
}

//==============================================================================
// �֐��� : bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
// ����   : void
// �߂�l : bool�^ : ��������
// ����   : ����������
//==============================================================================
bool CRendererDX::Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
{
	/* ===�ϐ��̐錾�E������=== */
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE        d3ddm;

	/* ===Direct3D�I�u�W�F�N�g�̐���=== */
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	if( m_pD3D == NULL )
	{
		return false;		// �������s
	}
	
	/* ===�f�B�X�v���C���[�h�̎擾=== */
	if( FAILED( m_pD3D -> GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &d3ddm ) ) )
	{
		return false;		// �擾���s
	}

	/* ===�������ݒ�=== */
	ZeroMemory( &d3dpp , sizeof( d3dpp ) );							// �������O����

																	/* ===DirectX�̏��ݒ�=== */
	d3dpp.BackBufferWidth            = ( UINT )SCREEN_WIDTH;			// | ��ʕ�
	d3dpp.BackBufferHeight           = ( UINT )SCREEN_HEIGHT;			// | ��ʍ���
	d3dpp.BackBufferFormat           = d3ddm.Format;					// | �o�b�N�o�b�t�@�t�H�[�}�b�g
	d3dpp.BackBufferCount            = 1;								// | �o�b�N�o�b�t�@��
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;			// | �o�b�t�@�؂�ւ��^�C�~���O
	d3dpp.EnableAutoDepthStencil     = TRUE;							// | ���s����
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D16;						// | �f�v�X�o�b�t�@�̎g�p�r�b�g��
	d3dpp.Windowed                   = bWindow;							// | �t���X�N���[������
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// | �o�b�t�@�̓����^�C�~���O
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// | �o�b�t�@�̓����^�C�~���O

	/* ===Direct3D�f�o�C�X�̐���=== */
	if( FAILED( m_pD3D -> CreateDevice(									/* ===��������=== */
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,
							hWnd,
							D3DCREATE_HARDWARE_VERTEXPROCESSING,
							&d3dpp,
							&m_pD3DDevice ) )
	){
		if( FAILED( m_pD3D -> CreateDevice(							/* ===��������=== */
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,
							hWnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&d3dpp,
							&m_pD3DDevice ) )
		){
			if( FAILED( m_pD3D -> CreateDevice(						/* ===�����O���=== */
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_REF,
							hWnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&d3dpp,
							&m_pD3DDevice ) )
			){
				return false;	// �������s
			}
		}
	}

	/* ==�����_�[�X�e�[�g�̏����ݒ�== */
	m_pD3DDevice -> SetRenderState( D3DRS_CULLMODE , D3DCULL_CCW );					// �J�����O�ݒ�
	m_pD3DDevice -> SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );				// �A���t�@�u�����h�ݒ�
	m_pD3DDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );			// �\�[�X���̐ݒ�
	m_pD3DDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );		// �f�X�g���̐ݒ�

	/* ===�T���v���[�X�e�[�g�̏����ݒ�=== */
	m_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_MINFILTER , D3DTEXF_LINEAR );		// �e�N�X�`���k�����̕�Ԑݒ�
	m_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_MAGFILTER , D3DTEXF_LINEAR );		// �e�N�X�`���g�厞�̕�Ԑݒ�
	m_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_ADDRESSU , D3DTADDRESS_WRAP );		// �e�N�X�`���t���W�̐ݒ�
	m_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_ADDRESSV , D3DTADDRESS_WRAP );		// �e�N�X�`���u���W�̐ݒ�

	/* ===�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�=== */
	m_pD3DDevice -> SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_MODULATE );	// �A���t�@�l�����ݒ�
	m_pD3DDevice -> SetTextureStageState( 0 , D3DTSS_ALPHAARG1 , D3DTA_TEXTURE );	// �������̈����ݒ�( 1 )
	m_pD3DDevice -> SetTextureStageState( 0 , D3DTSS_ALPHAARG2 , D3DTA_CURRENT );	// �������̈����ݒ�( 2 )

	//---------------------------------------------
	// [ ���̑��̏��� ]
	//---------------------------------------------
	m_pScene = new CSceneDX;

	if( m_pScene -> Init() == false )
	{
		return false;		// �������s
	}

	return true;																	// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CRendererDX::Uninit( void )
{
	/* ===�f�o�C�X�̉��=== */
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

	/* ===���̑��̉������=== */
	if( m_pScene != NULL )
	{
		m_pScene -> Uninit();
		delete m_pScene;
		m_pScene = NULL;
	}

}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CRendererDX::Update( void )
{
	m_pScene -> Update();
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CRendererDX::Draw( void )
{
	m_pScene -> Draw();
}

//==============================================================================
// �֐��� : bool BeginScene( void )
// ����   : void
// �߂�l : void
// ����   : �`��J�n����
//==============================================================================
bool CRendererDX::BeginScene( void )
{
	/* ===��ʂ̏�����=== */
	m_pD3DDevice -> Clear(								/* ===��ʃN���A=== */
		0,													// | �Œ�
		NULL,												// | �Œ�
		( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ),				// | �N���A����
		D3DCOLOR_RGBA( 0 , 0 , 0 , 0 ),						// | ��ʏ������F
		1.0f,												// | ���s�H
		0 );												// | �X�e���V���H

	/* ===�`�揈��=== */
	HRESULT hr = m_pD3DDevice -> BeginScene();			// �`��J�n����
	return SUCCEEDED( hr ) ? true : false;				// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : void EndScene( void )
// ����   : void
// �߂�l : void
// ����   : �`��I������
//==============================================================================
void CRendererDX::EndScene( void )
{
	m_pD3DDevice -> EndScene();						// �`��I��
}

//==============================================================================
// �֐��� : bool SwapBuffer( void )
// ����   : void
// �߂�l : bool�^ : ��������
// ����   : �o�b�N�o�b�t�@�[�̃X���b�v����
//==============================================================================
bool CRendererDX::SwapBuffer( void )
{
	HRESULT hr = m_pD3DDevice -> Present( NULL , NULL , NULL , NULL );		// �o�b�t�@�̐؂�ւ�
	return SUCCEEDED( hr ) ? true : false;									// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : bool CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff )
// ����   : void
// �߂�l : bool�^ : ��������
// ����   : ���_�o�b�t�@�[��������
//==============================================================================
bool CRendererDX::CreateVertexBuffer( UINT size , CVertexBuffer** ppVtxBuff )
{
	HRESULT hr = m_pD3DDevice -> CreateVertexBuffer(					/* ===�o�b�t�@�����ݒ�=== */
							sizeof( VERTEX_2D ) * size,						// | �m�ۂ���o�b�t�@�[�T�C�Y( Byte�P�� )
							D3DUSAGE_WRITEONLY,								// | �g�p���@
							FVF_VERTEX_2D,									// | ���_�t�H�[�}�b�g
							D3DPOOL_MANAGED,								// | ���\�[�X�̃o�b�t�@�[�̕ێ��ݒ�
							( LPDIRECT3DVERTEXBUFFER9* )ppVtxBuff,			// | �i�[��A�h���X
							NULL );											// | �e�̃n���h���H

	return SUCCEEDED( hr ) ? true : false;									// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : bool CreateTexture( char* pSrcFile , void** ppTexture )
// ����   : void
// �߂�l : bool�^ : ��������
// ����   : ���_�o�b�t�@�[��������
//==============================================================================
bool CRendererDX::CreateTexture( char* pSrcFile , void** ppTexture )
{
	HRESULT hr = D3DXCreateTextureFromFile(					/* ===�e�N�X�`���ǂݍ���=== */
					m_pD3DDevice,								// �f�o�C�X�|�C���^
					pSrcFile,									// �ǂݍ��ރe�N�X�`���t�@�C����
					( LPDIRECT3DTEXTURE9* )ppTexture );			// �e�N�X�`���|�C���^

	return SUCCEEDED( hr ) ? true : false;					// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : CRendererDX()
// ����   : void
// �߂�l : void
// ����   : �R���X�g���N�^
//==============================================================================

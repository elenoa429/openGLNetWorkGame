//==============================================================================
// �^�C�g��     :   ���C������
// �t�@�C����   :   main.cpp
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
#include "main.h"
#include "manager.h"
#include <CommCtrl.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================
#pragma comment( lib , "comctl32.lib" )		// �R�����R���g���[���p

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================
// �E�B���h�E�֘A
#define WND_CLASS_NAME		"ONION_S"						// �E�B���h�E�N���X��
#define WND_NAME			"OpenGL_ModelViewer"			// �E�B���h�E��

// FPS�֘A
#define FRAME_PER_SECOND	( 1000 / 60 )					// FPS�̌v���P��
#define FPS_GET_TIME		( 500 )							// FPS�擾����( �P�ʁFms )

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

//==============================================================================
// �O���[�o���錾
//==============================================================================
int g_nCountFPS = 0;									// FPS�J�E���^
RECT g_WindowSize;										// �E�B���h�E�T�C�Y�̋L�^�p

CManager* g_pManager = NULL;							// �Ǘ��N���X�ւ̃|�C���^

//================================================================================================================
// �֐��� : int WINAPI WinMain ( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
//
// ����   : HINSTANCE hInstance      : �A�v���P�[�V�����̃C���X�^���X�n���h��
//          HINSTANCE hPrevInstance  : �g���p�H( ��� NULL �łn�j )
//          LPSTR lpCmdLine          : �R�}���h���C������󂯎���������ւ̃|�C���^
//          int nCmdShow             : �A�v���P�[�V�����̏����E�B���h�E�\�����@�ݒ�
//
// �߂�l : int�^                    : 0 : ����I��
// ����   : ���C���֐�
//================================================================================================================
int WINAPI WinMain ( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
#ifdef _DEBUG
	// ���������[�N���o
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	// ----------------------------------------------------------------------
	// [ ���f���r���[�A�[�v���V�[�W������ ]
	// ----------------------------------------------------------------------
	//CModelViewerProc* pModelViewerProc = CModelViewerProc::Create( hInstance , IDR_MENU1 , IDR_ACCELERATOR1 );
	//CMenuBar* pMenuBar = pModelViewerProc->GetMenu();

	//----------------------------------------------
	// [ �E�B���h�E���� ]
	//----------------------------------------------
	DWORD dwFrameCount;																// �t���[���J�E���^
	DWORD dwCurrentTime;															// ���ݎ���
	DWORD dwExecLastTime;															// �A�v���X�V�̍ŏI����
	DWORD dwFPSLastTime;															// FPS�擾���̍ŏI����

	WNDCLASSEX wcex;																// �E�B���h�E�N���X

	wcex.cbSize         = sizeof( WNDCLASSEX );										// �������T�C�Y�w��
	wcex.style          = CS_HREDRAW | CS_VREDRAW;									// �\������E�B���h�E�̃X�^�C���ݒ�
	wcex.lpfnWndProc    = WndProc;													// �E�B���h�E�v���V�[�W���̃A�h���X�w��
	wcex.cbClsExtra     = 0;														// �g�p���Ȃ�
	wcex.cbWndExtra     = 0;														// �g�p���Ȃ�
	wcex.hInstance      = hInstance;												// �C���X�^���X�n���h��
	wcex.hIcon          = LoadIcon( hInstance , MAKEINTRESOURCE( IDI_ICON1 ) );		// �A�v���P�[�V�����̃A�C�R���w��
	wcex.hCursor        = LoadCursor( NULL, IDC_ARROW );							// �}�E�X�J�[�\���̎w��
	wcex.hbrBackground  = ( HBRUSH )( COLOR_WINDOW + 1 );							// �N���C�A���g�̈�̔w�i�F�w��
	wcex.lpszMenuName   = NULL;
	//wcex.lpszMenuName   = pMenuBar->GetMenuName();									// ���j���[�̎w��
	wcex.lpszClassName  = WND_CLASS_NAME;											// �E�B���h�E�N���X�̖��O
	wcex.hIconSm        = NULL;														// ���A�C�R���w�莞�̐ݒ�

	HWND hWnd;																		// �E�B���h�E�n���h��
	MSG msg;																		// ���b�Z�[�W�p
	RegisterClassEx( &wcex );														// �E�B���h�E�N���X�̓o�^
	RECT rect ={ 0 , 0 , ( LONG ) SCREEN_WIDTH , ( LONG ) SCREEN_HEIGHT };			// �E�B���h�E�쐬�p

	AdjustWindowRect(																/* ==�E�B���h�E����== */
		&rect ,																			// �����p�̕ϐ�
		WS_OVERLAPPEDWINDOW ,															// �X�^�C��
		false );																		// 

	hWnd = CreateWindowEx(															/* ==�E�B���h�E�쐬== */
		0 ,																				//
		WND_CLASS_NAME ,																// �E�B���h�E�N���X�̖��O
		WND_NAME ,																		// �E�B���h�E���̖̂��O
		WS_OVERLAPPEDWINDOW ,															// �E�B���h�E�X�^�C��
		CW_USEDEFAULT ,																	// �E�B���h�E����w���W
		CW_USEDEFAULT ,																	// �E�B���h�E����x���W
		( rect.right - rect.left ) ,													// �E�B���h�E��
		( rect.bottom - rect.top ) ,													// �E�B���h�E����
		NULL ,																			// �e�E�B���h�E�n���h��
		NULL ,																			// �q�E�B���h�E�h�c
		hInstance ,																		// �C���X�^���X�n���h��
		NULL );																			// �E�B���h�E�쐬�f�[�^

	if( hWnd == NULL )
	{
		return -1;
	}

	// ���f���r���[���[�\���v�f�̐����E������
	//pModelViewerProc->SetHWND( hWnd );												// �E�B���h�E�n���h���ݒ�
	//pModelViewerProc->MV_CreateDialog( hInstance , hWnd );							// �_�C�A���O����

	//----------------------------------------------
	// [ ���������� ]
	//----------------------------------------------
	// �E�B���h�E�\������
	ShowWindow( hWnd , nCmdShow );
	UpdateWindow( hWnd );

	// ���݂̃E�B���h�E�T�C�Y�̎擾
	GetWindowRect( hWnd , &g_WindowSize );

	// �Ǘ��N���X�̐����E������
	g_pManager = new CManager;							// �Ǘ��N���X����

	if( g_pManager->Init( hInstance , hWnd , true ) == false )
	{
		g_pManager->Uninit();
		delete g_pManager;
		g_pManager = NULL;
		return -1;										// �������s
	}

	// FPS�֘A
	timeBeginPeriod( 1 );								// ����\
	dwFrameCount = dwCurrentTime = 0;					// �J�E���^�n�̏�����
	dwExecLastTime = dwFPSLastTime = timeGetTime();		// �����̏�����

	//----------------------------------------------
	// [ ���C�����[�v ]
	//----------------------------------------------
	//HACCEL hAccel = pModelViewerProc->GetAccelerator()->GetHandle();

	while( 1 )
	{
		if( PeekMessage( &msg , NULL , 0 , 0 , PM_REMOVE ) != 0 )
		{
			//if( !TranslateAccelerator( hWnd , hAccel , &msg ) )
			//{
				// Windows�̏���
				if( msg.message == WM_QUIT )
				{
					// �I������n�m
					break;
				}
				else
				{
					// ���b�Z�[�W�̖|��E���o����
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
			//}
		}
		else
		{
			// �A�v���P�[�V�����̏���
			dwCurrentTime = timeGetTime();	// �����擾

			// �t���[�����擾����
			if( ( dwCurrentTime - dwFPSLastTime ) >= FPS_GET_TIME )
			{
				g_nCountFPS = ( dwFrameCount * 1000 ) / ( dwCurrentTime - dwFPSLastTime );	// �t���[�����̎擾
				dwFPSLastTime = dwCurrentTime;												// �擾�����̍X�V
				dwFrameCount = 0;															// �J�E���g���Z�b�g
			}

			// �A�v���P�[�V�����̍X�V�E�`�揈��
			if( ( dwCurrentTime - dwExecLastTime ) >= FRAME_PER_SECOND )
			{
				dwExecLastTime = dwCurrentTime;		// �擾�����̍X�V

				g_pManager->Update();				// �Ǘ��N���X�̍X�V����
				g_pManager->Draw();					// �Ǘ��N���X�̕`�揈��

				dwFrameCount++;						// �t���[�����J�E���g�A�b�v
			}
		}
	}

	//----------------------------------------------
	// [ �I���������� ]
	//----------------------------------------------
	// ���f���r���[�A�[�v���V�[�W�����
	//CModelViewerProc::GetModelViewerProc()->Release();

	// �Ǘ��N���X�̉������
	if( g_pManager != NULL )
	{
		g_pManager->Uninit();
		delete g_pManager;
		g_pManager = NULL;
	}

	UnregisterClass( WND_CLASS_NAME , wcex.hInstance );		// �E�B���h�E�N���X�̓o�^����
	timeEndPeriod( 1 );										// �X�V�����̏I������

	return ( int ) msg.wParam;
}

//================================================================================================================
// �֐��� : CManager* GetManager( void )
// ����   : void
// �߂�l : CManager*�^
// ����   : �Ǘ��N���X�擾����
//================================================================================================================
CManager* GetManager( void )
{
	return g_pManager;	// �Ǘ��N���X�ւ̃|�C���^��ԋp
}

//================================================================================================================
// �֐��� : void DrawFPS( void )
// ����   : void
// �߂�l : void
// ����   : FPS�`��p
//================================================================================================================
#ifdef _DEBUG
void DrawFPS( void )
{
	/* ===FPS�̊m�F=== */
	//PrintDebugProc( "FPS : %d" , g_nCountFPS );
	return;
}
#endif


//============================================================================================
// �֐��� : LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wPram , LPARAM lParam )
//
// ����   : HWND hWnd     : 
//          UINT uMsg     : 
//          WPARAM wPram  : 
//          LPARAM lParam : 
//
// �߂�l : LRESULT�^
// ����   : �E�B���h�E�v���V�[�W��
//============================================================================================
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	int nID;																				// ���b�Z�[�W�{�b�N�X����̖��ߔ��f�p
	CMenuBar* pMenuBar = NULL;																// ���j���[�o�[�����ւ̃|�C���^

	switch( uMsg )
	{
		case WM_CLOSE:
		{
			ShowCursor( TRUE );																// �J�[�\���̏o��
			nID = MessageBox( hWnd , "�I�����܂����H" , "�m�F" , MB_OKCANCEL );				// �I������̎擾

			if( nID == IDOK )
			{
				DestroyWindow( hWnd );
			}
			else
			{
				ShowCursor( FALSE );														// �J�[�\���̏���
				return 0;																	// ��I���̂��߁AWM_DESTROY�𑗂�Ȃ��悤�ɂ���
			}
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			break;
		}

		case WM_LBUTTONDOWN:
		{
			SetFocus( hWnd );
			break;
		}

		case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					PostMessage( hWnd , WM_CLOSE , 0 , 0 );
					break;

				default:
					break;
			}

			break;
		}

		case WM_COMMAND:
		{
			//pMenuBar = CModelViewerProc::GetModelViewerProc()->GetMenu();
			//pMenuBar->OperateMenu( wParam );
			break;
		}

		case WM_CREATE:
		{
			// �R�����R���g���[��������
			//InitCommonControls();
			//
			//// �X�e�[�^�X�o�[����
			//CModelViewerProc::GetModelViewerProc()->MV_CreateStatusBar( hWnd );
			//
			//// �c�[���o�[����
			//CModelViewerProc::GetModelViewerProc()->MV_CreateToolBar( hWnd );
			//
			//// ���j���[�o�[�n���h���擾
			//CModelViewerProc::GetModelViewerProc()->GetMenu()->SetHandle( GetMenu( hWnd ) );

			break;
		}

		case WM_SIZE:
		{
			// �R�����R���g���[���̃T�C�Y����
			//SendMessage( CModelViewerProc::GetModelViewerProc()->GetStatusBar()->GetHandle() , uMsg , wParam , lParam );
			//SendMessage( CModelViewerProc::GetModelViewerProc()->GetToolBar()->GetHandle() , uMsg , wParam , lParam );
			break;
		}

		default:
		{
			break;
		}
	}

	return DefWindowProc( hWnd , uMsg , wParam , lParam );
}

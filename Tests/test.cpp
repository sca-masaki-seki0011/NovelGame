#include "DxLib.h"
#include "select.h"
#include "graphic.h"
#include "script.h"
#include "message.h"

#define GAME_WINDOW_WIDTH 800
#define GAME_WINDOW_HEIGHT 600

#define SCRIPT_FILENAME "./script.txt"
#define GRAPHIC_BACKGROUND_FILENAME "./pic/back.png"

//�X�N���v�g�t�@�C��
ScriptInformation g_script;

//�O��}�E�X���N���b�N���ꂽ����
int g_mouseClickedTime;

//�v���g�^�C�v�錾
void initGame();

//������
void initGame()
{
	// �`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	//�t�H���g�̑傫�����Z�b�g
	SetFontSize(FONT_SIZE);

	// �}�E�X��\����Ԃɂ���
	SetMouseDispFlag(TRUE);

	//�I���{�b�N�X�̏�����
	initSelectBox();

	//�O���t�B�b�N�m�[�h������
	initGraphicNode();

	//���b�Z�[�W�{�b�N�X������
	initMessage();

	//�X�N���v�g���[�h
	loadScript(SCRIPT_FILENAME, &g_script);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);
	//��ʂ̑傫����800 * 600
	SetGraphMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, 16);
	//DxLib������
	if (DxLib_Init() == -1) {
		return -1;
	}

	//�Q�[��������
	initGame();

	//���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		//��ʃN���A
		ClearDrawScreen();

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			//�}�E�X�������ςȂ��̎��ɃX�N���v�g���ǂ�ǂ�i�܂Ȃ��悤�ɂ���
			if (GetNowCount() - g_mouseClickedTime > 500) {
				//�L�[���͑҂�������
				unsetWaitKeyInput();
				//�}�E�X�N���b�N�������Ԃ��擾
				g_mouseClickedTime = GetNowCount();
			}
		}
		//�I���{�b�N�X�������ꂽ���ǂ���
		checkSelectBoxClicked(&g_script);

		//�X�N���v�g����̉��
		if (getWaitKeyInput() != WAIT_UNTIL_KEY_INPUT &&
			getWaitSelectBoxInput() != WAIT_UNTIL_KEY_INPUT) {
			decodeScript(g_script.script[g_script.currentLine], &g_script);
			g_script.currentLine++;
		}

		//�摜�`��
		drawVisibleGraphic();
		//�I�����{�b�N�X�̕`��
		drawSelectBox();
		//���b�Z�[�W�`��
		drawMessage();

		Sleep(50);

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}

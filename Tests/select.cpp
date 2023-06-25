#include "select.h"

//�I�����{�b�N�X�֌W(�I������2�Ƃ���)
//��
int g_whiteColor;
//�I���{�b�N�X�̓ǂݍ���
int g_selectBoxGraphicHandle;
//�I���{�b�N�X�ɕ\�����郁�b�Z�[�W
char g_selectBoxMessage[2][SELECT_BOX_MESSAGE_MAX_LENGTH];
//�I���{�b�N�X��\�����邩�ǂ��� 0:��\�� 1:�\��
int g_selectBoxVisibleFlag;


//�I���{�b�N�X�̏�����
void initSelectBox()
{
	//��
	g_whiteColor = GetColor(255, 255, 255);
	//�I���{�b�N�X�̓ǂݍ���
	g_selectBoxGraphicHandle = LoadGraph(GRAPHIC_SELECTBOX_FILENAME);
	//�I���{�b�N�X�̃��b�Z�[�W������
	memset(g_selectBoxMessage[0], 0, SELECT_BOX_MESSAGE_MAX_LENGTH);
	memset(g_selectBoxMessage[1], 0, SELECT_BOX_MESSAGE_MAX_LENGTH);
	//�I���{�b�N�X��\�����Ȃ�
	g_selectBoxVisibleFlag = SELECT_BOX_HIDE;
}


//�w�肵���{�b�N�X���Ƀ}�E�X�����݂��邩�ǂ���
//�߂�l 1:���݂��� 0:���݂��Ȃ�
int isContainMousePointer(int x, int y, int width, int height)
{
	int mouseX, mouseY;

	//�}�E�X�̍��W���擾
	GetMousePoint(&mouseX, &mouseY);

	//�{�b�N�X���Ƀ}�E�X���W�����݂��邩
	if ((mouseX >= x && mouseX <= x + width) &&
		(mouseY >= y && mouseY <= y + height)) {
		return 1;
	}
	return 0;
}

//�I���{�b�N�X�Ƀ��b�Z�[�W���Z�b�g����
void setSelectBoxMessage(const char* message1, const char* message2)
{
	//���b�Z�[�W�Z�b�g
	strncpy_s(g_selectBoxMessage[0], message1, SELECT_BOX_MESSAGE_MAX_LENGTH);
	strncpy_s(g_selectBoxMessage[1], message2, SELECT_BOX_MESSAGE_MAX_LENGTH);
	//�I���{�b�N�X��\��
	g_selectBoxVisibleFlag = SELECT_BOX_SHOW;
}

//�I�����{�b�N�X��`�悷��
void drawSelectBox()
{
	//�I���{�b�N�X��\�����邩�ǂ���
	if (g_selectBoxVisibleFlag) {
		//�I�����{�b�N�X1���}�E�X�|�C���^���܂�ł����ꍇ
		if (isContainMousePointer(SELECT_BOX_X, SELECT_BOX_Y,
			SELECT_BOX_WIDTH, SELECT_BOX_HEIGHT)) {
			//�����x0���Ƃ���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		else {
			//�����x50%�Ƃ���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		}
		//�I���{�b�N�X�̕`��
		DrawGraph(SELECT_BOX_X, SELECT_BOX_Y, g_selectBoxGraphicHandle, TRUE);

		//�I�����{�b�N�X2���}�E�X�|�C���^���܂�ł����ꍇ
		if (isContainMousePointer(SELECT_BOX_X, SELECT_BOX_Y + SELECT_BOX_HEIGHT,
			SELECT_BOX_WIDTH, SELECT_BOX_HEIGHT)) {
			//�����x0���Ƃ���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		else {
			//�����x50%�Ƃ���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		}
		//�I���{�b�N�X2�ڂ̕`��
		DrawGraph(SELECT_BOX_X, SELECT_BOX_Y + SELECT_BOX_HEIGHT,
			g_selectBoxGraphicHandle, TRUE);

		//�A���t�@�u�����h�����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//���b�Z�[�W�\��
		DrawString(SELECT_BOX_X + 20, SELECT_BOX_Y + SELECT_BOX_MESSAGE_Y,
			g_selectBoxMessage[0], g_whiteColor);
		DrawString(SELECT_BOX_X + 20, SELECT_BOX_Y + SELECT_BOX_HEIGHT + SELECT_BOX_MESSAGE_Y,
			g_selectBoxMessage[1], g_whiteColor);
	}
}

//�I�����{�b�N�X���N���b�N���ꂽ���ǂ���
//0: �N���b�N����Ă��Ȃ� 1: �I����1���N���b�N���ꂽ 2: �I����2���N���b�N���ꂽ
int isClickedSelectBox()
{
	//�I�����{�b�N�X���\������Ă���Ƃ�
	if (g_selectBoxVisibleFlag) {
		//�}�E�X�̏�Ԃ𒲂ׂ�
		//���N���b�N���ꂽ�Ƃ�
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			if (isContainMousePointer(SELECT_BOX_X, SELECT_BOX_Y,
				SELECT_BOX_WIDTH, SELECT_BOX_HEIGHT)) {
				//�I�����{�b�N�X1���}�E�X�|�C���^���܂�ł����ꍇ
				//�I���{�b�N�X�̃��b�Z�[�W������
				memset(g_selectBoxMessage[0], 0, SELECT_BOX_MESSAGE_MAX_LENGTH);
				memset(g_selectBoxMessage[1], 0, SELECT_BOX_MESSAGE_MAX_LENGTH);
				//�I���{�b�N�X��\�����Ȃ�
				g_selectBoxVisibleFlag = SELECT_BOX_HIDE;
				//�I����1���N���b�N����Ă��邱�Ƃ�ʒm
				return 1;
			}
			else if (isContainMousePointer(SELECT_BOX_X,
				SELECT_BOX_Y + SELECT_BOX_HEIGHT,
				SELECT_BOX_WIDTH, SELECT_BOX_HEIGHT)) {
				//�I�����{�b�N�X2���}�E�X�|�C���^���܂�ł����ꍇ
				//�I���{�b�N�X�̃��b�Z�[�W������
				memset(g_selectBoxMessage[0], 0, SELECT_BOX_MESSAGE_MAX_LENGTH);
				memset(g_selectBoxMessage[1], 0, SELECT_BOX_MESSAGE_MAX_LENGTH);
				//�I���{�b�N�X��\�����Ȃ�
				g_selectBoxVisibleFlag = SELECT_BOX_HIDE;
				//�I����2���N���b�N����Ă��邱�Ƃ�ʒm
				return 2;
			}
		}
	}
	return 0;
}

#include "message.h"

//�\�����������b�Z�[�W
char g_message[MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE];

//��ʂɃ��b�Z�[�W��\������ۂɂ��悤���鉼�z�e�L�X�g�o�b�t�@
char g_messageBuffer[MESSAGE_MAX_LINE][MESSAGE_MAX_LENGTH];

//���b�Z�[�W�{�b�N�X�֌W

//���݉������ڂ܂ł�\�����Ă��邩
static int g_currentCursor = 0;
//���s�ڂ̕�����\�����Ă��邩
static int g_currentLineCursor = 0;
//��
static int g_whiteColor;
//��
static int g_blackColor;
//���b�Z�[�W�{�b�N�X�̉摜
static int g_messageBoxGraphicHandle;


//code �����{��ł��邩���肷��
//�߂�l 1:���{�� 0:���{��ł͂Ȃ�
int isJapaneseCharacter(unsigned char code)
{
	if ((code >= 0x81 && code <= 0x9F) ||
		(code >= 0xE0 && code <= 0xFC)) {
		return 1;
	}
	return 0;
}


//message�Ŏw�肵�����͂� start �̈ʒu���� len �������\������
void writeSubstring(char* message, int start, int len, int posX, int posY, int color, int bufferLine)
{
	int i;
	//������
	int maxLen = strlen(message);

	//start�̈ʒu��ύX����
	//start�̈ʒu�܂łɓ��{�ꂪ�łĂ��Ă�����C1�𑫂��Ă���
	for (i = 0; i < start && message[i] != '\0'; ) {
		if (isJapaneseCharacter(message[i])) {
			//���{��̏ꍇ�C2�o�C�g�������߂�
			i += 2;
			//start��1�o�C�g������
			start++;
		}
		else {
			//���p�����̏ꍇ�C1�o�C�g���i�߂�
			i++;
		}
	}

	//start�̈ʒu���\���������ő啶�������傫���ꍇ
	if (start >= maxLen) {
		return;
	}

	//�w�肵���ʒu����len�������\������
	for (i = 0; i < len && message[start + i] != '\0'; ) {
		if (isJapaneseCharacter(message[start + i])) {
			//���{��̏ꍇ�C2������buffer�ɃZ�b�g
			g_messageBuffer[bufferLine][i] = message[start + i];
			g_messageBuffer[bufferLine][i + 1] = message[start + i + 1];
			//len�͓��{��Ȃ̂ŁC1�o�C�g���ǉ�����
			len++;
			//2�o�C�g���i�߂�
			i += 2;
		}
		else {
			//���p����1�������Z�b�g
			g_messageBuffer[bufferLine][i] = message[start + i];
			//1�o�C�g���i�߂�
			i++;
		}
	}
	g_messageBuffer[bufferLine][i] = '\0';

	//���b�Z�[�W�`��
	DrawString(posX, posY, g_messageBuffer[bufferLine], color);
}


//���b�Z�[�W�`��
void drawMessage()
{
	

	//������1�������Z�b�g����Ă��Ȃ������烁�b�Z�[�W�{�b�N�X��\�����Ȃ�
	if (strnlen(g_message, MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE) <= 0) {
		return;
	}

	//���b�Z�[�W�{�b�N�X�`��
	DrawGraph(MESSAGE_BOX_X_POS, MESSAGE_BOX_Y_POS, g_messageBoxGraphicHandle, FALSE);

	if (g_message[g_currentCursor] != '\0') {
		g_currentCursor++;
	}

	//MESSAGE_MAX_LENGTH �܂ŕ�����`�悵����i����؂�ւ���
	if (g_currentCursor % MESSAGE_MAX_LENGTH == 0) {
		if (g_message[g_currentCursor] != '\0') {
			g_currentLineCursor++;
		}
	}

	//���b�Z�[�W�`�敔��
	for (int i = 0; i < MESSAGE_MAX_LINE; i++) {
		if (i == g_currentLineCursor) {
			//���b�Z�[�W���ɕ\��
			writeSubstring(g_message, i * MESSAGE_MAX_LENGTH, g_currentCursor - MESSAGE_MAX_LENGTH * i,
				MESSAGE_BOX_X_POS + 15, MESSAGE_BOX_Y_POS + MESSAGE_FONT_SIZE * i + 15, g_blackColor, i);
			break;
		}
		else {
			//���b�Z�[�W�����̂܂ܕ\��
			writeSubstring(g_message, i * MESSAGE_MAX_LENGTH, MESSAGE_MAX_LENGTH, MESSAGE_BOX_X_POS + 15,
				MESSAGE_BOX_Y_POS + MESSAGE_FONT_SIZE * i + 15, g_blackColor, i);
		}
	}
}

//����������
void initMessage()
{
	//��
	g_whiteColor = GetColor(255, 255, 255);
	//��
	g_blackColor = GetColor(0, 0, 0);
	//���b�Z�[�W�{�b�N�X
	g_messageBoxGraphicHandle = LoadGraph(MESSAGE_BOX_GRAPHIC_FILENAME);
}

//�`�悵�������b�Z�[�W���Z�b�g
void setMessage(const char* message)
{
	//�J�[�\����������
	g_currentCursor = 0;
	g_currentLineCursor = 0;

	//���b�Z�[�W���R�s�[
	strncpy_s(g_message, message, MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE);
}





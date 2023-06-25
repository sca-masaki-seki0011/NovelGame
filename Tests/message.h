#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "DxLib.h"

//���ӓ_�F�����R�[�h��SHIFT_JIS�iWindows�W���j��O��Ƃ��Ă���
//		  ���̕����R�[�h�ł͐���ɓ��삵�Ȃ�
//SHIFT_JIS�̏ꍇ�C���{���2�o�C�g�ŕ\�����
//��ʃo�C�g��0x81�`0x9F�A0xE0�`0xFC�͈̔͂Ɏ��܂�

int isJapaneseCharacter(unsigned char code);
void writeSubstring(char* message, int start, int len, int posX, int posY, int color, int bufferLine);
void drawMessage();
void initMessage();
void setMessage(const char* message);

//���b�Z�[�W�̃t�H���g�̑傫��
#define MESSAGE_FONT_SIZE 16
//���z�o�b�t�@�̍ő啶����
#define MESSAGE_MAX_LENGTH 30
//���z�o�b�t�@�̍ő�s��
#define MESSAGE_MAX_LINE 5
//���b�Z�[�W�{�b�N�X��X���W
#define MESSAGE_BOX_X_POS 100
//���b�Z�[�W�{�b�N�X��Y���W
#define MESSAGE_BOX_Y_POS 450

//���b�Z�[�W�{�b�N�X�̉摜
#define MESSAGE_BOX_GRAPHIC_FILENAME "./Pic/boxd3.jpg"

//�\�����������b�Z�[�W
extern char g_message[MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE];

//��ʂɃ��b�Z�[�W��\������ۂɂ��悤���鉼�z�e�L�X�g�o�b�t�@
extern char g_messageBuffer[MESSAGE_MAX_LINE][MESSAGE_MAX_LENGTH];

#endif
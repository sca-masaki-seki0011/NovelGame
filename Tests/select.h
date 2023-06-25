#ifndef SELECT_H_
#define SELECT_H_

#include "DxLib.h"

#define GRAPHIC_SELECTBOX_FILENAME  "./pic/select.png"

#define SELECT_BOX_X 50
#define SELECT_BOX_Y 200

#define SELECT_BOX_WIDTH 700
#define SELECT_BOX_HEIGHT 50

#define SELECT_BOX_MESSAGE_Y 20

//�t�H���g�T�C�Y��16�Ƃ���
#define FONT_SIZE 16

#define SELECT_BOX_MESSAGE_MAX_LENGTH 100
#define SELECT_BOX_HIDE 0
#define SELECT_BOX_SHOW 1

//�I�����{�b�N�X�֌W(�I������2�Ƃ���)
//��
extern int g_whiteColor;
//�I���{�b�N�X�̓ǂݍ���
extern int g_selectBoxGraphicHandle;
//�I���{�b�N�X�ɕ\�����郁�b�Z�[�W
extern char g_selectBoxMessage[2][SELECT_BOX_MESSAGE_MAX_LENGTH];
//�I���{�b�N�X��\�����邩�ǂ��� 0:��\�� 1:�\��
extern int g_selectBoxVisibleFlag;

//�v���g�^�C�v�錾
void initSelectBox();
int isContainMousePointer(int x, int y, int width, int height);
void drawSelectBox();
void setSelectBoxMessage(const char* message1, const char* message2);
int isClickedSelectBox();


#endif

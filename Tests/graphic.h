#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include "DxLib.h"

//�O���t�B�b�N���Ǘ�
typedef struct GraphicNode_tag {
	int id;			//�摜��id ���p���Ă��Ȃ��ꍇ��0���Z�b�g����Ă���
	int graphicHandle; //�摜�̃O���t�B�b�N�n���h��
} GraphicNode;

//��ʂɕ\������O���t�B�b�N���Ǘ�
typedef struct VisibleGraphicNode_tag {
	int graphicId; //�摜��id GraphicNode��id�Ƃ͕ʕ��Ȃ̂Œ��� 
				//���p���Ă��Ȃ��ꍇ��0���Z�b�g����Ă���
	int graphicHandle; //�摜�̃O���t�B�b�N�n���h��
	int x, y; //�\��������W
	int bright; //�P�x
	int mode; //�摜�`�惂�[�h 0:�P�x�ω����� 1:�t�F�[�h�C�� 2:�t�F�[�h�A�E�g
} VisibleGraphicNode;


//�O���t�B�b�N�̍ő�o�^��
#define GRAPHIC_MAX_NUM 3
//��ʂɕ\���ł���ő�̉摜��
#define VISIBLE_GRAPHIC_MAX_NUM 10
//�t�F�[�h�C���E�t�F�[�h�A�E�g�̃X�s�[�h
#define GRAPHIC_FADEIN_FADEOUT_SPEED 10
//�P�x�̍ő�l
#define GRAPHIC_MAX_BRIGHT 255
//�摜�`�惂�[�h
#define GRAPHIC_MODE_NONE 0
#define GRAPHIC_MODE_FADEIN 1
#define GRAPHIC_MODE_FADEOUT 2

//�O���t�B�b�N�Ǘ�
extern GraphicNode g_graphicManager[GRAPHIC_MAX_NUM];

//�\������O���t�B�b�N�̊Ǘ�
extern VisibleGraphicNode g_visibleGraphic[VISIBLE_GRAPHIC_MAX_NUM];

//�v���g�^�C�v�錾
void initGraphicNode();
int addGraphicNode(int id, const char* graphFilename);
int getGraphicHandle(int id);

int addVisibleGraphic(int id, int graphicId, int posX, int posY);
void drawVisibleGraphic();
int removeVisibleGraphic(int graphicId);

#endif

#include "graphic.h"

//�O���t�B�b�N�Ǘ�
GraphicNode g_graphicManager[GRAPHIC_MAX_NUM];

//�\������O���t�B�b�N�̊Ǘ�
VisibleGraphicNode g_visibleGraphic[VISIBLE_GRAPHIC_MAX_NUM];

//������
void initGraphicNode()
{
	//�O���t�B�b�N�Ǘ�������
	memset(&g_graphicManager, 0, sizeof(GraphicNode) * GRAPHIC_MAX_NUM);
	//�\������O���t�B�b�N�̊Ǘ�������
	memset(&g_visibleGraphic, 0, sizeof(VisibleGraphicNode) * VISIBLE_GRAPHIC_MAX_NUM);
}

//�O���t�B�b�N��ǂݍ���
//�߂�l -1: ���s 0: ����
int addGraphicNode(int id, const char* graphFilename)
{
	int i;
	//id���d�����Ă��Ȃ����m�F
	for (i = 0; i < GRAPHIC_MAX_NUM; i++) {
		if (id == g_graphicManager[i].id) {
			printf("id���d�����Ă��܂�(id %d)\n", id);
			return -1;
		}
	}

	//���p���Ă��Ȃ��m�[�h��������
	for (i = 0; i < GRAPHIC_MAX_NUM; i++) {
		if (g_graphicManager[i].id == 0) {
			break;
		}
	}
	//�O���t�B�b�N�m�[�h�̋󂫂��Ȃ�
	if (i == GRAPHIC_MAX_NUM) {
		printf("�O���t�B�b�N�m�[�h�̋󂫂�����܂���(id %d)\n", id);
		return -1;
	}

	//�摜�ǂݍ���
	g_graphicManager[i].graphicHandle = LoadGraph(graphFilename);

	//�ǂݍ��ݎ��s��
	if (g_graphicManager[i].graphicHandle == -1) {
		printf("�摜�ǂݍ��݂Ɏ��s���܂���(id %d)\n", id);
		g_graphicManager[i].graphicHandle = 0;
		return -1;
	}

	//id���Z�b�g
	g_graphicManager[i].id = id;
	return 0;
}

//id����O���t�B�b�N�n���h�����擾����
int getGraphicHandle(int id)
{
	int i = 0;
	for (i = 0; i < GRAPHIC_MAX_NUM; i++) {
		if (id == g_graphicManager[i].id) {
			return g_graphicManager[i].graphicHandle;
		}
	}
	return -1;
}


//��ʂɉ摜��\������
//id�ɂ�GraphicNode��id���w��C graphicId�͂��܂���`�悷��摜��id��t����
//posX, posY�͉摜��\������ʒu
//�߂�l -1: ���s 0: ����
int addVisibleGraphic(int id, int graphicId, int posX, int posY)
{
	int i;
	//id����O���t�B�b�N�n���h�����擾
	int handle = getGraphicHandle(id);

	//graphicHandle�̎擾���s
	if (handle == -1) {
		printf("ID: %d �̉摜�͓o�^����Ă��܂���\n", id);
		return -1;
	}

	//graphicId���d�����Ă��Ȃ����m�F
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++) {
		if (graphicId == g_visibleGraphic[i].graphicId) {
			printf("graph id���d�����Ă��܂�(id %d)\n", graphicId);
			return -1;
		}
	}

	//���p���Ă��Ȃ��m�[�h��������
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++) {
		if (g_visibleGraphic[i].graphicId == 0) {
			break;
		}
	}

	//�m�[�h�̋󂫂��Ȃ�
	if (i == VISIBLE_GRAPHIC_MAX_NUM) {
		printf("��ʂɂ���ȏ�摜��\���ł��܂���(id %d)\n", graphicId);
		return -1;
	}

	//���o�^
	//�O���t�B�b�N�n���h���o�^
	g_visibleGraphic[i].graphicHandle = handle;
	//graphicId��o�^
	g_visibleGraphic[i].graphicId = graphicId;
	//���W��o�^
	g_visibleGraphic[i].x = posX;
	g_visibleGraphic[i].y = posY;
	//�P�x���o�^
	g_visibleGraphic[i].bright = 0;
	//���[�h
	g_visibleGraphic[i].mode = GRAPHIC_MODE_FADEIN;

	return 0;
}

//�w�肵��graphicId�̉摜���폜����
//�߂�l -1: ���s 0:����
int removeVisibleGraphic(int graphicId)
{
	int i;
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++) {
		if (graphicId == g_visibleGraphic[i].graphicId) {
			//�w�肵���O���t�B�b�N����������
			//���[�h���t�F�[�h�A�E�g�Ƃ���
			g_visibleGraphic[i].mode = GRAPHIC_MODE_FADEOUT;
			return 0;
		}
	}
	return -1;
}


//�摜�`��
void drawVisibleGraphic()
{
	int i;
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++) {
		//graphicId��0�łȂ���΁i�摜�����݂����)
		if (g_visibleGraphic[i].graphicId != 0) {

			//�t�F�[�h�C�����s���Ƃ�
			if (g_visibleGraphic[i].mode == GRAPHIC_MODE_FADEIN) {
				//�P�x���グ��
				g_visibleGraphic[i].bright += GRAPHIC_FADEIN_FADEOUT_SPEED;
				if (g_visibleGraphic[i].bright > GRAPHIC_MAX_BRIGHT) {
					//�P�x���ő�l�ɒB������
					g_visibleGraphic[i].bright = GRAPHIC_MAX_BRIGHT;
					//�t�F�[�h�C������
					g_visibleGraphic[i].mode = GRAPHIC_MODE_NONE;
				}
			}

			//�t�F�[�h�A�E�g���s���Ƃ�
			if (g_visibleGraphic[i].mode == GRAPHIC_MODE_FADEOUT) {
				//�P�x��������
				g_visibleGraphic[i].bright -= GRAPHIC_FADEIN_FADEOUT_SPEED;
				if (g_visibleGraphic[i].bright <= 0) {
					//�摜����ʂ������
					g_visibleGraphic[i].graphicHandle = 0;
					g_visibleGraphic[i].graphicId = 0;
					g_visibleGraphic[i].x = 0;
					g_visibleGraphic[i].y = 0;
					g_visibleGraphic[i].bright = 0;
					g_visibleGraphic[i].mode = GRAPHIC_MODE_NONE;
					continue;
				}
			}

			//�P�x�Z�b�g
			SetDrawBright(g_visibleGraphic[i].bright,
				g_visibleGraphic[i].bright, g_visibleGraphic[i].bright);
			//�A���t�@�u�����h���s��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_visibleGraphic[i].bright);

			//�w�肵�����W�ɉ摜�`��
			DrawGraph(g_visibleGraphic[i].x, g_visibleGraphic[i].y,
				g_visibleGraphic[i].graphicHandle, TRUE);
		}
	}
	//�P�x�����f�t�H���g�ɖ߂��Ă���
	SetDrawBright(GRAPHIC_MAX_BRIGHT, GRAPHIC_MAX_BRIGHT, GRAPHIC_MAX_BRIGHT);
	//�u�����h���[�h�����ɂ��ǂ��Ă���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, GRAPHIC_MAX_BRIGHT);
}

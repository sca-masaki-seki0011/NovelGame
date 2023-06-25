#include "script.h"
#include "select.h"
#include "graphic.h"
#include "message.h"

//�L�[���͑҂����ǂ��� 1:���͑҂� 0:���͑҂��ł͂Ȃ�
int g_waitKeyInput;
//�I���{�b�N�X�I��҂�
int g_waitSelectBoxInput;
//��������Ɏg��
char* g_select[10][2];

//�L�[���͑҂���Ԃɂ���
void setWaitKeyInput()
{
	g_waitKeyInput = WAIT_UNTIL_KEY_INPUT;
}

//�L�[���͑҂���Ԃ�����
void unsetWaitKeyInput()
{
	g_waitKeyInput = NO_WAIT;
}

//�L�[���͑҂���Ԃ����擾
int getWaitKeyInput()
{
	return g_waitKeyInput;
}

//�I���{�b�N�X�I��҂���Ԃɂ���
void setWaitSelectBoxInput()
{
	g_waitSelectBoxInput = WAIT_UNTIL_KEY_INPUT;
}

//�I���{�b�N�X�̏�Ԃ��擾
int getWaitSelectBoxInput()
{
	return g_waitSelectBoxInput;
}

//�I���{�b�N�X���N���b�N���ꂽ�Ƃ��̏���
void checkSelectBoxClicked(ScriptInformation* scriptInfo)
{
	int choice, line;

	if (getWaitSelectBoxInput() == NO_WAIT) {
		return;
	}

	//�ǂ̑I���{�b�N�X���N���b�N���ꂽ��
	choice = isClickedSelectBox();
	if (choice == 0) {
		//�ǂ����N���b�N����Ă��Ȃ�
		return;
	}

	//���x�������s�ڂɂ��邩���擾
	line = searchScriptLabel(g_select[choice - 1][1], scriptInfo);
	//�w�肵�����x����������Ȃ�����
	if (line == -1) {
		printf("�X�N���v�g�G���[:��������̎w�胉�x�����Ԉ���Ă��܂�(%d�s��)\n",
			scriptInfo->currentLine + 1);
		return;
	}
	//�ǂݎ�蒆�̍s�ԍ������x���̍s�Ɉړ�
	scriptInfo->currentLine = line;

	//���͑҂�����
	g_waitSelectBoxInput = NO_WAIT;
}


//�I���{�b�N�X��

//�X�N���v�g�t�@�C����ǂݍ���
//�߂�l -1 : ���s  0 : ����
int loadScript(const char* filename, ScriptInformation* scriptInfo)
{
	int pos;
	char c;
	//�X�N���v�g�t�@�C��
	FILE* fp;

	//�X�N���v�g����������
	memset(scriptInfo, 0, sizeof(ScriptInformation));

	//�X�N���v�g�t�@�C�����J��
	fp = fopen(filename, "r");
	if (fp == NULL) {
		//�t�@�C���ǂݍ��݂Ɏ��s
		printf("�X�N���v�g %s ��ǂݍ��߂܂���ł���\n", filename);
		return -1;
	}

	//script�������ݎ��Ɏg�p
	pos = 0;

	for (;; ) {
		//�ꕶ���ǂݍ���
		c = fgetc(fp);
		//�t�@�C���̏I��肩�ǂ���
		if (feof(fp)) {
			break;
		}
		//���͐擪�̋󔒕�����ǂݔ�΂�
		while ((c == ' ' || c == '\t') && pos == 0 && !feof(fp)) {
			c = fgetc(fp);
		}

		if (pos >= SCRIPT_MAX_STRING_LENGTH - 1) {
			//1�s�̕���������������
			printf("error: ���������������܂� (%d�s��)", scriptInfo->currentLine);
			return -1;
		}

		//���s�������o�Ă����ꍇ�C���̍s�ֈړ�
		if (c == '\n') {
			//��s�͓ǂݔ�΂�
			if (pos == 0) {
				continue;
			}
			//\0�𕶎���̍Ō�ɕt����
			scriptInfo->script[scriptInfo->currentLine][pos] = '\0';
			//���̍s�Ɉړ�
			scriptInfo->currentLine++;
			//�������݈ʒu��0�ɂ���
			pos = 0;
		}
		else {
			//��������
			scriptInfo->script[scriptInfo->currentLine][pos] = c;
			//�����������݈ʒu�����炷
			pos++;
		}
	}
	//�ő�s��
	scriptInfo->maxLineNumber = scriptInfo->currentLine;
	//�ǂݍ��ݒ��̍s��0�ɂ���
	scriptInfo->currentLine = 0;
	//�X�N���v�g�t�@�C������ݒ�
	scriptInfo->filename = filename;

	return 0;
}

//�����񕪊�(1�s�̍ő啶������ SCRIPT_MAX_STRING_LENGTH)
//src : ����������������
//dest: �������ꂽ������
//delim: ��؂蕶��
//splitNum : �ő啪����
void splitString(const char* src, char* dest[], const char* delim, int splitNum)
{
	int i;
	char* cp;
	char* copySrc;

	//���̕��͂��R�s�[����
	copySrc = (char*)malloc(sizeof(int) * SCRIPT_MAX_STRING_LENGTH + 1);
	strncpy(copySrc, src, SCRIPT_MAX_STRING_LENGTH);
	cp = copySrc;

	//strtok���g���� copySrc ��delim��؂�ŕ�������
	for (i = 0; i < splitNum; i++) {
		//�����Ώە����񂪖����Ȃ�܂ŕ���
		if ((dest[i] = strtok(cp, delim)) == NULL) {
			break;
		}
		//2��ڂ�strtok���Ăяo�����́Ccp��NULL�ɂ���
		cp = NULL;
	}
	//�������ꂽ������̍Ō�̗v�f��NULL�Ƃ��Ă���
	dest[i] = NULL;
}

//�f�o�b�O�p
//elem�̗v�f��\��
void printElements(char* elem[])
{
	int i;
	for (i = 0; elem[i] != NULL; i++) {
		printf("%d : %s\n", i + 1, elem[i]);
	}
}

//�X�N���v�g������ǂ���
//�߂�l 1: ����  0: ���s
int decodeScript(const char* scriptMessage, ScriptInformation* scriptInfo)
{
	int i, selectNum, line;
	//�������ꂽ�X�N���v�g��
	char* message[100];
	//��������p
	char* selectMessage[10];

	//�����񕪊����̋�؂蕶��
	const char* delim = " ";
	const char* selectDelim = "@@";

	//�X�N���v�g����
	splitString(scriptMessage, message, delim, 100);

	//�����Ɏ��s�����ꍇ
	if (message[0] == NULL) {
		return 0;
	}

	//message[0] �� @@message �̎��́C���b�Z�[�W���߂������Ɣ��f
	if (strncmp(message[0], "@@message", SCRIPT_MAX_STRING_LENGTH) == 0) {
		printf("���b�Z�[�W : %s\n", message[1]);
		setMessage(message[1]);
		setWaitKeyInput();
	}
	else if (strncmp(message[0], "@@addgraph", SCRIPT_MAX_STRING_LENGTH) == 0) {
		//�\������摜��o�^
		addVisibleGraphic(atoi(message[1]), atoi(message[2]),
			atoi(message[3]), atoi(message[4]));
	}
	else if (strncmp(message[0], "@@load", SCRIPT_MAX_STRING_LENGTH) == 0) {
		//�摜��o�^
		addGraphicNode(atoi(message[1]), message[2]);

	}
	else if (strncmp(message[0], "@@removegraph", SCRIPT_MAX_STRING_LENGTH) == 0) {
		//�摜���폜
		removeVisibleGraphic(atoi(message[1]));

	}
	else if (strncmp(message[0], "@@select", SCRIPT_MAX_STRING_LENGTH) == 0) {

		for (i = 0; message[i + 1] != NULL; i++) {
			//�������������͂ƃW�����v���x���Ƃɕ�����
			splitString(message[i + 1], selectMessage, selectDelim, 2);
			//��������
			g_select[i][0] = selectMessage[0];
			//���x��
			g_select[i][1] = selectMessage[1];
		}
		//����
		selectNum = i;

		//��������̐���2�ɌŒ� ����ȊO�̓G���[�Ƃ���
		if (selectNum != 2) {
			printf("�X�N���v�g�G���[:��������̕��򐔂��Ԉ���Ă��܂�(%d�s��) \n",
				scriptInfo->currentLine + 1);
			return 0;
		}
		//��������̃��b�Z�[�W���Z�b�g
		setSelectBoxMessage(g_select[0][0], g_select[1][0]);

		//�����ŕ���҂������������
		setWaitSelectBoxInput();

	}
	else if (strncmp(message[0], "@@goto", SCRIPT_MAX_STRING_LENGTH) == 0) {
		//���x�������s�ڂɂ��邩���擾
		line = searchScriptLabel(message[1], scriptInfo);
		//�w�肵�����x����������Ȃ�����
		if (line == -1) {
			printf("�X�N���v�g�G���[:�w�肵�����x����������܂���ł���(%d�s��)\n",
				scriptInfo->currentLine + 1);
			return 0;
		}
		//�ǂݎ�蒆�̍s�ԍ������x���̍s�Ɉړ�
		scriptInfo->currentLine = line;

	}
	else if (strncmp(message[0], "@@label", SCRIPT_MAX_STRING_LENGTH) == 0) {
		//���x���̏ꍇ�͂Ȃɂ����Ȃ�
	}
	else if (strncmp(message[0], "@@wait", SCRIPT_MAX_STRING_LENGTH) == 0) {
		setWaitKeyInput();
		//�L�[���͑҂�	
	}
	else {
		printf("�X�N���v�g�G���[(%d�s��)\n", scriptInfo->currentLine + 1);
		return 0;
	}
	return 1;
}

//�w�肵�����x��������s����T��
//�߂�l ���̐�: �w�肵�����x���̍s�ԍ� -1: �G���[
int searchScriptLabel(const char* label, ScriptInformation* scriptInfo)
{
	//�������ꂽ�X�N���v�g��
	char* message[100];
	//�����񕪊����̋�؂蕶��
	const char* delim = " ";
	int i, line = -1;

	for (i = 0; i < scriptInfo->maxLineNumber; i++) {
		//�X�N���v�g����
		splitString(scriptInfo->script[i], message, delim, 100);

		//�����Ɏ��s�����ꍇ
		if (message[0] == NULL) {
			return -1;
		}

		//�w�肵�����x����T��
		if (strncmp(message[0], "@@label", SCRIPT_MAX_STRING_LENGTH) == 0) {
			if (strncmp(message[1], label, SCRIPT_MAX_STRING_LENGTH) == 0) {
				//�w�肵�����x��������������
				line = i;
				break;
			}
		}
	}

	return line;
}
#ifndef SCRIPT_H_
#define SCRIPT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//�X�N���v�g�͍ő�1000�s�܂œǂݍ���
#define SCRIPT_MAX_LINE 1000
//�X�N���v�g�ő啶����
#define SCRIPT_MAX_STRING_LENGTH 300

//�L�[���͑҂�
#define WAIT_UNTIL_KEY_INPUT 1
#define NO_WAIT 0

typedef struct ScriptInformation_tag {
	int maxLineNumber;			//�X�N���v�g�s��
	int currentLine;			//���݉��s�ڂ����s���Ă��邩
	const char* filename;		//�t�@�C����
	char script[SCRIPT_MAX_LINE][SCRIPT_MAX_STRING_LENGTH];
} ScriptInformation;

//�L�[���͑҂����ǂ��� 1:���͑҂� 0:���͑҂��ł͂Ȃ�
extern int g_waitKeyInput;
//�I���{�b�N�X�I��҂�
extern int g_waitSelectBoxInput;
//��������Ɏg��
extern char* g_select[10][2];


//�v���g�^�C�v�錾
int loadScript(const char* filename, ScriptInformation* scriptInfo);
void splitString(const char* src, char* dest[], const char* delim, int splitNum);
void printElements(char* elem[]);
int decodeScript(const char* scriptMessage, ScriptInformation* scriptInfo);
int searchScriptLabel(const char* label, ScriptInformation* scriptInfo);
void setWaitKeyInput();
void unsetWaitKeyInput();
int getWaitKeyInput();
void setWaitSelectBoxInput();
int getWaitSelectBoxInput();
void checkSelectBoxClicked(ScriptInformation* scriptInfo);

#endif

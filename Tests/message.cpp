#include "message.h"

//表示したいメッセージ
char g_message[MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE];

//画面にメッセージを表示する際にしようする仮想テキストバッファ
char g_messageBuffer[MESSAGE_MAX_LINE][MESSAGE_MAX_LENGTH];

//メッセージボックス関係

//現在何文字目までを表示しているか
static int g_currentCursor = 0;
//何行目の文字を表示しているか
static int g_currentLineCursor = 0;
//白
static int g_whiteColor;
//黒
static int g_blackColor;
//メッセージボックスの画像
static int g_messageBoxGraphicHandle;


//code が日本語であるか判定する
//戻り値 1:日本語 0:日本語ではない
int isJapaneseCharacter(unsigned char code)
{
	if ((code >= 0x81 && code <= 0x9F) ||
		(code >= 0xE0 && code <= 0xFC)) {
		return 1;
	}
	return 0;
}


//messageで指定した文章を start の位置から len 文字分表示する
void writeSubstring(char* message, int start, int len, int posX, int posY, int color, int bufferLine)
{
	int i;
	//文字数
	int maxLen = strlen(message);

	//startの位置を変更する
	//startの位置までに日本語がでてきていたら，1を足していく
	for (i = 0; i < start && message[i] != '\0'; ) {
		if (isJapaneseCharacter(message[i])) {
			//日本語の場合，2バイト分すすめる
			i += 2;
			//startに1バイト分足す
			start++;
		}
		else {
			//半角文字の場合，1バイト分進める
			i++;
		}
	}

	//startの位置が表示したい最大文字数より大きい場合
	if (start >= maxLen) {
		return;
	}

	//指定した位置からlen文字分表示する
	for (i = 0; i < len && message[start + i] != '\0'; ) {
		if (isJapaneseCharacter(message[start + i])) {
			//日本語の場合，2文字分bufferにセット
			g_messageBuffer[bufferLine][i] = message[start + i];
			g_messageBuffer[bufferLine][i + 1] = message[start + i + 1];
			//lenは日本語なので，1バイト分追加する
			len++;
			//2バイト分進める
			i += 2;
		}
		else {
			//半角文字1文字をセット
			g_messageBuffer[bufferLine][i] = message[start + i];
			//1バイト分進める
			i++;
		}
	}
	g_messageBuffer[bufferLine][i] = '\0';

	//メッセージ描画
	DrawString(posX, posY, g_messageBuffer[bufferLine], color);
}


//メッセージ描画
void drawMessage()
{
	

	//文字が1文字もセットされていなかったらメッセージボックスを表示しない
	if (strnlen(g_message, MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE) <= 0) {
		return;
	}

	//メッセージボックス描画
	DrawGraph(MESSAGE_BOX_X_POS, MESSAGE_BOX_Y_POS, g_messageBoxGraphicHandle, FALSE);

	if (g_message[g_currentCursor] != '\0') {
		g_currentCursor++;
	}

	//MESSAGE_MAX_LENGTH まで文字を描画したら段落を切り替える
	if (g_currentCursor % MESSAGE_MAX_LENGTH == 0) {
		if (g_message[g_currentCursor] != '\0') {
			g_currentLineCursor++;
		}
	}

	//メッセージ描画部分
	for (int i = 0; i < MESSAGE_MAX_LINE; i++) {
		if (i == g_currentLineCursor) {
			//メッセージ風に表示
			writeSubstring(g_message, i * MESSAGE_MAX_LENGTH, g_currentCursor - MESSAGE_MAX_LENGTH * i,
				MESSAGE_BOX_X_POS + 15, MESSAGE_BOX_Y_POS + MESSAGE_FONT_SIZE * i + 15, g_blackColor, i);
			break;
		}
		else {
			//メッセージをそのまま表示
			writeSubstring(g_message, i * MESSAGE_MAX_LENGTH, MESSAGE_MAX_LENGTH, MESSAGE_BOX_X_POS + 15,
				MESSAGE_BOX_Y_POS + MESSAGE_FONT_SIZE * i + 15, g_blackColor, i);
		}
	}
}

//初期化処理
void initMessage()
{
	//白
	g_whiteColor = GetColor(255, 255, 255);
	//黒
	g_blackColor = GetColor(0, 0, 0);
	//メッセージボックス
	g_messageBoxGraphicHandle = LoadGraph(MESSAGE_BOX_GRAPHIC_FILENAME);
}

//描画したいメッセージをセット
void setMessage(const char* message)
{
	//カーソルを初期化
	g_currentCursor = 0;
	g_currentLineCursor = 0;

	//メッセージをコピー
	strncpy_s(g_message, message, MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE);
}





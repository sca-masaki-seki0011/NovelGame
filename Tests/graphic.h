#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include "DxLib.h"

//グラフィックを管理
typedef struct GraphicNode_tag {
	int id;			//画像のid 利用していない場合は0がセットされている
	int graphicHandle; //画像のグラフィックハンドル
} GraphicNode;

//画面に表示するグラフィックを管理
typedef struct VisibleGraphicNode_tag {
	int graphicId; //画像のid GraphicNodeのidとは別物なので注意 
				//利用していない場合は0がセットされている
	int graphicHandle; //画像のグラフィックハンドル
	int x, y; //表示する座標
	int bright; //輝度
	int mode; //画像描画モード 0:輝度変化無し 1:フェードイン 2:フェードアウト
} VisibleGraphicNode;


//グラフィックの最大登録数
#define GRAPHIC_MAX_NUM 3
//画面に表示できる最大の画像数
#define VISIBLE_GRAPHIC_MAX_NUM 10
//フェードイン・フェードアウトのスピード
#define GRAPHIC_FADEIN_FADEOUT_SPEED 10
//輝度の最大値
#define GRAPHIC_MAX_BRIGHT 255
//画像描画モード
#define GRAPHIC_MODE_NONE 0
#define GRAPHIC_MODE_FADEIN 1
#define GRAPHIC_MODE_FADEOUT 2

//グラフィック管理
extern GraphicNode g_graphicManager[GRAPHIC_MAX_NUM];

//表示するグラフィックの管理
extern VisibleGraphicNode g_visibleGraphic[VISIBLE_GRAPHIC_MAX_NUM];

//プロトタイプ宣言
void initGraphicNode();
int addGraphicNode(int id, const char* graphFilename);
int getGraphicHandle(int id);

int addVisibleGraphic(int id, int graphicId, int posX, int posY);
void drawVisibleGraphic();
int removeVisibleGraphic(int graphicId);

#endif

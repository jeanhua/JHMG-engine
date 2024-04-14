#pragma once
#include<easyx.h>
#include "jhClass.h"
#include<map>
using namespace std;

//音乐播放所需库
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

/*	
坐标系说明：
	坐标原点在设备的左上角，X 轴向右为正，Y 轴向下为正，度量单位是像素
*/

//putImg拓展
inline void putimagePNG(int x, int y, IMAGE* img) {
	DWORD* pwin = GetImageBuffer();//获取窗口缓冲区指针
	DWORD* pimg = GetImageBuffer(img);//获取图片缓冲区指针
	int win_w = getwidth();
	int win_h = getheight();
	int img_w = img->getwidth();
	int img_h = img->getheight();
	//判断x,y坐标是否超出了窗口的范围
	int real_w = (x + img_w > win_w) ? win_w - x : img_w;//超出右边界实际贴图的宽度
	int real_h = (y + img_h > win_h) ? win_h - y : img_h;//超出下边界
	if (x < 0) {//超出左边界处理
		pimg += -x;//让指针向后偏移
		real_w -= -x;
		x = 0;
	}
	if (y < 0) {//超出上边界处理
		pimg += (img_w * -y);//让指针向后偏移
		real_h -= -y;
		y = 0;
	}
	pwin += (win_w * y + x);

	for (int iy = 0; iy < real_h; iy++) {
		for (int ix = 0; ix < real_w; ix++) {
			UCHAR alpha = pimg[ix] >> 24;
			if (alpha > 200)//alpha  0 表示完全透明
			{
				pwin[ix] = pimg[ix];
			}
		}
		//换到下一行
		pwin += win_w;
		pimg += img_w;
	}
}

class gameObject;
class gameUI;
class gameSound;
class gameInput;
class Game;


//游戏对象类
class gameObject
{
	friend class Game;
public:
	//游戏对象
	union Transform
	{
		jhObject2D::circle* circle;
		jhObject2D::diamond* diamond;
		jhObject2D::rectangle* rectangle;
		jhObject2D::triangle* triangle;
	};
	Transform transform;
	char transformType;

	//游戏对象可视性
	bool visible;
	//构造函数
	gameObject(jhObject2D::circle* transform, LPCTSTR file,int width ,int height, bool visible = true);
	gameObject(jhObject2D::rectangle* transform, LPCTSTR file,int width ,int height, bool visible = true);
	gameObject(jhObject2D::diamond* transform, LPCTSTR file,int width ,int height, bool visible = true);
	gameObject(jhObject2D::triangle* transform, LPCTSTR file,int width ,int height, bool visible = true);
	//设置碰撞回调函数
	void setOnCollision(void (*onCollision)(gameObject* gameObject));
	

private:
	//游戏对象的图片
	IMAGE* image;
	//碰撞回调函数
	void (*onCollision)(gameObject* gameObject) = NULL;
};

//游戏界面类
class gameUI
{
	friend class Game;
private:
	//图片
	IMAGE* image;
public:
	//位置
	jhVector2 position;
	//大小
	jhVector2 size;
	//可视性
	bool visible;
	//构造函数
	gameUI(jhVector2 position, jhVector2 size, jhString image, bool visible = true);
};

//游戏音效类
class gameSound
{
public:
	//音效
	jhString music_file;
	//设置音乐文件
	void setSound(jhString music_file);
	//播放音效
	void play();
	//停止音效
	void stop();
	//暂停音效
	void pause();
	//继续音效
	void resume();
	//设置音量
	void setVolume(int volume);
	//获取音量
	int getVolume();
	//设置播放位置
	void setPosition(int position);
	//获取播放位置
	int getPosition();
	//获取音效长度
	int getLength();
	//获取音效状态
	int getState();
	//关闭音效
	void close();
	//析构函数
	~gameSound();
};

//键盘消息类
enum KeyMessage
{
	a =65,
	b =66,
	c =67,
	d =68,
	e =69,
	f =70,
	g =71,
	h =72,
	i =73,
	j =74,
	k =75,
	l =76,
	m =77,
	n =78,
	o =79,
	p =80,
	q =81,
	r =82,
	s =83,
	t =84,
	u =85,
	v =86,
	w =87,
	x =88,
	y =89,
	z =90,
	enter =13,
	space =32,
	esc =27,
};

//键盘输入类
class gameInput
{
	friend class Game;
private:
	ExMessage msg;
	char key;
	void getMessage();
public:
	//获取键盘输入
	char getKey();
};

//游戏类
class Game
{
private:
	//游戏窗口句柄
	HWND window;
	//游戏窗口大小
	jhVector2 windowSize= jhVector2(800, 600);
	//游戏窗口标题
	jhString windowTitle = "not define";
	//游戏物体
	jhList<gameObject*> gameObjects;
	//游戏界面
	jhList<gameUI*> gameUIs;
	//游戏帧率
	int targetFrame = 60;
	//游戏间隔
	long deltaTime;
	//游戏循环自定义函数
	void(*gameLoopFunc)() = NULL;
	//游戏音效
	gameSound Sound;
	//游戏物体map
	map<jhString,gameObject*> gameObjectsMap;
	//游戏界面map
	map<jhString,gameUI*> gameUIMap;
	//游戏循环
	void gameLoop();
public:
	//设置游戏窗口大小
	void setWindowSize(jhVector2 windowSize);
	//设置游戏窗口标题
	void setWindowTitle(jhString windowTitle);
	//设置循环函数
	void setGameLoopFunc(void(*func)());
	//初始化窗口,开始游戏
	void initWindow();
	//设置游戏帧率
	void setTargetFrame(int targetFrame);
	//获取游戏窗口大小
	jhVector2 getWindowSize();
	//获取游戏窗口标题
	jhString getWindowTitle();
	//添加游戏物体
	void addGameObject(jhString name,gameObject* gameObject);
	//删除游戏物体
	void removeGameObject(jhString name);
	//获取游戏物体
	gameObject* getGameObject(jhString name);
	//获取游戏对象名字
	jhString getName(gameObject* gameObject);
	//添加游戏界面
	void addGameUI(jhString name,gameUI* gameUI);
	//删除游戏界面
	void removeGameUI(jhString name);
	//获取游戏界面
	gameUI* getGameUI(jhString name);
	//键盘输入
	gameInput Input;
};
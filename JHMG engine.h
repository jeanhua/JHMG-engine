#ifndef JHMG_ENGINE_H
#define JHMG_ENGINE_H
#include "easyx.h"
#include<map>
#include<string>
#include<iostream>
#include<stdexcept>
#include<cmath>
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

/*
   自定义类：jhString类，jhFraction类，jhVector2类，jhList类，jhMatrix类，jhObject2D命名空间{transform类,circle类,rectangle类,triangle类,diamond类,trapezium类}
*/
#define PI 3.14
// 类的声明
class jhString;
class jhFraction;
class jhVector2;
template<class T> class jhList;
class jhMatrix;
namespace jhObject2D
{
	class transform;
	class circle;
	class rectangle;
	class triangle;
	class diamond;
	class trapezium;
};

//游戏各种类
class gameObject;
class gameUI;
class gameUIText;
class gameSound;
class gameInput;
class gameScene;
template<class T> class MouseAction;
class gameInputBox;
class gameMessageBox;
class Game;

//jhString类:字符串类型
class jhString
{
public:
	//友元类
	friend ostream& operator<<(ostream& cout, const jhString& str);
	friend istream& operator>>(istream& cin, const jhString& str);
	//构造函数
	jhString();
	jhString(const string& str);
	jhString(const char* str);
	jhString(const jhString& str);
	//运算符重载
	jhString operator+(const jhString& str);
	jhString operator+(const string& str);
	void operator=(const jhString& str);
	void operator=(const string& str);
	void operator+=(const jhString& str);
	void operator+=(const string& str);
	bool operator==(const jhString& str);
	bool operator<(const jhString& str)const;
	bool operator>(const jhString& str)const;
	//字符串转换为整型数据(如果可以)
	int to_int();
	//转换为char*
	char* to_char();
	//字符串转换为浮点型数据(如果可以)
	float to_float();
	//返回字符串索引，从0开始
	int indexOf(const string& str);
	//返回字符串索引，从0开始
	int indexOf(const jhString& str);
	//转换为std::string
	string to_stdString();
	//字符串截取，从起始位置截取到终点位置，从0开始
	string substr(int begin, int end);
	//字符串截取,从左边字符截取到右边字符(不包含边界)，若找不到左边，返回空；若找到左边，但找不到右边，返回左边到末尾
	string substr(const string& leftStr, const string& rightStr);
private:
	string str;
};
//jhFraction类:s/m分数类
class jhFraction
{
public:
	//友元类
	friend ostream& operator<<(ostream& cout, const jhFraction& num);
	friend istream& operator>>(istream& cin, jhFraction& num);
	//构造函数
	jhFraction();
	//拷贝构造函数
	jhFraction(const jhFraction& num);
	//构造函数
	jhFraction(int num);
	jhFraction(double num);
	jhFraction(int s, int m);
	//化简
	void simplify();
	//打印
	void print();
	//转换为浮点数
	float to_float();
	//加法运算符重载
	jhFraction operator+(const jhFraction& num);
	jhFraction operator+(float num);
	//加等于运算符重载
	jhFraction& operator+=(float num);
	jhFraction& operator+=(const jhFraction& num);
	//减法运算符重载
	jhFraction operator-(const jhFraction& num);
	jhFraction operator-(float num);
	//减等于运算符重载
	jhFraction& operator-=(const jhFraction& num);
	jhFraction& operator-=(float num);
	//乘法运算符重载
	jhFraction operator*(const jhFraction& num);
	jhFraction operator*(float num);
	//乘等于运算符重载
	jhFraction operator*=(float num);
	//等于运算符重载
	jhFraction operator=(const jhFraction& num);
	//除法运算符重载
	jhFraction operator/(const jhFraction& num);
	jhFraction operator/(float num);
	//除等于运算符重载
	jhFraction operator/=(float num);
	//比较运算符重载
	bool operator>(const jhFraction& num);
	bool operator>(float num);
	bool operator>=(const jhFraction& num);
	bool operator>=(float num);
	bool operator<(const jhFraction& num);
	bool operator<(float num);
	bool operator<=(const jhFraction& num);
	bool operator<=(float num);
	bool operator==(const jhFraction& num);
	bool operator==(float num);
private:
	int s, m;/* （s/m分数类型）*/
};
//jhVector2类：二维向量，坐标
class jhVector2
{
public:
	//友元类
	float x, y;
	//默认构造函数
	jhVector2();
	//构造函数
	jhVector2(float x, float y);
	//拷贝构造函数
	jhVector2(const jhVector2& v2);
	//赋值运算符重载
	jhVector2& operator=(const jhVector2& v2);
	//加法运算符重载
	jhVector2 operator+(const jhVector2& v2);
	//加等于运算符重载
	jhVector2& operator+=(const jhVector2& v2);
	//减法运算符重载
	jhVector2 operator-(const jhVector2& v2);
	//减等于运算符重载
	jhVector2& operator-=(const jhVector2& v2);
	//乘法运算符重载
	jhVector2 operator*(float i);
	//除法运算符重载
	jhVector2 operator/(float i);
	//判断是否相等
	bool operator==(const jhVector2& v2);
	//求坐标距离
	double destance(const jhVector2& objective);
	//求向量叉乘
	double cross_product(const jhVector2& objective);
	//求向量点乘
	double dot_product(const jhVector2& objective);
	//旋转
	void rotate(const jhVector2& center, float angle);
};
//jhList:链表模板类(无序链表)
template<class T>
class jhList
{
public:
	struct node
	{
		node* p_back = NULL;
		node* p_next = NULL;
		T value;
	};
	//链表头
	node* p_first;
	//在后面添加节点
	void addList(T value);
	//删除节点
	void deleteList(node* list);
	//默认构造函数
	jhList();
	//析构函数
	~jhList();
};
//jhMatrix类，矩阵类
class jhMatrix
{
private:

	float** matrix;
	int row, column;
	void init(int row, int column)
	{
		this->row = row;
		this->column = column;
		this->matrix = new float* [row];
		for (int i = 0; i < this->row; i++)
		{
			this->matrix[i] = new float[this->column];
		}
	}
public:

	// 默认构造函数
	jhMatrix(int row, int column);
	//用另一个矩阵构造
	jhMatrix(const jhMatrix& other);
	// jhVector2构造函数
	jhMatrix(const jhVector2& v2);
	// 二维数组转换的一维指针构造
	jhMatrix(float* other, int row, int column);
	// 析构函数
	~jhMatrix();
	// 设置矩阵值
	void setValue(int row, int column, float value);
	//打印矩阵
	void print(bool isFraction = false);
	// 取转置矩阵
	jhMatrix getTransposeMatrix();
	// 取逆矩阵
	jhMatrix getInverseMatrix();
	//取行列式
	float getDeterminant();
	// 交换行
	void swapRows(int row1, int row2);
	// 将某行所有元素除以一个数
	void divideRow(int row, float divisor);
	// 将一行加到另一行的倍数
	void addToRow(int sourceRow, int destRow, float multiple);
	// 矩阵运算
	jhMatrix operator+(const jhMatrix& other);
	jhMatrix operator-(const jhMatrix& other);
	jhMatrix operator*(const jhMatrix& other);
	jhMatrix operator*(float num);
	void operator=(const jhMatrix& other);
	bool operator==(const jhMatrix& other);
};

namespace jhObject2D
{
	// 声明类
	class transform;
	class circle;
	class rectangle;
	class triangle;
	class diamond;
	//类的实现
	// 物体基类
	class transform
	{
	public:

		//友元类
		friend class circle;
		friend class rectangle;
		friend class triangle;
		friend class diamond;
		// 默认构造函数
		transform();
		//拷贝构造函数
		transform(const transform& other);
		// 构造函数
		transform(jhVector2 position);
		//移动
		virtual void move(jhVector2 dest) = 0;
		//获取当前位置
		virtual jhVector2 getPosition();
		// 计算面积
		virtual float getAreaSize() = 0;
		// 计算距离
		float getDistance(const transform& other);
		//获取左上角坐标
		virtual jhVector2 getLeftTopPosition() = 0;
		// 判断是否在三角形内
		virtual bool isTriggerEnter(const triangle& other) = 0;
		// 判断是否在矩形内
		virtual bool isTriggerEnter(const rectangle& other) = 0;
		// 判断是否在菱形内
		virtual bool isTriggerEnter(const diamond& other) = 0;
		// 判断是否在圆形内
		virtual bool isTriggerEnter(const circle& other) = 0;
	private:
		// 位置(图形中心坐标，即外接圆中心坐标)
		jhVector2 position;
	};

	// 圆形
	class circle :public transform
	{
	public:

		// 默认构造函数
		circle(float radius, jhVector2 position = jhVector2(0, 0));
		// 拷贝构造函数
		circle(const circle& other);
		// 半径
		float radius;
		// 获取面积
		virtual float getAreaSize();
		// 移动
		virtual void move(jhVector2 dest);
		//获取左上角坐标
		virtual jhVector2 getLeftTopPosition();
		// 判断是否在三角形内
		virtual bool isTriggerEnter(const triangle& other);
		// 判断是否在矩形内
		virtual bool isTriggerEnter(const rectangle& other);
		// 判断是否在菱形内
		virtual bool isTriggerEnter(const diamond& other);
		// 判断是否在圆形内
		virtual bool isTriggerEnter(const circle& other);
	};

	// 矩形
	class rectangle : public transform
	{
	public:

		// 默认构造函数
		rectangle(float width, float height, jhVector2 position = jhVector2(0, 0));
		// 拷贝构造函数
		rectangle(const rectangle& other);
		// 宽度和高度
		float width;
		// 高度
		float height;
		// 获取面积
		virtual float getAreaSize();
		// 移动
		virtual void move(jhVector2 dest);
		// 获取左上角坐标
		virtual jhVector2 getLeftTopPosition();
		// 判断是否在三角形内
		virtual bool isTriggerEnter(const triangle& other);
		// 判断是否在矩形内
		virtual bool isTriggerEnter(const rectangle& other);
		// 判断是否在菱形内
		virtual bool isTriggerEnter(const diamond& other);
		// 判断是否在圆形内
		virtual bool isTriggerEnter(const circle& other);
	};
	// 三角形
	class triangle :public transform
	{
	public:

		// 构造普通三角形
		triangle(jhVector2 pointA, jhVector2 pointB, jhVector2 pointC);
		// 构造等边三角形
		triangle(jhVector2 center, float coLength);
		// 拷贝构造函数
		triangle(const triangle& other);
		// 移动
		virtual void move(jhVector2 dest);
		// 三个顶点
		jhVector2 pointA, pointB, pointC;
		// 获取点A的坐标
		jhVector2 getPositionA();
		// 获取点B的坐标
		jhVector2 getPositionB();
		// 获取点C的坐标
		jhVector2 getPositionC();
		//获取左上角坐标
		virtual jhVector2 getLeftTopPosition();
		// 获取面积
		virtual float getAreaSize();
		// 判断是否在三角形内
		virtual bool isTriggerEnter(const triangle& other);
		// 判断是否在矩形内
		virtual bool isTriggerEnter(const rectangle& other);
		// 判断是否在菱形内
		virtual bool isTriggerEnter(const diamond& other);
		// 判断是否在圆形内
		virtual bool isTriggerEnter(const circle& other);
	};

	// 菱形
	class diamond :public transform
	{
	public:

		// 以对角线长度构造菱形
		diamond(float lengthX, float lengthY, jhVector2 position = jhVector2(0, 0));
		//拷贝构造函数
		diamond(const diamond& other);
		// 对角线长度
		float lengthX, lengthY;
		// 获取面积
		virtual float getAreaSize();
		// 移动
		virtual void move(jhVector2 dest);
		//获取左上角坐标
		virtual jhVector2 getLeftTopPosition();
		// 判断是否在三角形内
		virtual bool isTriggerEnter(const triangle& other);
		// 判断是否在矩形内
		virtual bool isTriggerEnter(const rectangle& other);
		// 判断是否在菱形内
		virtual bool isTriggerEnter(const diamond& other);
		// 判断是否在圆形内
		virtual bool isTriggerEnter(const circle& other);
	};

};



//游戏对象类
class gameObject
{
	friend class Game;
	friend class gameScene;
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
	//鼠标事件
	MouseAction<gameObject*>* mouseAction;
	//游戏对象可视性
	bool visible;
	//构造函数
	gameObject(jhObject2D::circle* transform, LPCTSTR file, int width, int height, bool visible = true);
	gameObject(jhObject2D::rectangle* transform, LPCTSTR file, int width, int height, bool visible = true);
	gameObject(jhObject2D::diamond* transform, LPCTSTR file, int width, int height, bool visible = true);
	gameObject(jhObject2D::triangle* transform, LPCTSTR file, int width, int height, bool visible = true);
	//设置碰撞回调函数
	gameObject* setOnCollision(void (*onCollision)(gameObject* gameObject));
	//设置游戏循环回调函数
	gameObject* setGameLoopFunc(void(*gameLoopFunc)(gameObject* gameObject));
	// 修改游戏对象贴图
	gameObject* changeImage(LPCTSTR file,jhVector2 size);
	//标签
	jhString tag="gameObject";


private:
	//游戏对象的图片
	IMAGE* image;
	//碰撞回调函数
	void (*onCollision)(gameObject* gameObject) = NULL;
	//游戏循环回调函数
	void(*gameLoopFunc)(gameObject* gameObject) = NULL;
	//被引用次数
	int refCount = 0;
};

//游戏界面类
class gameUI
{
	friend class Game;
	friend class gameScene;
private:
	//图片
	IMAGE* image;
	//被引用次数
	int refCount = 0;
	//循环函数
	void (*gameLoopFunc)(gameUI* self) = NULL;
public:
	//位置
	jhVector2 position;
	//大小
	jhVector2 size;
	//鼠标事件
	MouseAction<gameUI*>* mouseAction;
	//可视性
	bool visible;
	//设置循环函数
	gameUI* setGameLoopFunc(void (*gameLoopFunc)(gameUI* self));
	//构造函数
	gameUI(jhVector2 position, jhVector2 size, jhString image, bool visible = true);
	//修改游戏界面贴图
	gameUI* changeImage(LPCTSTR file, jhVector2 size);
	//标签
	jhString tag = "gameUI";
};

//游戏界面文字类
class gameUIText
{
	friend class Game;
	friend class gameScene;
public:
	// 文字
	jhString text;
	// 颜色
	COLORREF color;
	// 字体大小
	jhVector2 size;
	// 位置
	jhVector2 position;
	// 可视性
	bool visible;
	// 构造函数
	gameUIText(jhString text, jhVector2 position, COLORREF color = WHITE, jhVector2 size = jhVector2(0, 15), bool visible = true);
private:
	//被引用次数
	int refCount = 0;
	//标签
	jhString tag = "gameUIText";
};


//游戏音效类
class gameSound
{
	friend class Game;
private:
	//音效
	jhString music_file;
public:
	//设置音乐文件
	void setSound(jhString music_file);
	//播放音效
	void play(bool repeat=false);
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
	a = 65,
	b = 66,
	c = 67,
	d = 68,
	e = 69,
	f = 70,
	g = 71,
	h = 72,
	i = 73,
	j = 74,
	k = 75,
	l = 76,
	m = 77,
	n = 78,
	o = 79,
	p = 80,
	q = 81,
	r = 82,
	s = 83,
	t = 84,
	u = 85,
	v = 86,
	w = 87,
	x = 88,
	y = 89,
	z = 90,
	enter = 13,
	space = 32,
	esc = 27,
};

//键盘输入类
class gameInput
{
	friend class Game;
private:
	char key;
	void getMessage(const ExMessage& msg);
public:
	//获取键盘输入
	char getKey();
};

enum MouseMessage
{
	leftDown = 513,
	leftUp = 514,
	rightDown = 516,
	rightUp = 517,
};

//游戏场景类
class gameScene
{
	friend class Game;
private:
	//游戏物体
	jhList<gameObject*> gameObjects;
	//游戏界面
	jhList<gameUI*> gameUIs;
	//界面文字
	jhList<gameUIText*> gameUITexts;
	//游戏物体map
	map<jhString, gameObject*> gameObjectsMap;
	//游戏界面map
	map<jhString, gameUI*> gameUIMap;
	//游戏界面文字map
	map<jhString, gameUIText*> gameUITextsMap;
	//资源总map 物体100，界面UI10，界面文字1
	map<jhString, int> gameTotalMap;
	//循环函数
	void (*gameLoop)()=NULL;
	//唤醒函数
	void (*awake)() = NULL;
public:
	//析构函数
	~gameScene();
	//添加游戏物体
	void addGameObject(jhString name, gameObject* gameObject);
	//删除游戏物体
	void removeGameObject(jhString name);
	//获取游戏对象名字
	jhString getName(gameObject* gameObject);
	jhString getName(gameUI* gameUI);
	jhString getName(gameUIText* gameUIText);
	//添加游戏界面UI对象
	void addGameUI(jhString name, gameUI* gameUI);
	//添加游戏界面文字
	void addGameUIText(jhString name, gameUIText* text);
	//删除游戏界面
	void removeGameUI(jhString name);
	//删除游戏界面文字
	void removeGameUIText(jhString name);
	//获取游戏物体
	gameObject* getGameObject(jhString name);
	//获取游戏界面
	gameUI* getGameUI(jhString name);
	//获取游戏界面文本
	gameUIText* getGameUIText(jhString name);
	//设置循环函数
	void setGameLoopFunc(void (*gameLoop)());
	//设置唤醒函数
	void setAwakeFunc(void (*awake)());
};

//鼠标事件类
template<class T>
class MouseAction
{
	friend class Game;
	friend class gameObject;
	friend class gameUI;
private:
	//左上角起始判断坐标
	jhVector2 beginPosition;
	//右下角结束判断坐标
	jhVector2 endPosition;
	//获取鼠标点击事件
	void getMouseMessage(const ExMessage& msg);
	//父对象指针
	T self;
	//鼠标点击回调函数
	void (*onClick)(int mouseMessage, jhVector2 position,T self) = NULL;
public:
	//设置鼠标点击回调函数
	void setClickFunc(void (*onClick)(int mouseMessage, jhVector2 position,T self));
};

//输入框类
class gameInputBox
{
	friend class Game;
private:
	jhString* inputText;
	jhString title;
	jhString prompt = "";
	jhString defaultText = "";
	int maxInput = 100;
	jhVector2 size = jhVector2(0,0);
public:
	gameInputBox(jhString* inputText, jhString title="notice", jhString prompt="", jhString defaultText="", int max=256, jhVector2 size=jhVector2(0,0));
	void show();
};

//消息框类
class gameMessageBox
{
	friend class Game;
private:
		jhString title = "notice:";
		jhString message = "";
public:
	gameMessageBox(jhString title, jhString message);
	void show();
};

//游戏类
class Game
{
private:
	//游戏窗口句柄
	HWND window;
	//游戏窗口大小
	jhVector2 windowSize = jhVector2(800, 600);
	//游戏窗口标题
	jhString windowTitle = "not define";
	//游戏场景
	gameScene* Scene = NULL;
	//游戏帧率
	int targetFrame = 60;
	//游戏音效
	gameSound Sound;
	//游戏循环
	void gameLoop();
public:
	//设置游戏窗口大小
	void setWindowSize(jhVector2 windowSize);
	//设置游戏窗口标题
	void setWindowTitle(jhString windowTitle);
	//初始化窗口,开始游戏
	void initWindow();
	//设置游戏场景
	void setScene(gameScene* Scene);
	//设置游戏帧率
	void setTargetFrame(int targetFrame);
	//游戏间隔
	long deltaTime;
	//获取游戏窗口大小
	jhVector2 getWindowSize();
	//获取游戏窗口标题
	jhString getWindowTitle();
	//获取游戏场景
	gameScene* getScene();
	//键盘输入
	gameInput Input;
};


#endif // !JHMG_ENGINE_H
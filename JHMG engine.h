#ifndef JHMG_ENGINE_H
#define JHMG_ENGINE_H
#include "easyx.h"
#include<map>
#include<string>
#include<time.h>
#include<iostream>
#include<stdexcept>
#include<cmath>

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


#define PI 3.14

namespace JHMG_ENGINE
{
	// 类定义
	class Transform;
	class Circle;
	class Rectangle;
	class Triangle;
	class Diamond;
	class Trapezium;

	class GameObject;
	class GameUI;
	class GameUIText;
	class GameSound;
	class GameInput;
	class GameScene;
	template<class T> class MouseAction;
	class GameInputBox;
	class GameMessageBox;
	class Game;

	class String;
	class Fraction;
	class Vector2;
	template<class T> class List;
	class Matrix;
};


//jhString类:字符串类型
class JHMG_ENGINE::String
{
	//友元类
	friend std::ostream& operator<<(std::ostream& cout, const JHMG_ENGINE::String& m_str);
	friend std::istream& operator>>(std::istream& cin, const JHMG_ENGINE::String& m_str);
public:
	//构造函数
	String();
	String(const std::string& m_str);
	String(const char* m_str);
	String(const String& m_str);
	//运算符重载
	String operator+(const String& m_str);
	String operator+(const std::string& m_str);
	void operator=(const String& m_str);
	void operator=(const std::string& m_str);
	void operator+=(const String& m_str);
	void operator+=(const std::string& m_str);
	bool operator==(const String& m_str);
	bool operator<(const String& m_str)const;
	bool operator>(const String& m_str)const;
	//字符串转换为整型数据(如果可以)
	int to_int();
	//转换为char*
	char* to_char();
	//字符串转换为浮点型数据(如果可以)
	float to_float();
	//返回字符串索引，从0开始
	int indexOf(const std::string& m_str);
	//返回字符串索引，从0开始
	int indexOf(const String& m_str);
	//转换为std::string
	std::string to_stdString();
	//字符串截取，从起始位置截取到终点位置，从0开始
	std::string substr(int begin, int end);
	//字符串截取,从左边字符截取到右边字符(不包含边界)，若找不到左边，返回空；若找到左边，但找不到右边，返回左边到末尾
	std::string substr(const std::string& leftStr, const std::string& rightStr);
private:
	std::string m_str;
};
//jhFraction类:s/m分数类
class JHMG_ENGINE::Fraction
{
public:
	//友元类
	friend std::ostream& operator<<(std::ostream& cout, const Fraction& num);
	friend std::istream& operator>>(std::istream& cin, Fraction& num);
	//构造函数
	Fraction();
	//拷贝构造函数
	Fraction(const Fraction& num);
	//构造函数
	Fraction(int num);
	Fraction(double num);
	Fraction(int s, int m);
	//化简
	void simplify();
	//打印
	void print();
	//转换为浮点数
	float to_float();
	//加法运算符重载
	Fraction operator+(const Fraction& num);
	Fraction operator+(float num);
	//加等于运算符重载
	Fraction& operator+=(float num);
	Fraction& operator+=(const Fraction& num);
	//减法运算符重载
	Fraction operator-(const Fraction& num);
	Fraction operator-(float num);
	//减等于运算符重载
	Fraction& operator-=(const Fraction& num);
	Fraction& operator-=(float num);
	//乘法运算符重载
	Fraction operator*(const Fraction& num);
	Fraction operator*(float num);
	//乘等于运算符重载
	Fraction operator*=(float num);
	//等于运算符重载
	Fraction operator=(const Fraction& num);
	//除法运算符重载
	Fraction operator/(const Fraction& num);
	Fraction operator/(float num);
	//除等于运算符重载
	Fraction operator/=(float num);
	//比较运算符重载
	bool operator>(const Fraction& num);
	bool operator>(float num);
	bool operator>=(const Fraction& num);
	bool operator>=(float num);
	bool operator<(const Fraction& num);
	bool operator<(float num);
	bool operator<=(const Fraction& num);
	bool operator<=(float num);
	bool operator==(const Fraction& num);
	bool operator==(float num);
private:
	int s, m;/* （s/m分数类型）*/
};
//jhVector2类：二维向量，坐标
class JHMG_ENGINE::Vector2
{
public:
	//友元类
	float x, y;
	//默认构造函数
	Vector2();
	//构造函数
	Vector2(float x, float y);
	//拷贝构造函数
	Vector2(const Vector2& v2);
	//赋值运算符重载
	Vector2& operator=(const Vector2& v2);
	//加法运算符重载
	Vector2 operator+(const Vector2& v2);
	//加等于运算符重载
	Vector2& operator+=(const Vector2& v2);
	//减法运算符重载
	Vector2 operator-(const Vector2& v2);
	//减等于运算符重载
	Vector2& operator-=(const Vector2& v2);
	//乘法运算符重载
	Vector2 operator*(float i);
	//除法运算符重载
	Vector2 operator/(float i);
	//判断是否相等
	bool operator==(const Vector2& v2);
	//求坐标距离
	double destance(const Vector2& objective);
	//求向量叉乘
	double cross_product(const Vector2& objective);
	//求向量点乘
	double dot_product(const Vector2& objective);
	//旋转
	void rotate(const Vector2& center, float angle);
};
//jhList:链表模板类(无序链表)
template<class T>
class JHMG_ENGINE::List
{
public:
	struct node
	{
		node* p_back = NULL;
		node* p_next = NULL;
		T value = NULL;
	};
	//链表头
	node* p_first;
	//在后面添加节点
	void addList(T value);
	//删除节点
	void deleteList(node* list);
	//默认构造函数
	List();
	//析构函数
	~List();
};
//jhMatrix类，矩阵类
class JHMG_ENGINE::Matrix
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
	Matrix(int row, int column);
	//用另一个矩阵构造
	Matrix(const Matrix& other);
	// jhVector2构造函数
	Matrix(const Vector2& v2);
	// 二维数组转换的一维指针构造
	Matrix(float* other, int row, int column);
	// 析构函数
	~Matrix();
	// 设置矩阵值
	void setValue(int row, int column, float value);
	//打印矩阵
	void print(bool isFraction = false);
	// 取转置矩阵
	Matrix getTransposeMatrix();
	// 取逆矩阵
	Matrix getInverseMatrix();
	//取行列式
	float getDeterminant();
	// 交换行
	void swapRows(int row1, int row2);
	// 将某行所有元素除以一个数
	void divideRow(int row, float divisor);
	// 将一行加到另一行的倍数
	void addToRow(int sourceRow, int destRow, float multiple);
	// 矩阵运算
	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);
	Matrix operator*(float num);
	void operator=(const Matrix& other);
	bool operator==(const Matrix& other);
};

	// 物体基类
	class JHMG_ENGINE::Transform
	{
	public:

		//友元类
		friend class Circle;
		friend class Rectangle;
		friend class Triangle;
		friend class Diamond;
		// 默认构造函数
		Transform();
		//拷贝构造函数
		Transform(const JHMG_ENGINE::Transform& other);
		// 构造函数
		Transform(JHMG_ENGINE::Vector2 position);
		//移动
		virtual void move(JHMG_ENGINE::Vector2 dest) = 0;
		//获取当前位置
		virtual JHMG_ENGINE::Vector2 getPosition();
		// 计算面积
		virtual float getAreaSize() = 0;
		// 计算距离
		float getDistance(const JHMG_ENGINE::Transform& other);
		//获取左上角坐标
		virtual JHMG_ENGINE::Vector2 getLeftTopPosition() = 0;
		// 判断是否在三角形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Triangle& other) = 0;
		// 判断是否在矩形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Rectangle& other) = 0;
		// 判断是否在菱形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Diamond& other) = 0;
		// 判断是否在圆形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Circle& other) = 0;
	private:
		// 位置(图形中心坐标，即外接圆中心坐标)
		JHMG_ENGINE::Vector2 position;
	};

	// 圆形
	class JHMG_ENGINE::Circle :public JHMG_ENGINE::Transform
	{
	public:

		// 默认构造函数
		Circle(float radius, JHMG_ENGINE::Vector2 position = JHMG_ENGINE::Vector2(0, 0));
		// 拷贝构造函数
		Circle(const Circle& other);
		// 半径
		float radius;
		// 获取面积
		virtual float getAreaSize();
		// 移动
		virtual void move(JHMG_ENGINE::Vector2 dest);
		//获取左上角坐标
		virtual JHMG_ENGINE::Vector2 getLeftTopPosition();
		// 判断是否在三角形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Triangle& other);
		// 判断是否在矩形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Rectangle& other);
		// 判断是否在菱形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Diamond& other);
		// 判断是否在圆形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Circle& other);
	};

	// 矩形
	class JHMG_ENGINE::Rectangle : public JHMG_ENGINE::Transform
	{
	public:

		// 默认构造函数
		Rectangle(float width, float height, JHMG_ENGINE::Vector2 position = JHMG_ENGINE::Vector2(0, 0));
		// 拷贝构造函数
		Rectangle(const Rectangle& other);
		// 宽度和高度
		float width;
		// 高度
		float height;
		// 获取面积
		virtual float getAreaSize();
		// 移动
		virtual void move(JHMG_ENGINE::Vector2 dest);
		// 获取左上角坐标
		virtual JHMG_ENGINE::Vector2 getLeftTopPosition();
		// 判断是否在三角形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Triangle& other);
		// 判断是否在矩形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Rectangle& other);
		// 判断是否在菱形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Diamond& other);
		// 判断是否在圆形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Circle& other);
	};
	// 三角形
	class JHMG_ENGINE::Triangle :public JHMG_ENGINE::Transform
	{
	public:

		// 构造普通三角形
		Triangle(JHMG_ENGINE::Vector2 pointA, JHMG_ENGINE::Vector2 pointB, JHMG_ENGINE::Vector2 pointC);
		// 构造等边三角形
		Triangle(JHMG_ENGINE::Vector2 center, float coLength);
		// 拷贝构造函数
		Triangle(const Triangle& other);
		// 移动
		virtual void move(JHMG_ENGINE::Vector2 dest);
		// 三个顶点
		JHMG_ENGINE::Vector2 pointA, pointB, pointC;
		// 获取点A的坐标
		JHMG_ENGINE::Vector2 getPositionA();
		// 获取点B的坐标
		JHMG_ENGINE::Vector2 getPositionB();
		// 获取点C的坐标
		JHMG_ENGINE::Vector2 getPositionC();
		//获取左上角坐标
		virtual JHMG_ENGINE::Vector2 getLeftTopPosition();
		// 获取面积
		virtual float getAreaSize();
		// 判断是否在三角形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Triangle& other);
		// 判断是否在矩形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Rectangle& other);
		// 判断是否在菱形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Diamond& other);
		// 判断是否在圆形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Circle& other);
	};

	// 菱形
	class JHMG_ENGINE::Diamond :public JHMG_ENGINE::Transform
	{
	public:

		// 以对角线长度构造菱形
		Diamond(float lengthX, float lengthY, JHMG_ENGINE::Vector2 position = JHMG_ENGINE::Vector2(0, 0));
		//拷贝构造函数
		Diamond(const Diamond& other);
		// 对角线长度
		float lengthX, lengthY;
		// 获取面积
		virtual float getAreaSize();
		// 移动
		virtual void move(JHMG_ENGINE::Vector2 dest);
		//获取左上角坐标
		virtual JHMG_ENGINE::Vector2 getLeftTopPosition();
		// 判断是否在三角形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Triangle& other);
		// 判断是否在矩形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Rectangle& other);
		// 判断是否在菱形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Diamond& other);
		// 判断是否在圆形内
		virtual bool isTriggerEnter(const JHMG_ENGINE::Circle& other);
	};




//游戏对象类
class JHMG_ENGINE::GameObject
{
	friend class JHMG_ENGINE::Game;
	friend class JHMG_ENGINE::GameScene;
public:
	//游戏对象
	union Transform
	{
		JHMG_ENGINE::Circle* Circle;
		JHMG_ENGINE::Diamond* Diamond;
		JHMG_ENGINE::Rectangle* Rectangle;
		JHMG_ENGINE::Triangle* Triangle;
	};
	Transform Transform;
	char transformType;
	//鼠标事件
	JHMG_ENGINE::MouseAction<JHMG_ENGINE::GameObject*>* mouseAction;
	//游戏对象可视性
	bool visible;
	//构造函数
	GameObject(JHMG_ENGINE::Circle* Transform, JHMG_ENGINE::String file, int width, int height, bool visible = true);
	GameObject(JHMG_ENGINE::Circle* Transform, IMAGE* image, bool visible = true);
	GameObject(JHMG_ENGINE::Rectangle* Transform, JHMG_ENGINE::String file, int width, int height, bool visible = true);
	GameObject(JHMG_ENGINE::Rectangle* Transform, IMAGE* image, bool visible = true);
	GameObject(JHMG_ENGINE::Diamond* Transform, JHMG_ENGINE::String file, int width, int height, bool visible = true);
	GameObject(JHMG_ENGINE::Diamond* Transform, IMAGE* image, bool visible = true);
	GameObject(JHMG_ENGINE::Triangle* Transform, JHMG_ENGINE::String file, int width, int height, bool visible = true);
	GameObject(JHMG_ENGINE::Triangle* Transform, IMAGE* image, bool visible = true);
	//设置碰撞回调函数
	GameObject* setOnCollision(void (*onCollision)(GameObject* self, GameObject* GameObject));
	//设置游戏循环回调函数
	GameObject* setGameLoopFunc(void(*gameLoopFunc)(GameObject* self));
	// 修改游戏对象贴图
	GameObject* changeImage(LPCTSTR file, JHMG_ENGINE::Vector2 size);
	GameObject* changeImage(IMAGE* image, bool release = true);
	//标签
	JHMG_ENGINE::String tag="gameObject";
	//析构函数
	~GameObject();

private:
	//游戏对象的图片
	IMAGE* image;
	//碰撞回调函数
	void (*onCollision)(GameObject* self,GameObject* GameObject) = NULL;
	//游戏循环回调函数
	void(*gameLoopFunc)(GameObject* self) = NULL;
	//被引用次数
	int refCount = 0;
	//是否删除图片
	bool imgRelease = false;
};

//游戏界面类
class JHMG_ENGINE::GameUI
{
	friend class JHMG_ENGINE::Game;
	friend class JHMG_ENGINE::GameScene;
private:
	//图片
	IMAGE* image;
	//被引用次数
	int refCount = 0;
	//循环函数
	void (*gameLoopFunc)(GameUI* self) = NULL;
	//是否删除图片
	bool imgRelease = false;
public:
	//位置
	JHMG_ENGINE::Vector2 position;
	//大小
	JHMG_ENGINE::Vector2 size;
	//鼠标事件
	JHMG_ENGINE::MouseAction<JHMG_ENGINE::GameUI*>* mouseAction;
	//可视性
	bool visible;
	//设置循环函数
	GameUI* setGameLoopFunc(void (*gameLoopFunc)(GameUI* self));
	//构造函数
	GameUI(JHMG_ENGINE::Vector2 position, JHMG_ENGINE::Vector2 size, JHMG_ENGINE::String image, bool visible = true);
	GameUI(JHMG_ENGINE::Vector2 position, IMAGE* image, bool visible = true);
	//修改游戏界面贴图
	GameUI* changeImage(LPCTSTR file, JHMG_ENGINE::Vector2 size);
	GameUI* changeImage(IMAGE* image,bool release = true);
	//标签
	JHMG_ENGINE::String tag = "gameUI";
	//析构函数
	~GameUI();
};

//游戏界面文字类
class JHMG_ENGINE::GameUIText
{
	friend class JHMG_ENGINE::Game;
	friend class JHMG_ENGINE::GameScene;
public:
	// 文字
	JHMG_ENGINE::String text;
	// 颜色
	COLORREF color;
	// 字体大小
	JHMG_ENGINE::Vector2 size;
	// 位置
	JHMG_ENGINE::Vector2 position;
	// 可视性
	bool visible;
	// 构造函数
	GameUIText(JHMG_ENGINE::String text, JHMG_ENGINE::Vector2 position, COLORREF color = WHITE, JHMG_ENGINE::Vector2 size = JHMG_ENGINE::Vector2(0, 15), bool visible = true);
private:
	//被引用次数
	int refCount = 0;
	//标签
	JHMG_ENGINE::String tag = "gameUIText";
};


//游戏音效类
class JHMG_ENGINE::GameSound
{
	friend class JHMG_ENGINE::Game;
private:
	//名称
	JHMG_ENGINE::String name;
public:
	//打开音乐文件
	void open(JHMG_ENGINE::String name, JHMG_ENGINE::String music_file);
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
	~GameSound();
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
class JHMG_ENGINE::GameInput
{
	friend class JHMG_ENGINE::Game;
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
class JHMG_ENGINE::GameScene
{
	friend class JHMG_ENGINE::Game;
private:
	//游戏物体
	JHMG_ENGINE::List<JHMG_ENGINE::GameObject*> gameObjects;
	//游戏界面
	JHMG_ENGINE::List<JHMG_ENGINE::GameUI*> gameUIs;
	//界面文字
	JHMG_ENGINE::List<JHMG_ENGINE::GameUIText*> gameUITexts;
	//游戏物体map
	std::map<JHMG_ENGINE::String, JHMG_ENGINE::GameObject*> gameObjectsMap;
	//游戏界面map
	std::map<JHMG_ENGINE::String, JHMG_ENGINE::GameUI*> gameUIMap;
	//游戏界面文字map
	std::map<JHMG_ENGINE::String, JHMG_ENGINE::GameUIText*> gameUITextsMap;
	//资源总map 物体100，界面UI10，界面文字1
	std::map<JHMG_ENGINE::String, int> gameTotalMap;
	//循环函数
	void (*gameLoop)()=NULL;
	//唤醒函数
	void (*awake)() = NULL;
public:
	//析构函数
	~GameScene();
	//添加游戏物体
	void addGameObject(JHMG_ENGINE::String name, JHMG_ENGINE::GameObject* GameObject);
	//删除游戏物体
	void removeGameObject(JHMG_ENGINE::String name);
	//获取游戏对象名字
	JHMG_ENGINE::String getName(JHMG_ENGINE::GameObject* GameObject);
	JHMG_ENGINE::String getName(JHMG_ENGINE::GameUI* GameUI);
	JHMG_ENGINE::String getName(JHMG_ENGINE::GameUIText* GameUIText);
	//添加游戏界面UI对象
	void addGameUI(JHMG_ENGINE::String name, JHMG_ENGINE::GameUI* GameUI);
	//添加游戏界面文字
	void addGameUIText(JHMG_ENGINE::String name, JHMG_ENGINE::GameUIText* text);
	//删除游戏界面
	void removeGameUI(JHMG_ENGINE::String name);
	//删除游戏界面文字
	void removeGameUIText(JHMG_ENGINE::String name);
	//获取游戏物体
	JHMG_ENGINE::GameObject* getGameObject(JHMG_ENGINE::String name);
	//获取游戏界面
	JHMG_ENGINE::GameUI* getGameUI(JHMG_ENGINE::String name);
	//获取游戏界面文本
	JHMG_ENGINE::GameUIText* getGameUIText(JHMG_ENGINE::String name);
	//设置循环函数
	void setGameLoopFunc(void (*gameLoop)());
	//设置唤醒函数
	void setAwakeFunc(void (*awake)());
};

//鼠标事件类
template<class T>
class JHMG_ENGINE::MouseAction
{
	friend class Game;
	friend class GameObject;
	friend class GameUI;
private:
	//鼠标当前位置
	Vector2 mousePosition;
	//左上角起始判断坐标
	Vector2 beginPosition;
	//右下角结束判断坐标
	Vector2 endPosition;
	//获取鼠标点击事件
	void getMouseMessage(const ExMessage& msg);
	//父对象指针
	T self;
	//鼠标点击回调函数
	void (*onClick)(int mouseMessage, Vector2 position,T self) = NULL;
public:
	//设置鼠标点击回调函数
	void setClickFunc(void (*onClick)(int mouseMessage, Vector2 position,T self));
	//获取鼠标当前位置
	Vector2 getMousePosition();
};

//输入框类
class JHMG_ENGINE::GameInputBox
{
	friend class JHMG_ENGINE::Game;
private:
	JHMG_ENGINE::String* inputText;
	JHMG_ENGINE::String title;
	JHMG_ENGINE::String prompt = "";
	JHMG_ENGINE::String defaultText = "";
	int maxInput = 100;
	JHMG_ENGINE::Vector2 size = JHMG_ENGINE::Vector2(0,0);
public:
	GameInputBox(JHMG_ENGINE::String* inputText, JHMG_ENGINE::String title="notice", JHMG_ENGINE::String prompt="", JHMG_ENGINE::String defaultText="", int max=256, JHMG_ENGINE::Vector2 size= JHMG_ENGINE::Vector2(0,0));
	void show();
};

//消息框类
class JHMG_ENGINE::GameMessageBox
{
	friend class JHMG_ENGINE::Game;
private:
	JHMG_ENGINE::String title = "notice:";
	JHMG_ENGINE::String message = "";
public:
	GameMessageBox(JHMG_ENGINE::String title, JHMG_ENGINE::String message);
	void show();
};

//游戏类
class JHMG_ENGINE::Game
{
private:
	//游戏窗口句柄
	HWND window;
	//游戏窗口大小
	JHMG_ENGINE::Vector2 windowSize = JHMG_ENGINE::Vector2(800, 600);
	//游戏窗口标题
	JHMG_ENGINE::String windowTitle = "not define";
	//游戏场景
	JHMG_ENGINE::GameScene* Scene = NULL;
	//游戏帧率
	int targetFrame = 60;
	//游戏循环
	void gameLoop();
	//游戏是否运行
	bool isRun = true;
public:
	//设置游戏窗口大小
	void setWindowSize(JHMG_ENGINE::Vector2 windowSize);
	//设置游戏窗口标题
	void setWindowTitle(JHMG_ENGINE::String windowTitle);
	//初始化窗口,开始游戏
	void initWindow();
	//设置游戏场景
	void setScene(JHMG_ENGINE::GameScene* Scene);
	//设置游戏帧率
	void setTargetFrame(int targetFrame);
	//关闭游戏
	void close();
	//游戏间隔
	long deltaTime;
	//获取游戏窗口大小
	JHMG_ENGINE::Vector2 getWindowSize();
	//获取游戏窗口标题
	JHMG_ENGINE::String getWindowTitle();
	//获取游戏场景
	JHMG_ENGINE::GameScene* getScene();
	//键盘输入
	JHMG_ENGINE::GameInput input;
};


#endif // !JHMG_ENGINE_H
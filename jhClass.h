#pragma once
#include<string>
#include<iostream>
#include<stdexcept>
#include<cmath>
using namespace std;
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
	jhString operator=(const jhString& str);
	jhString operator=(const string& str);
	jhString operator+=(const jhString& str);
	jhString operator+=(const string& str);
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

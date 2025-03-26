#ifndef JHMG_ENGINE_H
#define JHMG_ENGINE_H
#include<easyx.h>
#include<map>
#include<string>
#include<time.h>
#include<iostream>
#include<stdexcept>
#include<cmath>

//���ֲ��������
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

/*
����ϵ˵����
	����ԭ�����豸�����Ͻǣ�X ������Ϊ����Y ������Ϊ����������λ������
*/

//putImg��չ
inline void putimagePNG(int x, int y, IMAGE* img) {
	DWORD* pwin = GetImageBuffer();//��ȡ���ڻ�����ָ��
	DWORD* pimg = GetImageBuffer(img);//��ȡͼƬ������ָ��
	int win_w = getwidth();
	int win_h = getheight();
	int img_w = img->getwidth();
	int img_h = img->getheight();
	//�ж�x,y�����Ƿ񳬳��˴��ڵķ�Χ
	int real_w = (x + img_w > win_w) ? win_w - x : img_w;//�����ұ߽�ʵ����ͼ�Ŀ��
	int real_h = (y + img_h > win_h) ? win_h - y : img_h;//�����±߽�
	if (x < 0) {//������߽紦��
		pimg += -x;//��ָ�����ƫ��
		real_w -= -x;
		x = 0;
	}
	if (y < 0) {//�����ϱ߽紦��
		pimg += (img_w * -y);//��ָ�����ƫ��
		real_h -= -y;
		y = 0;
	}
	pwin += (win_w * y + x);

	for (int iy = 0; iy < real_h; iy++) {
		for (int ix = 0; ix < real_w; ix++) {
			UCHAR alpha = pimg[ix] >> 24;
			if (alpha > 200)//alpha  0 ��ʾ��ȫ͸��
			{
				pwin[ix] = pimg[ix];
			}
		}
		//������һ��
		pwin += win_w;
		pimg += img_w;
	}
}


#define PI 3.14

namespace JHMG_ENGINE
{
	// �ඨ��
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


//jhString��:�ַ�������
class JHMG_ENGINE::String
{
	//��Ԫ��
	friend std::ostream& operator<<(std::ostream& cout, const JHMG_ENGINE::String& m_str);
	friend std::istream& operator>>(std::istream& cin, const JHMG_ENGINE::String& m_str);
public:
	//���캯��
	String();
	String(const std::string& m_str);
	String(const char* m_str);
	String(const String& m_str);
	//���������
	String operator+(const String& m_str);
	String operator+(const std::string& m_str);
	void operator=(const String& m_str);
	void operator=(const std::string& m_str);
	void operator+=(const String& m_str);
	void operator+=(const std::string& m_str);
	bool operator==(const String& m_str);
	bool operator<(const String& m_str)const;
	bool operator>(const String& m_str)const;
	//�ַ���ת��Ϊ��������(�������)
	int to_int();
	//ת��Ϊchar*
	char* to_char();
	//�ַ���ת��Ϊ����������(�������)
	float to_float();
	//�����ַ�����������0��ʼ
	int indexOf(const std::string& m_str);
	//�����ַ�����������0��ʼ
	int indexOf(const String& m_str);
	//ת��Ϊstd::string
	std::string to_stdString();
	//�ַ�����ȡ������ʼλ�ý�ȡ���յ�λ�ã���0��ʼ
	std::string substr(int begin, int end);
	//�ַ�����ȡ,������ַ���ȡ���ұ��ַ�(�������߽�)�����Ҳ�����ߣ����ؿգ����ҵ���ߣ����Ҳ����ұߣ�������ߵ�ĩβ
	std::string substr(const std::string& leftStr, const std::string& rightStr);
private:
	std::string m_str;
};
//jhFraction��:s/m������
class JHMG_ENGINE::Fraction
{
public:
	//��Ԫ��
	friend std::ostream& operator<<(std::ostream& cout, const Fraction& num);
	friend std::istream& operator>>(std::istream& cin, Fraction& num);
	//���캯��
	Fraction();
	//�������캯��
	Fraction(const Fraction& num);
	//���캯��
	Fraction(int num);
	Fraction(double num);
	Fraction(int s, int m);
	//����
	void simplify();
	//��ӡ
	void print();
	//ת��Ϊ������
	float to_float();
	//�ӷ����������
	Fraction operator+(const Fraction& num);
	Fraction operator+(float num);
	//�ӵ������������
	Fraction& operator+=(float num);
	Fraction& operator+=(const Fraction& num);
	//�������������
	Fraction operator-(const Fraction& num);
	Fraction operator-(float num);
	//���������������
	Fraction& operator-=(const Fraction& num);
	Fraction& operator-=(float num);
	//�˷����������
	Fraction operator*(const Fraction& num);
	Fraction operator*(float num);
	//�˵������������
	Fraction operator*=(float num);
	//�������������
	Fraction operator=(const Fraction& num);
	//�������������
	Fraction operator/(const Fraction& num);
	Fraction operator/(float num);
	//���������������
	Fraction operator/=(float num);
	//�Ƚ����������
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
	int s, m;/* ��s/m�������ͣ�*/
};
//jhVector2�ࣺ��ά����������
class JHMG_ENGINE::Vector2
{
public:
	//��Ԫ��
	float x, y;
	//Ĭ�Ϲ��캯��
	Vector2();
	//���캯��
	Vector2(float x, float y);
	//�������캯��
	Vector2(const Vector2& v2);
	//��ֵ���������
	Vector2& operator=(const Vector2& v2);
	//�ӷ����������
	Vector2 operator+(const Vector2& v2);
	//�ӵ������������
	Vector2& operator+=(const Vector2& v2);
	//�������������
	Vector2 operator-(const Vector2& v2);
	//���������������
	Vector2& operator-=(const Vector2& v2);
	//�˷����������
	Vector2 operator*(float i);
	//�������������
	Vector2 operator/(float i);
	//�ж��Ƿ����
	bool operator==(const Vector2& v2);
	//���������
	double destance(const Vector2& objective);
	//���������
	double cross_product(const Vector2& objective);
	//���������
	double dot_product(const Vector2& objective);
	//��ת
	void rotate(const Vector2& center, float angle);
};
//jhList:����ģ����(��������)
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
	//����ͷ
	node* p_first;
	//�ں�����ӽڵ�
	void addList(T value);
	//ɾ���ڵ�
	void deleteList(node* list);
	//Ĭ�Ϲ��캯��
	List();
	//��������
	~List();
};
//jhMatrix�࣬������
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

	// Ĭ�Ϲ��캯��
	Matrix(int row, int column);
	//����һ��������
	Matrix(const Matrix& other);
	// jhVector2���캯��
	Matrix(const Vector2& v2);
	// ��ά����ת����һάָ�빹��
	Matrix(float* other, int row, int column);
	// ��������
	~Matrix();
	// ���þ���ֵ
	void setValue(int row, int column, float value);
	//��ӡ����
	void print(bool isFraction = false);
	// ȡת�þ���
	Matrix getTransposeMatrix();
	// ȡ�����
	Matrix getInverseMatrix();
	//ȡ����ʽ
	float getDeterminant();
	// ������
	void swapRows(int row1, int row2);
	// ��ĳ������Ԫ�س���һ����
	void divideRow(int row, float divisor);
	// ��һ�мӵ���һ�еı���
	void addToRow(int sourceRow, int destRow, float multiple);
	// ��������
	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);
	Matrix operator*(float num);
	void operator=(const Matrix& other);
	bool operator==(const Matrix& other);
};

	// �������
	class JHMG_ENGINE::Transform
	{
	public:

		//��Ԫ��
		friend class Circle;
		friend class Rectangle;
		friend class Triangle;
		friend class Diamond;
		// Ĭ�Ϲ��캯��
		Transform();
		//�������캯��
		Transform(const JHMG_ENGINE::Transform& other);
		// ���캯��
		Transform(JHMG_ENGINE::Vector2 position);
		//�ƶ�
		virtual void move(JHMG_ENGINE::Vector2 dest) = 0;
		//��ȡ��ǰλ��
		virtual JHMG_ENGINE::Vector2 getPosition();
		// �������
		virtual float getAreaSize() = 0;
		// �������
		float getDistance(const JHMG_ENGINE::Transform& other);
		//��ȡ���Ͻ�����
		virtual JHMG_ENGINE::Vector2 getLeftTopPosition() = 0;
		// �ж��Ƿ�����������
		virtual bool isTriggerEnter(const JHMG_ENGINE::Triangle& other) = 0;
		// �ж��Ƿ��ھ�����
		virtual bool isTriggerEnter(const JHMG_ENGINE::Rectangle& other) = 0;
		// �ж��Ƿ���������
		virtual bool isTriggerEnter(const JHMG_ENGINE::Diamond& other) = 0;
		// �ж��Ƿ���Բ����
		virtual bool isTriggerEnter(const JHMG_ENGINE::Circle& other) = 0;
	private:
		// λ��(ͼ���������꣬�����Բ��������)
		JHMG_ENGINE::Vector2 position;
	};

	// Բ��
	class JHMG_ENGINE::Circle :public JHMG_ENGINE::Transform
	{
	public:

		// Ĭ�Ϲ��캯��
		Circle(float radius, JHMG_ENGINE::Vector2 position = JHMG_ENGINE::Vector2(0, 0));
		// �������캯��
		Circle(const Circle& other);
		// �뾶
		float radius;
		// ��ȡ���
		virtual float getAreaSize();
		// �ƶ�
		virtual void move(JHMG_ENGINE::Vector2 dest);
		//��ȡ���Ͻ�����
		virtual JHMG_ENGINE::Vector2 getLeftTopPosition();
		// �ж��Ƿ�����������
		virtual bool isTriggerEnter(const JHMG_ENGINE::Triangle& other);
		// �ж��Ƿ��ھ�����
		virtual bool isTriggerEnter(const JHMG_ENGINE::Rectangle& other);
		// �ж��Ƿ���������
		virtual bool isTriggerEnter(const JHMG_ENGINE::Diamond& other);
		// �ж��Ƿ���Բ����
		virtual bool isTriggerEnter(const JHMG_ENGINE::Circle& other);
	};

	// ����
	class JHMG_ENGINE::Rectangle : public JHMG_ENGINE::Transform
	{
	public:

		// Ĭ�Ϲ��캯��
		Rectangle(float width, float height, JHMG_ENGINE::Vector2 position = JHMG_ENGINE::Vector2(0, 0));
		// �������캯��
		Rectangle(const Rectangle& other);
		// ��Ⱥ͸߶�
		float width;
		// �߶�
		float height;
		// ��ȡ���
		virtual float getAreaSize();
		// �ƶ�
		virtual void move(JHMG_ENGINE::Vector2 dest);
		// ��ȡ���Ͻ�����
		virtual JHMG_ENGINE::Vector2 getLeftTopPosition();
		// �ж��Ƿ�����������
		virtual bool isTriggerEnter(const JHMG_ENGINE::Triangle& other);
		// �ж��Ƿ��ھ�����
		virtual bool isTriggerEnter(const JHMG_ENGINE::Rectangle& other);
		// �ж��Ƿ���������
		virtual bool isTriggerEnter(const JHMG_ENGINE::Diamond& other);
		// �ж��Ƿ���Բ����
		virtual bool isTriggerEnter(const JHMG_ENGINE::Circle& other);
	};
	// ������
	class JHMG_ENGINE::Triangle :public JHMG_ENGINE::Transform
	{
	public:

		// ������ͨ������
		Triangle(JHMG_ENGINE::Vector2 pointA, JHMG_ENGINE::Vector2 pointB, JHMG_ENGINE::Vector2 pointC);
		// ����ȱ�������
		Triangle(JHMG_ENGINE::Vector2 center, float coLength);
		// �������캯��
		Triangle(const Triangle& other);
		// �ƶ�
		virtual void move(JHMG_ENGINE::Vector2 dest);
		// ��������
		JHMG_ENGINE::Vector2 pointA, pointB, pointC;
		// ��ȡ��A������
		JHMG_ENGINE::Vector2 getPositionA();
		// ��ȡ��B������
		JHMG_ENGINE::Vector2 getPositionB();
		// ��ȡ��C������
		JHMG_ENGINE::Vector2 getPositionC();
		//��ȡ���Ͻ�����
		virtual JHMG_ENGINE::Vector2 getLeftTopPosition();
		// ��ȡ���
		virtual float getAreaSize();
		// �ж��Ƿ�����������
		virtual bool isTriggerEnter(const JHMG_ENGINE::Triangle& other);
		// �ж��Ƿ��ھ�����
		virtual bool isTriggerEnter(const JHMG_ENGINE::Rectangle& other);
		// �ж��Ƿ���������
		virtual bool isTriggerEnter(const JHMG_ENGINE::Diamond& other);
		// �ж��Ƿ���Բ����
		virtual bool isTriggerEnter(const JHMG_ENGINE::Circle& other);
	};

	// ����
	class JHMG_ENGINE::Diamond :public JHMG_ENGINE::Transform
	{
	public:

		// �ԶԽ��߳��ȹ�������
		Diamond(float lengthX, float lengthY, JHMG_ENGINE::Vector2 position = JHMG_ENGINE::Vector2(0, 0));
		//�������캯��
		Diamond(const Diamond& other);
		// �Խ��߳���
		float lengthX, lengthY;
		// ��ȡ���
		virtual float getAreaSize();
		// �ƶ�
		virtual void move(JHMG_ENGINE::Vector2 dest);
		//��ȡ���Ͻ�����
		virtual JHMG_ENGINE::Vector2 getLeftTopPosition();
		// �ж��Ƿ�����������
		virtual bool isTriggerEnter(const JHMG_ENGINE::Triangle& other);
		// �ж��Ƿ��ھ�����
		virtual bool isTriggerEnter(const JHMG_ENGINE::Rectangle& other);
		// �ж��Ƿ���������
		virtual bool isTriggerEnter(const JHMG_ENGINE::Diamond& other);
		// �ж��Ƿ���Բ����
		virtual bool isTriggerEnter(const JHMG_ENGINE::Circle& other);
	};




//��Ϸ������
class JHMG_ENGINE::GameObject
{
	friend class JHMG_ENGINE::Game;
	friend class JHMG_ENGINE::GameScene;
public:
	//��Ϸ����
	union Transform
	{
		JHMG_ENGINE::Circle* Circle;
		JHMG_ENGINE::Diamond* Diamond;
		JHMG_ENGINE::Rectangle* Rectangle;
		JHMG_ENGINE::Triangle* Triangle;
	};
	Transform Transform;
	char transformType;
	//����¼�
	JHMG_ENGINE::MouseAction<JHMG_ENGINE::GameObject*>* mouseAction;
	//��Ϸ���������
	bool visible;
	//���캯��
	GameObject(JHMG_ENGINE::Circle* Transform, JHMG_ENGINE::String file, int width, int height, bool visible = true);
	GameObject(JHMG_ENGINE::Circle* Transform, IMAGE* image, bool visible = true);
	GameObject(JHMG_ENGINE::Rectangle* Transform, JHMG_ENGINE::String file, int width, int height, bool visible = true);
	GameObject(JHMG_ENGINE::Rectangle* Transform, IMAGE* image, bool visible = true);
	GameObject(JHMG_ENGINE::Diamond* Transform, JHMG_ENGINE::String file, int width, int height, bool visible = true);
	GameObject(JHMG_ENGINE::Diamond* Transform, IMAGE* image, bool visible = true);
	GameObject(JHMG_ENGINE::Triangle* Transform, JHMG_ENGINE::String file, int width, int height, bool visible = true);
	GameObject(JHMG_ENGINE::Triangle* Transform, IMAGE* image, bool visible = true);
	//������ײ�ص�����
	GameObject* setOnCollision(void (*onCollision)(GameObject* self, GameObject* GameObject));
	//������Ϸѭ���ص�����
	GameObject* setGameLoopFunc(void(*gameLoopFunc)(GameObject* self));
	// �޸���Ϸ������ͼ
	GameObject* changeImage(LPCTSTR file, JHMG_ENGINE::Vector2 size);
	GameObject* changeImage(IMAGE* image, bool release = true);
	//��ǩ
	JHMG_ENGINE::String tag="gameObject";
	//��������
	~GameObject();

private:
	//��Ϸ�����ͼƬ
	IMAGE* image;
	//��ײ�ص�����
	void (*onCollision)(GameObject* self,GameObject* GameObject) = NULL;
	//��Ϸѭ���ص�����
	void(*gameLoopFunc)(GameObject* self) = NULL;
	//�����ô���
	int refCount = 0;
	//�Ƿ�ɾ��ͼƬ
	bool imgRelease = false;
};

//��Ϸ������
class JHMG_ENGINE::GameUI
{
	friend class JHMG_ENGINE::Game;
	friend class JHMG_ENGINE::GameScene;
private:
	//ͼƬ
	IMAGE* image;
	//�����ô���
	int refCount = 0;
	//ѭ������
	void (*gameLoopFunc)(GameUI* self) = NULL;
	//�Ƿ�ɾ��ͼƬ
	bool imgRelease = false;
public:
	//λ��
	JHMG_ENGINE::Vector2 position;
	//��С
	JHMG_ENGINE::Vector2 size;
	//����¼�
	JHMG_ENGINE::MouseAction<JHMG_ENGINE::GameUI*>* mouseAction;
	//������
	bool visible;
	//����ѭ������
	GameUI* setGameLoopFunc(void (*gameLoopFunc)(GameUI* self));
	//���캯��
	GameUI(JHMG_ENGINE::Vector2 position, JHMG_ENGINE::Vector2 size, JHMG_ENGINE::String image, bool visible = true);
	GameUI(JHMG_ENGINE::Vector2 position, IMAGE* image, bool visible = true);
	//�޸���Ϸ������ͼ
	GameUI* changeImage(LPCTSTR file, JHMG_ENGINE::Vector2 size);
	GameUI* changeImage(IMAGE* image,bool release = true);
	//��ǩ
	JHMG_ENGINE::String tag = "gameUI";
	//��������
	~GameUI();
};

//��Ϸ����������
class JHMG_ENGINE::GameUIText
{
	friend class JHMG_ENGINE::Game;
	friend class JHMG_ENGINE::GameScene;
public:
	// ����
	JHMG_ENGINE::String text;
	// ��ɫ
	COLORREF color;
	// �����С
	JHMG_ENGINE::Vector2 size;
	// λ��
	JHMG_ENGINE::Vector2 position;
	// ������
	bool visible;
	// ���캯��
	GameUIText(JHMG_ENGINE::String text, JHMG_ENGINE::Vector2 position, COLORREF color = WHITE, JHMG_ENGINE::Vector2 size = JHMG_ENGINE::Vector2(0, 15), bool visible = true);
private:
	//�����ô���
	int refCount = 0;
	//��ǩ
	JHMG_ENGINE::String tag = "gameUIText";
};


//��Ϸ��Ч��
class JHMG_ENGINE::GameSound
{
	friend class JHMG_ENGINE::Game;
private:
	//����
	JHMG_ENGINE::String name;
public:
	//�������ļ�
	void open(JHMG_ENGINE::String name, JHMG_ENGINE::String music_file);
	//������Ч
	void play(bool repeat=false);
	//ֹͣ��Ч
	void stop();
	//��ͣ��Ч
	void pause();
	//������Ч
	void resume();
	//��������
	void setVolume(int volume);
	//��ȡ����
	int getVolume();
	//���ò���λ��
	void setPosition(int position);
	//��ȡ����λ��
	int getPosition();
	//��ȡ��Ч����
	int getLength();
	//��ȡ��Ч״̬
	int getState();
	//�ر���Ч
	void close();
	//��������
	~GameSound();
};

//������Ϣ��
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

//����������
class JHMG_ENGINE::GameInput
{
	friend class JHMG_ENGINE::Game;
private:
	char key;
	void getMessage(const ExMessage& msg);
public:
	//��ȡ��������
	char getKey();
};

enum MouseMessage
{
	leftDown = 513,
	leftUp = 514,
	rightDown = 516,
	rightUp = 517,
};

//��Ϸ������
class JHMG_ENGINE::GameScene
{
	friend class JHMG_ENGINE::Game;
private:
	//��Ϸ����
	JHMG_ENGINE::List<JHMG_ENGINE::GameObject*> gameObjects;
	//��Ϸ����
	JHMG_ENGINE::List<JHMG_ENGINE::GameUI*> gameUIs;
	//��������
	JHMG_ENGINE::List<JHMG_ENGINE::GameUIText*> gameUITexts;
	//��Ϸ����map
	std::map<JHMG_ENGINE::String, JHMG_ENGINE::GameObject*> gameObjectsMap;
	//��Ϸ����map
	std::map<JHMG_ENGINE::String, JHMG_ENGINE::GameUI*> gameUIMap;
	//��Ϸ��������map
	std::map<JHMG_ENGINE::String, JHMG_ENGINE::GameUIText*> gameUITextsMap;
	//��Դ��map ����100������UI10����������1
	std::map<JHMG_ENGINE::String, int> gameTotalMap;
	//ѭ������
	void (*gameLoop)()=NULL;
	//���Ѻ���
	void (*awake)() = NULL;
public:
	//��������
	~GameScene();
	//�����Ϸ����
	void addGameObject(JHMG_ENGINE::String name, JHMG_ENGINE::GameObject* GameObject);
	//ɾ����Ϸ����
	void removeGameObject(JHMG_ENGINE::String name);
	//��ȡ��Ϸ��������
	JHMG_ENGINE::String getName(JHMG_ENGINE::GameObject* GameObject);
	JHMG_ENGINE::String getName(JHMG_ENGINE::GameUI* GameUI);
	JHMG_ENGINE::String getName(JHMG_ENGINE::GameUIText* GameUIText);
	//�����Ϸ����UI����
	void addGameUI(JHMG_ENGINE::String name, JHMG_ENGINE::GameUI* GameUI);
	//�����Ϸ��������
	void addGameUIText(JHMG_ENGINE::String name, JHMG_ENGINE::GameUIText* text);
	//ɾ����Ϸ����
	void removeGameUI(JHMG_ENGINE::String name);
	//ɾ����Ϸ��������
	void removeGameUIText(JHMG_ENGINE::String name);
	//��ȡ��Ϸ����
	JHMG_ENGINE::GameObject* getGameObject(JHMG_ENGINE::String name);
	//��ȡ��Ϸ����
	JHMG_ENGINE::GameUI* getGameUI(JHMG_ENGINE::String name);
	//��ȡ��Ϸ�����ı�
	JHMG_ENGINE::GameUIText* getGameUIText(JHMG_ENGINE::String name);
	//����ѭ������
	void setGameLoopFunc(void (*gameLoop)());
	//���û��Ѻ���
	void setAwakeFunc(void (*awake)());
};

//����¼���
template<class T>
class JHMG_ENGINE::MouseAction
{
	friend class Game;
	friend class GameObject;
	friend class GameUI;
private:
	//��굱ǰλ��
	Vector2 mousePosition;
	//���Ͻ���ʼ�ж�����
	Vector2 beginPosition;
	//���½ǽ����ж�����
	Vector2 endPosition;
	//��ȡ������¼�
	void getMouseMessage(const ExMessage& msg);
	//������ָ��
	T self;
	//������ص�����
	void (*onClick)(int mouseMessage, Vector2 position,T self) = NULL;
public:
	//����������ص�����
	void setClickFunc(void (*onClick)(int mouseMessage, Vector2 position,T self));
	//��ȡ��굱ǰλ��
	Vector2 getMousePosition();
};

//�������
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

//��Ϣ����
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

//��Ϸ��
class JHMG_ENGINE::Game
{
private:
	//��Ϸ���ھ��
	HWND window;
	//��Ϸ���ڴ�С
	JHMG_ENGINE::Vector2 windowSize = JHMG_ENGINE::Vector2(800, 600);
	//��Ϸ���ڱ���
	JHMG_ENGINE::String windowTitle = "not define";
	//��Ϸ����
	JHMG_ENGINE::GameScene* Scene = NULL;
	//��Ϸ֡��
	int targetFrame = 60;
	//��Ϸѭ��
	void gameLoop();
	//��Ϸ�Ƿ�����
	bool isRun = true;
public:
	//������Ϸ���ڴ�С
	void setWindowSize(JHMG_ENGINE::Vector2 windowSize);
	//������Ϸ���ڱ���
	void setWindowTitle(JHMG_ENGINE::String windowTitle);
	//��ʼ������,��ʼ��Ϸ
	void initWindow();
	//������Ϸ����
	void setScene(JHMG_ENGINE::GameScene* Scene);
	//������Ϸ֡��
	void setTargetFrame(int targetFrame);
	//�ر���Ϸ
	void close();
	//��Ϸ���
	long deltaTime;
	//��ȡ��Ϸ���ڴ�С
	JHMG_ENGINE::Vector2 getWindowSize();
	//��ȡ��Ϸ���ڱ���
	JHMG_ENGINE::String getWindowTitle();
	//��ȡ��Ϸ����
	JHMG_ENGINE::GameScene* getScene();
	//��������
	JHMG_ENGINE::GameInput input;
};


#endif // !JHMG_ENGINE_H
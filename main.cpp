#include "JHMG engine.h"

//声明游戏全局变量
Game* mainGame = NULL;
gameUI* xiaoxin = NULL;
gameObject* pikaqiu = NULL;
gameObject* player = NULL;
//声明函数
void loop();
void trigle(gameObject* other);

int main(int argc, char* argv[])
{
	//创建游戏对象
	mainGame = new Game;
	//设置窗口大小和标题
	mainGame->setWindowSize(jhVector2(800,600));
	mainGame->setWindowTitle("Game");
	//设置游戏帧率
	mainGame->setTargetFrame(60);
	//设置游戏循环函数(每帧调用一次)
	mainGame->setGameLoopFunc(loop);

	//创建UI对象
	xiaoxin = new gameUI(jhVector2(0,0),jhVector2(50,50),".\\xiaoxin.png",true);
	//添加UI对象到游戏中
	mainGame->addGameUI("xiaoxin",xiaoxin);
	//创建文本UI
	gameUIText* text = new gameUIText(jhString("my game"), jhVector2(100, 100), true);
	//添加文本UI到游戏中
	mainGame->addGameUIText("text", text);
	//创建游戏对象
	player = new gameObject(new jhObject2D::circle(20,jhVector2(170,70)),".\\pkq.png",40,40,true);
	pikaqiu = new gameObject(new jhObject2D::circle(20, jhVector2(270, 70)), ".\\pkq.png", 40, 40, true);
	//绑定游戏对象碰撞事件
	player->setOnCollision(trigle);
	//添加游戏对象到游戏中
	mainGame->addGameObject("player",player);
	mainGame->addGameObject("pikaqiu", pikaqiu);

	//初始化窗口开始游戏
	mainGame->initWindow();
}

void loop()
{
	//获取键盘输入
	auto key = mainGame->Input.getKey();
	//判断键盘输入
	if (key == KeyMessage::a)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(-50,0);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::d)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(50,0);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::w)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(0,-50);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::s)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(0,50);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::space)
	{
		//删除物体
		cout << "delete pikaqiu" << endl;
		mainGame->removeGameObject("pikaqiu");
	}
	if (key == KeyMessage::esc)
	{
		//退出游戏
		exit(0);
	}
}

void trigle(gameObject* other)
{
	//碰撞输出名字
	cout<<mainGame->getName(other)<<endl;
}
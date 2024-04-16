#include "JHMG engine.h"

//声明全局游戏对象
Game* mainGame;

//声明函数
void loop();
void trigger(gameObject* other);
void onClick(int messageType, jhVector2 position);

int main(int argc, char* argv[])
{
	//创建游戏对象
	mainGame = new Game;
	//设置窗口大小和标题
	mainGame->setWindowSize(jhVector2(800, 600));
	mainGame->setWindowTitle("Game demo");
	//设置游戏帧率
	mainGame->setTargetFrame(165);
	//创建游戏场景
	gameScene* scene = new gameScene;
	//创建UI对象
	gameUI* xiaoxin = new gameUI(jhVector2(0, 0), jhVector2(50, 50), ".\\xiaoxin.png", true);
	//添加UI对象到场景中
	scene->addGameUI("xiaoxin", xiaoxin);
	//创建文本UI
	gameUIText* text = new gameUIText(jhString("fps"), jhVector2(100, 100), true);
	//添加文本UI到场景中
	scene->addGameUIText("text", text);
	//创建游戏对象
	gameObject* player = new gameObject(new jhObject2D::circle(25, jhVector2(170, 70)), ".\\pkq.png", 50, 50, true);
	//绑定游戏对象碰撞事件(物体碰撞调用)
	player->setOnCollision(trigger);
	//绑定游戏对象循环事件(每帧调用一次)
	player->setGameLoopFunc(loop);
	//添加游戏对象到场景中
	scene->addGameObject("player", player);
	//创建游戏对象
	gameObject* pikaqiu = new gameObject(new jhObject2D::circle(25, jhVector2(270, 70)), ".\\pkq.png", 50, 50, true);
	//绑定游戏对象点击事件(点击调用)
	pikaqiu->mouseAction->setClickFunc(onClick);
	//添加游戏对象到场景中
	scene->addGameObject("pikaqiu", pikaqiu);
	//添加场景到游戏中
	mainGame->setScene(scene);
	//初始化窗口开始游戏
	mainGame->initWindow();
}

void loop()
{
	//获取游戏场景
	auto scene = mainGame->getScene();
	//获取游戏对象
	auto player = scene->getGameObject("player");
	//获取UI文本对象
	auto text = scene->getGameUIText("text");
	//拼接显示fps
	text->text = "fps:" + to_string(int(1000 / mainGame->deltaTime));
	//获取键盘输入
	auto key = mainGame->Input.getKey();
	//判断键盘输入
	if (key == KeyMessage::a)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		//x = deltaX + X0 = V*t + X0
		currentPosition += jhVector2(-250, 0) * ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::d)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(250, 0) * ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::w)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(0, -250) * ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::s)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(0, 250) * ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::space)
	{
		//删除物体
		cout << "delete pikaqiu" << endl;
		scene->removeGameObject("pikaqiu");
	}
	if (key == KeyMessage::esc)
	{
		//退出游戏
		exit(0);
	}
}

void trigger(gameObject* other)
{
	//碰撞输出名字
	cout << mainGame->getScene()->getName(other) << endl;
}

void onClick(int messageType, jhVector2 position)
{
	//点击输出
	if (messageType == MouseMessage::leftDown)
		cout << "左键按下" << endl;
	if (messageType == MouseMessage::leftUp)
		cout << "左键放开" << endl;
	if (messageType == MouseMessage::rightDown)
		cout << "右键按下" << endl;
	if (messageType == MouseMessage::rightUp)
		cout << "右键放开" << endl;
}
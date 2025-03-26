#include "JHMG engine.h"
using namespace JHMG_ENGINE;

//声明全局游戏对象
Game* mainGame;

//声明函数
void loop(GameObject* self);
void trigger(GameObject* self, GameObject* other);
void onClick(int messageType, Vector2 position,GameObject* self);

int main()
{
	//创建游戏对象
	mainGame = new Game;
	//设置窗口大小和标题
	mainGame->setWindowSize(Vector2(800, 600));
	mainGame->setWindowTitle("Game demo");
	//设置游戏帧率
	mainGame->setTargetFrame(165);
	//创建游戏场景
	GameScene* scene = new GameScene;
	//添加场景到游戏中
	mainGame->setScene(scene);
	//创建UI对象
	GameUI* xiaoxin = new GameUI(Vector2(0, 0), Vector2(800, 600), ".\\background.jpg", true);
	//添加UI对象到场景中
	scene->addGameUI("xiaoxin", xiaoxin);
	//创建文本UI
	GameUIText* text = new GameUIText(String("fps"), Vector2(100, 100));
	//添加文本UI到场景中
	scene->addGameUIText("text", text);
	//创建游戏对象
	GameObject* player = new GameObject(new Circle(25, Vector2(170, 70)), ".\\pkq.png", 50, 50, true);
	//绑定游戏对象碰撞事件(物体碰撞调用)
	player->setOnCollision(trigger);
	//绑定游戏对象循环事件(每帧调用一次)
	player->setGameLoopFunc(loop);
	//添加游戏对象到场景中
	scene->addGameObject("player", player);
	//创建游戏对象
	GameObject* pikaqiu = new GameObject(new Circle(25, Vector2(270, 70)), ".\\pkq.png", 50, 50, true);
	//绑定游戏对象点击事件(点击调用)
	pikaqiu->mouseAction->setClickFunc(onClick);
	//添加游戏对象到场景中
	scene->addGameObject("pikaqiu", pikaqiu);
	//初始化窗口开始游戏
	mainGame->initWindow();
}

void loop(GameObject* self)
{
	//获取游戏场景
	auto scene = mainGame->getScene();
	//获取游戏对象
	auto player = scene->getGameObject("player");
	//获取UI文本对象
	auto text = scene->getGameUIText("text");
	//拼接显示fps
	text->text = "fps:" + std::to_string(int(1000 / mainGame->deltaTime));
	//获取键盘输入
	auto key = mainGame->input.getKey();
	//判断键盘输入
	if (key == KeyMessage::a)
	{
		Vector2 currentPosition = player->Transform.Circle->getPosition();
		//x = deltaX + X0 = V*t + X0
		currentPosition += Vector2(-250, 0) * ((float)mainGame->deltaTime / 1000);
		player->Transform.Circle->move(currentPosition);
	}
	if (key == KeyMessage::d)
	{
		Vector2 currentPosition = player->Transform.Circle->getPosition();
		currentPosition += Vector2(250, 0) * ((float)mainGame->deltaTime / 1000);
		player->Transform.Circle->move(currentPosition);
	}
	if (key == KeyMessage::w)
	{
		Vector2 currentPosition = player->Transform.Circle->getPosition();
		currentPosition += Vector2(0, -250) * ((float)mainGame->deltaTime / 1000);
		player->Transform.Circle->move(currentPosition);
	}
	if (key == KeyMessage::s)
	{
		Vector2 currentPosition = player->Transform.Circle->getPosition();
		currentPosition += Vector2(0, 250) * ((float)mainGame->deltaTime / 1000);
		player->Transform.Circle->move(currentPosition);
	}
	if (key == KeyMessage::space)
	{
		//删除物体
		std::cout << "delete pikaqiu" << std::endl;
		scene->removeGameObject("pikaqiu");
	}
	if (key == KeyMessage::esc)
	{
		//退出游戏
		exit(0);
	}
}

void trigger(GameObject* self,GameObject* other)
{
	//碰撞输出名字
	std::cout << mainGame->getScene()->getName(other) << std::endl;
}

void onClick(int messageType, Vector2 position,GameObject* self)
{
	std::cout<<mainGame->getScene()->getName(self)<< std::endl;
	//点击输出
	if (messageType == MouseMessage::leftDown)
		std::cout << "左键按下" << std::endl;
	if (messageType == MouseMessage::leftUp)
		std::cout << "左键放开" << std::endl;
	if (messageType == MouseMessage::rightDown)
		std::cout << "右键按下" << std::endl;
	if (messageType == MouseMessage::rightUp)
		std::cout << "右键放开" << std::endl;
}
#include "JHMG engine.h"
using namespace JHMG_ENGINE;

//����ȫ����Ϸ����
Game* mainGame;

//��������
void loop(GameObject* self);
void trigger(GameObject* self, GameObject* other);
void onClick(int messageType, Vector2 position,GameObject* self);

int main()
{
	//������Ϸ����
	mainGame = new Game;
	//���ô��ڴ�С�ͱ���
	mainGame->setWindowSize(Vector2(800, 600));
	mainGame->setWindowTitle("Game demo");
	//������Ϸ֡��
	mainGame->setTargetFrame(165);
	//������Ϸ����
	GameScene* scene = new GameScene;
	//��ӳ�������Ϸ��
	mainGame->setScene(scene);
	//����UI����
	GameUI* xiaoxin = new GameUI(Vector2(0, 0), Vector2(800, 600), ".\\background.jpg", true);
	//���UI���󵽳�����
	scene->addGameUI("xiaoxin", xiaoxin);
	//�����ı�UI
	GameUIText* text = new GameUIText(String("fps"), Vector2(100, 100));
	//����ı�UI��������
	scene->addGameUIText("text", text);
	//������Ϸ����
	GameObject* player = new GameObject(new Circle(25, Vector2(170, 70)), ".\\pkq.png", 50, 50, true);
	//����Ϸ������ײ�¼�(������ײ����)
	player->setOnCollision(trigger);
	//����Ϸ����ѭ���¼�(ÿ֡����һ��)
	player->setGameLoopFunc(loop);
	//�����Ϸ���󵽳�����
	scene->addGameObject("player", player);
	//������Ϸ����
	GameObject* pikaqiu = new GameObject(new Circle(25, Vector2(270, 70)), ".\\pkq.png", 50, 50, true);
	//����Ϸ�������¼�(�������)
	pikaqiu->mouseAction->setClickFunc(onClick);
	//�����Ϸ���󵽳�����
	scene->addGameObject("pikaqiu", pikaqiu);
	//��ʼ�����ڿ�ʼ��Ϸ
	mainGame->initWindow();
}

void loop(GameObject* self)
{
	//��ȡ��Ϸ����
	auto scene = mainGame->getScene();
	//��ȡ��Ϸ����
	auto player = scene->getGameObject("player");
	//��ȡUI�ı�����
	auto text = scene->getGameUIText("text");
	//ƴ����ʾfps
	text->text = "fps:" + std::to_string(int(1000 / mainGame->deltaTime));
	//��ȡ��������
	auto key = mainGame->input.getKey();
	//�жϼ�������
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
		//ɾ������
		std::cout << "delete pikaqiu" << std::endl;
		scene->removeGameObject("pikaqiu");
	}
	if (key == KeyMessage::esc)
	{
		//�˳���Ϸ
		exit(0);
	}
}

void trigger(GameObject* self,GameObject* other)
{
	//��ײ�������
	std::cout << mainGame->getScene()->getName(other) << std::endl;
}

void onClick(int messageType, Vector2 position,GameObject* self)
{
	std::cout<<mainGame->getScene()->getName(self)<< std::endl;
	//������
	if (messageType == MouseMessage::leftDown)
		std::cout << "�������" << std::endl;
	if (messageType == MouseMessage::leftUp)
		std::cout << "����ſ�" << std::endl;
	if (messageType == MouseMessage::rightDown)
		std::cout << "�Ҽ�����" << std::endl;
	if (messageType == MouseMessage::rightUp)
		std::cout << "�Ҽ��ſ�" << std::endl;
}
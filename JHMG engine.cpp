#include "JHMG engine.h"
using namespace JHMG_ENGINE;
static bool canOperator = true;
#define CHECK if(canOperator == false){canOperator = true;break;}
#define CHECK_n if(canOperator == false){break;}

GameObject::GameObject(Circle* Transform, String file, int width, int height, bool visible)
{
	this->Transform.Circle = Transform;
	this->transformType = 'c';
	IMAGE* img = new IMAGE;
	loadimage(img, file.to_char(), width, height, true);
	this->image = img;
	this->mouseAction = new MouseAction<GameObject*>;
	this->mouseAction->beginPosition = Transform->getLeftTopPosition();
	this->mouseAction->endPosition = Transform->getLeftTopPosition() + Vector2(width, height);
	this->mouseAction->self = this;
	this->visible = visible;
	imgRelease = true;
}

GameObject::GameObject(Circle* Transform, IMAGE* image, bool visible)
{
	this->Transform.Circle = Transform;
	this->transformType = 'c';
	this->image = image;
	this->mouseAction = new MouseAction<GameObject*>;
	this->mouseAction->beginPosition = Transform->getLeftTopPosition();
	this->mouseAction->endPosition = Transform->getLeftTopPosition() + Vector2(image->getwidth(), image->getheight());
	this->mouseAction->self = this;
	this->visible = visible;
	imgRelease = false;
}

GameObject::GameObject(Rectangle* Transform, String file, int width, int height, bool visible)
{
	this->Transform.Rectangle = Transform;
	this->transformType = 'r';
	IMAGE* img = new IMAGE;
	loadimage(img, file.to_char(), width, height, true);
	this->image = img;
	this->mouseAction = new MouseAction<GameObject*>;
	this->mouseAction->beginPosition = Transform->getLeftTopPosition();
	this->mouseAction->endPosition = Transform->getLeftTopPosition() + Vector2(width, height);
	this->mouseAction->self = this;
	this->visible = visible;
	imgRelease = true;
}

GameObject::GameObject(Rectangle* Transform, IMAGE* image, bool visible)
{
	this->Transform.Rectangle = Transform;
	this->transformType = 'r';
	this->image = image;
	this->mouseAction = new MouseAction<GameObject*>;
	this->mouseAction->beginPosition = Transform->getLeftTopPosition();
	this->mouseAction->endPosition = Transform->getLeftTopPosition() + Vector2(image->getwidth(), image->getheight());
	this->mouseAction->self = this;
	this->visible = visible;
	imgRelease = false;
}

GameObject::GameObject(Diamond* Transform, String file, int width, int height, bool visible)
{
	this->Transform.Diamond = Transform;
	this->transformType = 'd';
	IMAGE* img = new IMAGE;
	loadimage(img, file.to_char(), width, height, true);
	this->image = img;
	this->mouseAction = new MouseAction<GameObject*>;
	this->mouseAction->beginPosition = Transform->getLeftTopPosition();
	this->mouseAction->endPosition = Transform->getLeftTopPosition() + Vector2(width, height);
	this->mouseAction->self = this;
	this->visible = visible;
	imgRelease = true;
}

GameObject::GameObject(Diamond* Transform, IMAGE* image, bool visible)
{
	this->Transform.Diamond = Transform;
	this->transformType = 'd';
	this->image = image;
	this->mouseAction = new MouseAction<GameObject*>;
	this->mouseAction->beginPosition = Transform->getLeftTopPosition();
	this->mouseAction->endPosition = Transform->getLeftTopPosition() + Vector2(image->getwidth(), image->getheight());
	this->mouseAction->self = this;
	this->visible = visible;
	imgRelease = false;
}

GameObject::GameObject(Triangle* Transform, String file, int width, int height, bool visible)
{
	this->Transform.Triangle = Transform;
	this->transformType = 't';
	IMAGE* img = new IMAGE;
	loadimage(img, file.to_char(), width, height, true);
	this->image = img;
	this->mouseAction = new MouseAction<GameObject*>;
	this->mouseAction->beginPosition = Transform->getLeftTopPosition();
	this->mouseAction->endPosition = Transform->getLeftTopPosition() + Vector2(width, height);
	this->mouseAction->self = this;
	this->visible = visible;
	imgRelease = true;
}

GameObject::GameObject(Triangle* Transform, IMAGE* image, bool visible)
{
	this->Transform.Triangle = Transform;
	this->transformType = 't';
	this->image = image;
	this->mouseAction = new MouseAction<GameObject*>;
	this->mouseAction->beginPosition = Transform->getLeftTopPosition();
	this->mouseAction->endPosition = Transform->getLeftTopPosition() + Vector2(image->getwidth(), image->getheight());
	this->mouseAction->self = this;
	this->visible = visible;
	imgRelease = false;
}

GameObject* GameObject::setOnCollision(void(*onCollision)(GameObject* self, GameObject* GameObject))
{
	this->onCollision = onCollision;
	return this;
}

GameObject* GameObject::setGameLoopFunc(void(*gameLoopFunc)(GameObject* self))
{
	this->gameLoopFunc = gameLoopFunc;
	return this;
}

GameObject* GameObject::changeImage(LPCTSTR file, Vector2 size)
{
	imgRelease = true;
	IMAGE* img = new IMAGE;
	loadimage(img, file, size.x, size.y, true);
	delete this->image;
	this->image = img;
	return this;
}

GameObject* GameObject::changeImage(IMAGE* image, bool release)
{
	if (release)
		delete this->image;
	this->image = image;
	return this;
}

GameObject::~GameObject()
{
	if (this->transformType == 'c')
		delete this->Transform.Circle;
	else if (this->transformType == 'r')
		delete this->Transform.Rectangle;
	else if (this->transformType == 'd')
		delete this->Transform.Diamond;
	else if (this->transformType == 't')
		delete this->Transform.Triangle;
	if (imgRelease)
		delete this->image;
	delete this->mouseAction;
	this->Transform.Circle = NULL;
	this->Transform.Rectangle = NULL;
	this->Transform.Diamond = NULL;
	this->Transform.Triangle = NULL;
	this->image = NULL;
	this->mouseAction = NULL;
}


GameUI* GameUI::setGameLoopFunc(void(*gameLoopFunc)(GameUI* self))
{
	this->gameLoopFunc = gameLoopFunc;
	return this;
}

GameUI::GameUI(Vector2 position, Vector2 size, String image, bool visible)
{
	this->position = position;
	this->size = size;
	IMAGE* img = new IMAGE;
	loadimage(img, image.to_char(), size.x, size.y, true);
	this->image = img;
	this->mouseAction = new MouseAction<GameUI*>;
	this->mouseAction->beginPosition = position;
	this->mouseAction->endPosition = position + size;
	this->mouseAction->self = this;
	this->visible = visible;
	imgRelease = true;
}

GameUI::GameUI(Vector2 position, IMAGE* image, bool visible)
{
	this->position = position;
	this->image = image;
	this->mouseAction = new MouseAction<GameUI*>;
	this->mouseAction->beginPosition = position;
	this->mouseAction->endPosition = position + Vector2(image->getwidth(), image->getheight());
	this->mouseAction->self = this;
	this->visible = visible;
	imgRelease = false;
}

GameUI* GameUI::changeImage(LPCTSTR file, Vector2 size)
{
	IMAGE* img = new IMAGE;
	loadimage(img, file, size.x, size.y, true);
	delete this->image;
	this->image = img;
	imgRelease = true;
	return this;
}

GameUI* GameUI::changeImage(IMAGE* image,bool release)
{
	if (release)
	delete this->image;
	this->image = image;
	imgRelease = false;
	return this;
}

GameUI::~GameUI()
{
	if (imgRelease)
		delete this->image;
	delete this->mouseAction;
	this->image = NULL;
	this->mouseAction = NULL;
}

void GameSound::open(String name, String music_file)
{
	this->name = name;
	char command[256];
	sprintf(command, "open %s alias %s", music_file.to_char(), name.to_char());
	mciSendString(command, NULL, 0, NULL);
}

void GameSound::play(bool repeat)
{
	char command[256];
	if (repeat)
		sprintf(command, "play %s repeat", name.to_char());
	else
		sprintf(command, "play %s from 0", name.to_char());
	mciSendString(command, NULL, 0, NULL);
}

void GameSound::stop()
{
	char command[256];
	sprintf(command, "stop %s", name.to_char());
	mciSendString(command, NULL, 0, NULL);
}

void GameSound::pause()
{
	char command[256];
	sprintf(command, "pause %s", name.to_char());
	mciSendString(command, NULL, 0, NULL);
}

void GameSound::resume()
{
	char command[256];
	sprintf(command, "resume %s", name.to_char());
	mciSendString(command, NULL, 0, NULL);
}

void GameSound::setVolume(int volume)
{
	char command[256];
	sprintf(command, "setaudio %s volume to %d", name.to_char(), volume);
	mciSendString(command, NULL, 0, NULL);
}

int GameSound::getVolume()
{
	char command[256];
	sprintf(command, "status %s volume", name.to_char());
	char result[256];
	mciSendString(command, result, 256, NULL);
	int volume;
	sscanf(result, "%d", &volume);
	return volume;
}

void GameSound::setPosition(int position)
{
	char command[256];
	sprintf(command, "seek %s to %d", name.to_char(), position);
	mciSendString(command, NULL, 0, NULL);
}

int GameSound::getPosition()
{
	char command[256];
	sprintf(command, "status %s position", name.to_char());
	char result[256];
	mciSendString(command, result, 256, NULL);
	int position;
	sscanf(result, "%d", &position);
	return position;
}

int GameSound::getLength()
{
	char command[256];
	sprintf(command, "status %s length", name.to_char());
	char result[256];
	mciSendString(command, result, 256, NULL);
	int length;
	sscanf(result, "%d", &length);
	return length;
}

int GameSound::getState()
{
	char command[256];
	sprintf(command, "status %s mode", name.to_char());
	char result[256];
	mciSendString(command, result, 256, NULL);
	int state;
	sscanf(result, "%d", &state);
	return state;
}

void GameSound::close()
{
	char command[256];
	sprintf(command, "close %s", name.to_char());
	mciSendString(command, NULL, 0, NULL);
}

GameSound::~GameSound()
{
	char command[256];
	sprintf(command, "close %s", name.to_char());
	mciSendString(command, NULL, 0, NULL);
}

void Game::setWindowSize(Vector2 windowSize)
{
	this->windowSize = windowSize;
}

void Game::setWindowTitle(String windowTitle)
{
	this->windowTitle = windowTitle;
}


void Game::initWindow()
{
	this->window = initgraph(windowSize.x, windowSize.y);
	SetWindowText(window, windowTitle.to_char());
	if (this->Scene->awake != NULL)
		this->Scene->awake();
	setbkmode(TRANSPARENT);
	this->gameLoop();
}

void Game::setScene(GameScene* Scene)
{
	this->Scene = Scene;
}

void Game::setTargetFrame(int targetFrame)
{
	if (targetFrame > 0)
		this->targetFrame = targetFrame;
	else
		this->targetFrame = 60;
}

void Game::close()
{
	isRun = false;
}

void Game::gameLoop()
{
	clock_t endtime = 0, starttime = 0;
	//游戏循环
	BeginBatchDraw();
	while (isRun)
	{
		endtime = clock();
		canOperator = true;
		///判断窗口是否关闭
		if (GetHWnd() == NULL)
		{
			isRun = false;
			break;
		}
		//判断场景是否为空
		if (this->Scene == NULL)
		{
			throw std::invalid_argument("The scene is empty");
			return;
		}
		//按帧循环
		while (endtime - starttime >= 1000 / targetFrame)
		{
			//清屏
			cleardevice();
			//消息变量
			ExMessage msg;
			bool isMessage = peekmessage(&msg);
			//调用场景循环函数
			if (this->Scene->gameLoop != NULL)
				this->Scene->gameLoop();

			//遍历界面
			for (auto it = this->Scene->gameUIs.p_first; it != NULL; it = it->p_next)
			{
				if (it->value->visible)
					putimagePNG(it->value->position.x, it->value->position.y, it->value->image);
				//调用界面循环函数
				if (it->value->gameLoopFunc != NULL)
					it->value->gameLoopFunc(it->value);
				CHECK
					//获取消息
					while (isMessage)
					{
						//调用鼠标事件
						it->value->mouseAction->getMouseMessage(msg);
						//获取键盘输入
						input.getMessage(msg);
						break;
					}
			}
			//遍历物体
			for (auto it = this->Scene->gameObjects.p_first; it != NULL; it = it->p_next)
			{
				//打印物体
				if (it->value)
				{
					if (it->value->visible)
					{
						if (it->value->transformType == 'c')
						{
							putimagePNG(it->value->Transform.Circle->getLeftTopPosition().x, it->value->Transform.Circle->getLeftTopPosition().y, it->value->image);
							it->value->mouseAction->beginPosition = it->value->Transform.Circle->getLeftTopPosition();
							it->value->mouseAction->endPosition = it->value->Transform.Circle->getLeftTopPosition() + Vector2(it->value->image->getwidth(), it->value->image->getheight());
						}
						else if (it->value->transformType == 'r')
						{
							putimagePNG(it->value->Transform.Rectangle->getLeftTopPosition().x, it->value->Transform.Rectangle->getLeftTopPosition().y, it->value->image);
							it->value->mouseAction->beginPosition = it->value->Transform.Rectangle->getLeftTopPosition();
							it->value->mouseAction->endPosition = it->value->Transform.Rectangle->getLeftTopPosition() + Vector2(it->value->image->getwidth(), it->value->image->getheight());
						}
						else if (it->value->transformType == 'd')
						{
							putimagePNG(it->value->Transform.Diamond->getLeftTopPosition().x, it->value->Transform.Diamond->getLeftTopPosition().y, it->value->image);
							it->value->mouseAction->beginPosition = it->value->Transform.Diamond->getLeftTopPosition();
							it->value->mouseAction->endPosition = it->value->Transform.Diamond->getLeftTopPosition() + Vector2(it->value->image->getwidth(), it->value->image->getheight());
						}
						else if (it->value->transformType == 't')
						{
							putimagePNG(it->value->Transform.Triangle->getLeftTopPosition().x, it->value->Transform.Triangle->getLeftTopPosition().y, it->value->image);
							it->value->mouseAction->beginPosition = it->value->Transform.Triangle->getLeftTopPosition();
							it->value->mouseAction->endPosition = it->value->Transform.Triangle->getLeftTopPosition() + Vector2(it->value->image->getwidth(), it->value->image->getheight());
						}
					}
				}
				//调用物体循环函数
				if (it->value->gameLoopFunc != NULL)
				{
					it->value->gameLoopFunc(it->value);
				}
				CHECK
					//获取消息
					while (isMessage)
					{
						//调用鼠标事件
						it->value->mouseAction->getMouseMessage(msg);
						//获取键盘输入
						input.getMessage(msg);
						break;
					}
				//遍历其他物体计算碰撞
				if (it->value->onCollision != NULL)
				{
					for (auto it2 = this->Scene->gameObjects.p_first; it2 != NULL; it2 = it2->p_next)
					{
						if (it != it2)
						{
							if (it2->value->transformType == 'c')
							{
								if (it->value->Transform.Circle->isTriggerEnter(*it2->value->Transform.Circle))
								{
									it->value->onCollision(it->value,it2->value);
									CHECK_n
								}
							}
							else if (it2->value->transformType == 'r')
							{
								if (it->value->Transform.Circle->isTriggerEnter(*it2->value->Transform.Rectangle))
								{
									it->value->onCollision(it->value, it2->value);
									CHECK_n
								}
							}
							else if (it2->value->transformType == 'd')
							{
								if (it->value->Transform.Circle->isTriggerEnter(*it2->value->Transform.Diamond))
								{
									it->value->onCollision(it->value, it2->value);
									CHECK_n
								}
							}
							else if (it2->value->transformType == 't')
							{
								if (it->value->Transform.Circle->isTriggerEnter(*it2->value->Transform.Triangle))
								{
									it->value->onCollision(it->value, it2->value);
									CHECK_n
								}
							}
						}
					}
					CHECK
				}
			}
			//遍历界面文本
			for (auto it = this->Scene->gameUITexts.p_first; it != NULL; it = it->p_next)
			{
				settextcolor(it->value->color);
				settextstyle(it->value->size.y, it->value->size.x, _T("宋体"));
				if (it->value->visible)
					outtextxy(it->value->position.x, it->value->position.y, it->value->text.to_char());
			}
			//清除消息缓存
			flushmessage(-1);
			//清除打印缓存
			FlushBatchDraw();
			deltaTime = endtime - starttime;
			starttime = clock();
		}
	}
	EndBatchDraw();
}

Vector2 Game::getWindowSize()
{
	return windowSize;
}

String Game::getWindowTitle()
{
	return windowTitle;
}

GameScene* Game::getScene()
{
	return Scene;
}

GameScene::~GameScene()
{
	for (auto it = this->gameObjects.p_first; it != NULL; it = it->p_next)
	{
		this->removeGameObject(this->getName(it->value));
	}
	for (auto it = this->gameUIs.p_first; it != NULL; it = it->p_next)
	{
		this->removeGameUI(this->getName(it->value));
	}
	for (auto it = this->gameUITexts.p_first; it != NULL; it = it->p_next)
	{
		this->removeGameUIText(this->getName(it->value));
	}
}

void GameScene::addGameObject(String name, GameObject* gameObject_pre)
{
	if (this->gameTotalMap[name] >= 100)
	{
		throw std::invalid_argument("The name already exists");
		return;
	}
	this->gameObjects.addList(gameObject_pre);
	this->gameObjectsMap[name] = gameObject_pre;
	this->gameTotalMap[name] += 100;
	gameObject_pre->refCount++;
}

void GameScene::removeGameObject(String name)
{
	for (auto it = this->gameObjects.p_first; it != NULL; it = it->p_next)
	{
		if (it->value == gameObjectsMap[name])
		{
			if (it->value->refCount == 1)
			{
				canOperator = false;
				delete it->value;
				it->value = NULL;
				this->gameObjects.deleteList(it);
			}
			else
			{
				it->value->refCount--;
			}
			this->gameObjectsMap.erase(name);
			this->gameTotalMap[name] -= 100;
			return;
		}
	}
}

GameObject* GameScene::getGameObject(String name)
{
	return this->gameObjectsMap[name];
}

String GameScene::getName(GameObject* GameObject)
{
	for (auto it : gameObjectsMap)
	{
		if (it.second == GameObject)
		{
			return it.first;
		}
	}
	return String();
}

String GameScene::getName(GameUI* GameUI)
{
	for (auto it : gameUIMap)
	{
		if (it.second == GameUI)
		{
			return it.first;
		}
	}
	return String();
}

String GameScene::getName(GameUIText* GameUIText)
{
	for (auto it : gameUITextsMap)
	{
		if (it.second == GameUIText)
		{
			return it.first;
		}
	}
	return String();
}

void GameScene::addGameUI(String name, GameUI* GameUI)
{
	if (this->gameTotalMap[name] % 100 >= 10)
	{
		throw std::invalid_argument("The name already exists");
		return;
	}
	this->gameUIs.addList(GameUI);
	this->gameUIMap[name] = GameUI;
	this->gameTotalMap[name] += 10;
	GameUI->refCount++;
}

void GameScene::addGameUIText(String name, GameUIText* text)
{
	if (this->gameTotalMap[name] % 10 >= 1)
	{
		throw std::invalid_argument("The name already exists");
		return;
	}
	this->gameUITexts.addList(text);
	this->gameUITextsMap[name] = text;
	this->gameTotalMap[name] += 1;
	text->refCount++;
}

void GameScene::removeGameUI(String name)
{
	for (auto it = this->gameUIs.p_first; it != NULL; it = it->p_next)
	{
		if (it->value == gameUIMap[name])
		{
			if (it->value->refCount == 1)
			{
				canOperator = false;
				delete it->value;
				it->value = NULL;
				this->gameUIs.deleteList(it);
			}
			else
			{
				it->value->refCount--;
			}
			this->gameTotalMap[name] -= 10;
			return;
		}
	}
}

void GameScene::removeGameUIText(String name)
{
	for (auto it = this->gameUITexts.p_first; it != NULL; it = it->p_next)
	{
		if (it->value == gameUITextsMap[name])
		{
			if (it->value->refCount == 1)
			{
				canOperator = false;
				delete it->value;
			}
			else
			{
				it->value->refCount--;
			}
			this->gameUITexts.deleteList(it);
			this->gameTotalMap[name] -= 1;
			return;
		}
	}
}

GameUI* GameScene::getGameUI(String name)
{
	return this->gameUIMap[name];
}

GameUIText* GameScene::getGameUIText(String name)
{
	return this->gameUITextsMap[name];
}

void GameScene::setGameLoopFunc(void(*gameLoop)())
{
	this->gameLoop = gameLoop;
}

void GameScene::setAwakeFunc(void(*awake)())
{
	this->awake = awake;
}

void GameInput::getMessage(const ExMessage& msg)
{

	if (msg.message == WM_KEYDOWN)
	{
		if(msg.vkcode != 0x1B)
		this->key = msg.vkcode;
	}
	else if (msg.message == WM_KEYUP)
	{
		this->key = 0;
	}

}

char GameInput::getKey()
{
	return this->key;
}

GameUIText::GameUIText(String text, Vector2 position, COLORREF color, Vector2 size, bool visible)
{
	this->text = text;
	this->color = color;
	this->size = size;
	this->position = position;
	this->visible = visible;
}

template<class T>
void MouseAction<T>::getMouseMessage(const ExMessage& msg)
{
	if (msg.message == WM_LBUTTONDOWN)
	{
		if (msg.x >= beginPosition.x && msg.x <= endPosition.x && msg.y >= beginPosition.y && msg.y <= endPosition.y)
		{
			if (onClick != NULL)
				onClick(MouseMessage::leftDown, Vector2(msg.x, msg.y), self);
		}
	}
	if (msg.message == WM_LBUTTONUP)
	{
		if (msg.x >= beginPosition.x && msg.x <= endPosition.x && msg.y >= beginPosition.y && msg.y <= endPosition.y)
		{
			if (onClick != NULL)
				onClick(MouseMessage::leftUp, Vector2(msg.x, msg.y), self);
		}
	}
	if (msg.message == WM_RBUTTONDOWN)
	{
		if (msg.x >= beginPosition.x && msg.x <= endPosition.x && msg.y >= beginPosition.y && msg.y <= endPosition.y)
		{
			if (onClick != NULL)
				onClick(MouseMessage::rightDown, Vector2(msg.x, msg.y), self);
		}
	}
	if (msg.message == WM_RBUTTONUP)
	{
		if (msg.x >= beginPosition.x && msg.x <= endPosition.x && msg.y >= beginPosition.y && msg.y <= endPosition.y)
		{
			if (onClick != NULL)
				onClick(MouseMessage::rightUp, Vector2(msg.x, msg.y), self);
		}
	}
	if (msg.message == WM_MOUSEMOVE)
	{
		this->mousePosition.x = msg.x;
		this->mousePosition.y = msg.y;
	}
}

template<class T>
void MouseAction<T>::setClickFunc(void(*onClick)(int mouseMessage, Vector2 position, T self))
{
	this->onClick = onClick;
}

template<class T>
Vector2 MouseAction<T>::getMousePosition()
{
	return this->mousePosition;
}

GameInputBox::GameInputBox(String* inputText, String title, String prompt, String defaultText, int max, Vector2 size)
{
	this->inputText = inputText;
	this->title = title;
	this->prompt = prompt;
	this->defaultText = defaultText;
	this->maxInput = max;
	this->size = size;
}

void GameInputBox::show()
{
	InputBox(inputText->to_char(), this->maxInput, this->prompt.to_char(), this->title.to_char(), this->defaultText.to_char(), this->size.x, this->size.y);
}

GameMessageBox::GameMessageBox(String title, String message)
{
	this->title = title;
	this->message = message;
}

void GameMessageBox::show()
{
	MessageBox(GetHWnd(), message.to_char(), title.to_char(), MB_OK);
}



std::ostream& JHMG_ENGINE::operator<<(std::ostream& cout, const JHMG_ENGINE::String& m_str)
{
	std::cout << m_str.m_str;
	return cout;
}

std::istream& JHMG_ENGINE::operator>>(std::istream& cin, const JHMG_ENGINE::String& m_str)
{
	cin >> m_str.m_str;
	return cin;
}

String::String()
{
	this->m_str = "";
}

String::String(const std::string& m_str)
{
	this->m_str = m_str;
}

String::String(const char* m_str)
{
	this->m_str = std::string(m_str);
}

String::String(const String& m_str)
{
	this->m_str = m_str.m_str;
}

String String::operator+(const String& m_str)
{
	return String(this->m_str + m_str.m_str);
}

String String::operator+(const std::string& m_str)
{
	return String(this->m_str + m_str);
}

void String::operator=(const String& m_str)
{
	this->m_str = m_str.m_str;
}

void String::operator=(const std::string& m_str)
{
	this->m_str = m_str;
}

void String::operator+=(const String& m_str)
{
	this->m_str += m_str.m_str;
}

void String::operator+=(const std::string& m_str)
{
	this->m_str += m_str;
}

bool String::operator==(const String& m_str)
{
	if (this->m_str == m_str.m_str)
	{
		return true;
	}

	else return false;
}

bool String::operator<(const String& m_str)const
{
	if (this->m_str < m_str.m_str)
	{
		return true;
	}

	else return false;
}

bool String::operator>(const String& m_str)const
{
	if (this->m_str > m_str.m_str)
	{
		return true;
	}

	else return false;
}

int String::to_int()
{
	return atoi(this->m_str.c_str());
}

char* String::to_char()
{
	return (char*)(this->m_str.c_str());
}

float String::to_float()
{
	return atof(this->m_str.c_str());
}

int String::indexOf(const std::string& m_str)
{
	return this->m_str.find(m_str);
}

int String::indexOf(const String& m_str)
{
	return this->m_str.find(m_str.m_str);
}

std::string String::to_stdString()
{
	return this->m_str;
}

std::string String::substr(int begin, int end)
{
	if (end <= begin)
		return this->m_str.substr(begin, end - begin + 1);
	else
		return this->m_str;
}

std::string String::substr(const std::string& leftStr, const std::string& rightStr)//取出中间字符串
{
	int left = this->m_str.find(leftStr);
	int right;
	if (left == -1)
	{
		return "";//找不到左边，返回空
	}

	else
	{
		right = this->m_str.find(rightStr, left);
	}

	if (right != -1)//找到右边
	{
		return this->m_str.substr(left + leftStr.length(), right - (left + leftStr.length()));
	}

	else//找不到右边，截取从左边到末尾
	{
		return this->m_str.substr(left + 1);
	}

}


std::ostream& JHMG_ENGINE::operator<<(std::ostream& cout, const Fraction& num)
{
	if (num.m != 1 && num.s != 0)
		cout << num.s << "/" << num.m;
	else
		cout << num.s;
	return cout;
}

std::istream& JHMG_ENGINE::operator>>(std::istream& cin, Fraction& num)
{
	int s, m;
	scanf("%d/%d", &s, &m);
	num.s = s;
	if (m != 0)
		num.m = m;
	else
		num.m = 1;
	num.simplify();
	return cin;
}

void Fraction::simplify()
{
	if (s >= 0 && m > 0)
	{
		for (int i = 1; i <= (s < m ? s : m); i++)
		{
			if (s % i == 0 && m % i == 0)
			{
				s /= i; m /= i;
				i = 1;
			}

		}

	}

	if (s <= 0 && m > 0)
	{
		s = -s;
		for (int i = 1; i <= (s < m ? s : m); i++)
		{
			if (s % i == 0 && m % i == 0)
			{
				s /= i; m /= i;
				i = 1;
			}

		}

		s = -s;
	}

}

void Fraction::print()
{
	std::cout << s << "/" << m;
}

Fraction::Fraction()
{
	s = 0; m = 1;
}

Fraction::Fraction(const Fraction& num)
{
	s = num.s;
	m = num.m;
}

Fraction::Fraction(int sm)
{
	s = sm;
	m = 1;
}

Fraction::Fraction(double num)
{
	int M = 1;
	while (num - int(num) != 0)
	{
		num *= 10;
		M *= 10;
	}

	s = num; m = M;
	simplify();
}

Fraction::Fraction(int s, int m)
{
	if ((s < 0 && m < 0) || (s > 0 && m < 0))
	{
		s = -s; m = -m;
	}

	this->s = s;
	if (m != 0)
		this->m = m;
	else
		this->m = 1;
	simplify();
}

float Fraction::to_float()
{
	return float(s) / m;
}

Fraction Fraction::operator+(const Fraction& num)
{
	return Fraction(this->s * num.m + this->m * num.s, this->m * num.m);
}

Fraction Fraction::operator+(float num)
{
	return Fraction(this->to_float() + num);
}

Fraction& Fraction::operator+=(float num)
{
	*this = *this + num;
	return *this;
}

Fraction Fraction::operator-(const Fraction& num)
{
	return Fraction(this->s * num.m - this->m * num.s, this->m * num.m);
}

Fraction Fraction::operator-(float num)
{
	return Fraction(this->to_float() - num);
}

Fraction Fraction::operator*(const Fraction& num)
{
	return Fraction(this->s * num.s, this->m * num.m);
}

Fraction Fraction::operator*(float num)
{
	return Fraction(this->to_float() * num);
}

Fraction Fraction::operator*=(float num)
{
	*this = *this * num;
	return *this;
}

Fraction Fraction::operator=(const Fraction& num)
{
	this->s = num.s;
	this->m = num.m;
	return *this;
}

Fraction Fraction::operator/(const Fraction& num)
{
	return Fraction(this->s * num.m, this->m * num.s);
}

Fraction Fraction::operator/(float num)
{
	return Fraction(this->to_float() / num);
}

Fraction Fraction::operator/=(float num)
{
	if (num != 0)
	{
		*this = *this / num;
	}

	else
	{
		throw std::invalid_argument("Can't be divided by 0");
	}

	return *this;
}

bool Fraction::operator>(const Fraction& num)
{
	if (this->s * num.m - num.s - this->m > 0)
		return true;
	else
		return false;
}

bool Fraction::operator>(float num)
{
	if (this->to_float() > num)
		return true;
	else
		return false;
}

bool Fraction::operator>=(const Fraction& num)
{
	if (*this > num || *this == num)
	{
		return true;
	}

	else
		return false;
}

bool Fraction::operator>=(float num)
{
	if (this->to_float() >= num)
		return true;
	else
		return false;
}

bool Fraction::operator<=(const Fraction& num)
{
	if (*this < num || *this == num)
	{
		return true;
	}

	else
		return false;
}

bool Fraction::operator<=(float num)
{
	if (this->to_float() <= num)
		return true;
	else
		return false;
}

bool Fraction::operator<(const Fraction& num)
{
	if (this->s * num.m - num.s - this->m > 0)
		return false;
	else
		return true;
}

bool Fraction::operator<(float num)
{
	if (this->to_float() < num)
		return true;
	else
		return false;
}

bool Fraction::operator==(const Fraction& num)
{
	if (this->s * num.m - num.s - this->m == 0)
		return true;
	else
		return false;
}

bool Fraction::operator==(float num)
{
	if (this->to_float() == num)
		return true;
	else
		return false;
}

Fraction& Fraction::operator+=(const Fraction& num)
{
	*this = *this + num;
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& num)
{
	*this = *this - num;
	return *this;
}

Fraction& Fraction::operator-=(float num)
{
	*this = *this - num;
	return *this;
}

Vector2::Vector2()
{
	x = 0; y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& v2)
{
	this->x = v2.x;
	this->y = v2.y;
}

Vector2& Vector2::operator=(const Vector2& v2)
{
	this->x = v2.x;
	this->y = v2.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& v2)
{
	return Vector2(this->x + v2.x, this->y + v2.y);
}

Vector2& Vector2::operator+=(const Vector2& v2)
{
	this->x += v2.x;
	this->y += v2.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& v2)
{
	return Vector2(this->x - v2.x, this->y - v2.y);
}

Vector2& Vector2::operator-=(const Vector2& v2)
{
	this->x -= v2.x;
	this->y -= v2.y;
	return *this;
}

Vector2 Vector2::operator*(float i)
{
	return Vector2(this->x * i, this->y * i);
}

Vector2 Vector2::operator/(float i)
{
	return Vector2(this->x / i, this->y / i);
}

bool Vector2::operator==(const Vector2& v2)
{
	if (this->x == v2.x && this->y == v2.y)
		return true;
	else
		return false;
}

double Vector2::destance(const Vector2& obj)
{
	return sqrt(pow(this->x - obj.x, 2) + pow(this->y - obj.y, 2));
}

double Vector2::cross_product(const Vector2& objective)
{
	return this->x * objective.y - this->y * objective.x;
}

double Vector2::dot_product(const Vector2& objective)
{
	return this->x * objective.x + this->y * objective.y;
}

void Vector2::rotate(const Vector2& center, float angle)
{
	float s = sin(angle);
	float c = cos(angle);
	this->x = (x - center.x) * c - (y - center.y) * s + center.x;
	this->y = (x - center.x) * s + (y - center.y) * c + center.y;
}

template<class T>
inline void List<T>::addList(T value)
{
	node* newlist = new node;
	newlist->p_next = NULL;
	newlist->value = value;
	if (this->p_first == NULL)
	{
		this->p_first = newlist;
		newlist->p_back = NULL;
	}

	else
	{
		node* p = this->p_first;
		while (p->p_next != NULL)
		{
			p = p->p_next;
		}

		newlist->p_back = p;
		p->p_next = newlist;
	}

}

template<class T>
inline void List<T>::deleteList(node* list)
{
	if (list == NULL)
		return;
	if (list == this->p_first)
	{
		this->p_first = list->p_next;
		if (list->p_next != NULL)
		{
			list->p_next->p_back = NULL;
		}
		delete list;
		return;
	}
	if (list->p_back == NULL)
	{
		if (list->p_next == NULL)
		{
			this->p_first = NULL;
			delete list;
			return;
		}

		this->p_first = list->p_next;
		if (list->p_next != NULL)
		{
			list->p_next->p_back = NULL;
		}

	}

	else
	{
		list->p_back->p_next = list->p_next;
		if (list->p_next != NULL)
		{
			list->p_next->p_back = list->p_back;
		}

	}

	delete list;
}

template<class T>
inline List<T>::List()
{
	p_first = NULL;
}

template<class T>
inline List<T>::~List()
{
	node* now = this->p_first;
	while (now != NULL)
	{
		node* tmp = now;
		now = now->p_next;
		delete tmp;
	}

}

//模板实例化
template class List<GameObject*>;
template class List<GameUI*>;
template class List<GameUIText*>;
template class MouseAction<GameObject*>;
template class MouseAction<GameUI*>;

Matrix::Matrix(int row, int column)
{
	this->init(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			matrix[i][j] = 0;
		}

	}

}

Matrix::Matrix(const Matrix& other)
{
	this->row = other.row;
	this->column = other.column;
	this->row = other.row;
	this->column = other.column;
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->column; j++)
		{
			this->matrix[i][j] = other.matrix[i][j];
		}

	}

}

Matrix::~Matrix()
{
	for (int i = 0; i < this->row; i++)delete[] this->matrix[i];
	delete[] this->matrix;
}

Matrix::Matrix(const Vector2& v2)
{
	this->init(int(v2.x), int(v2.y));
}

Matrix::Matrix(float* other, int row, int column)
{
	this->init(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			this->matrix[i][j] = *(other + i * column + j);
		}

	}

}

void Matrix::setValue(int row, int column, float value)
{
	this->matrix[row][column] = value;
}

void Matrix::print(bool isFraction)
{
	if (isFraction == false)
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				std::cout << matrix[i][j] << " ";
			}

			std::cout << std::endl;
		}

	else
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				std::cout << Fraction(matrix[i][j]) << " ";
			}

			std::cout << std::endl;
		}

}

void Matrix::swapRows(int row1, int row2) {
	if (row1 < 0 || row1 >= row || row2 < 0 || row2 >= row) {
		throw std::out_of_range("Row index out of range");
	}

	float* temp = matrix[row1];
	matrix[row1] = matrix[row2];
	matrix[row2] = temp;
}

void Matrix::divideRow(int row, float divisor) {
	if (row < 0 || row >= this->row) {
		throw std::out_of_range("Row index out of range");
	}

	else if (divisor == 0)
	{
		throw std::invalid_argument("Can't be divided by 0");
	}

	for (int j = 0; j < column; ++j) {
		matrix[row][j] /= divisor;
	}

}

void Matrix::addToRow(int sourceRow, int destRow, float multiple) {
	if (sourceRow < 0 || sourceRow >= row || destRow < 0 || destRow >= row) {
		throw std::out_of_range("Row index out of range");
	}

	for (int j = 0; j < column; ++j) {
		matrix[destRow][j] += matrix[sourceRow][j] * multiple;
	}

}

Matrix Matrix::getTransposeMatrix()
{
	Matrix transpose(column, row); // 新建一个矩阵，行列互换
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			transpose.matrix[j][i] = matrix[i][j]; // 转置
		}

	}

	return transpose;
}

float calDeterminant(float** det, int n)//det-行列式，n:行列式的阶数
{
	float detVal = 0;//行列式的值
	if (n == 1)//递归终止条件 
		return det[0][0];
	float** tempdet = new float* [n - 1];//用来存储余相应的余子式
	for (int i = 0; i < n - 1; i++)
		tempdet[i] = new float[n - 1];
	for (int i = 0; i < n; i++)//第一重循环，行列式按第一行展开 
	{
		for (int j = 0; j < n - 1; j++)
			for (int k = 0; k < n - 1; k++)
			{
				if (k < i)
					tempdet[j][k] = det[j + 1][k];
				else
					tempdet[j][k] = det[j + 1][k + 1];
			}

		detVal += det[0][i] * pow(-1.0, i) * calDeterminant(tempdet, n - 1);
	}

	for (int i = 0; i < n - 1; i++)delete[] tempdet[i]; delete[] tempdet;
	return detVal;
}

//使用高斯消元法对矩阵进行求逆
Matrix Matrix::getInverseMatrix() {
	if (row != column) {
		throw std::invalid_argument("Matrix is not square.");
	}

	// 创建扩增矩阵
	double** augmentedMatrix = new double* [row];
	for (int i = 0; i < row; ++i) {
		augmentedMatrix[i] = new double[2 * row];
		for (int j = 0; j < row; ++j) {
			augmentedMatrix[i][j] = matrix[i][j];
			augmentedMatrix[i][j + row] = (i == j) ? 1 : 0; // 对角线置为1，其余置为0
		}

	}

	// 高斯消元
	for (int i = 0; i < row; ++i) {
		// 判断主元素是否为0，如果是则交换行
		if (augmentedMatrix[i][i] == 0) {
			int swapRow = i + 1;
			while (swapRow < row && augmentedMatrix[swapRow][i] == 0) {
				++swapRow;
			}

			if (swapRow == row) {
				throw std::invalid_argument("Matrix is singular.");
			}

			std::swap(augmentedMatrix[i], augmentedMatrix[swapRow]);
		}

		// 将主元素归一
		double pivot = augmentedMatrix[i][i];
		for (int j = 0; j < 2 * row; ++j) {
			augmentedMatrix[i][j] /= pivot;
		}

		// 使用主元素消去其他行
		for (int j = 0; j < row; ++j) {
			if (j != i) {
				double factor = augmentedMatrix[j][i];
				for (int k = 0; k < 2 * row; ++k) {
					augmentedMatrix[j][k] -= factor * augmentedMatrix[i][k];
				}

			}

		}

	}

	// 提取逆矩阵
	Matrix inverse(row, column);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < row; ++j) {
			inverse.matrix[i][j] = augmentedMatrix[i][j + row];
		}

	}

	// 释放内存
	for (int i = 0; i < row; ++i) {
		delete[] augmentedMatrix[i];
	}

	delete[] augmentedMatrix;
	return inverse;
}

float Matrix::getDeterminant()
{
	if (row != column) {
		throw std::invalid_argument("Cannot calculate determinant for non-square matrix");
	}

	if (row == 1) {
		return matrix[0][0];
	}

	else
	{
		return calDeterminant(this->matrix, row);
	}

}

// 矩阵加法
Matrix Matrix::operator+(const Matrix& other) {
	if (row != other.row || column != other.column) {
		throw std::invalid_argument("Matrix dimensions do not match for addition");
	}

	Matrix result(row, column);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
		}

	}

	return result;
}

// 矩阵减法
Matrix Matrix::operator-(const Matrix& other)
{
	if (row != other.row || column != other.column)
	{
		throw std::invalid_argument("Matrix dimensions do not match for subtraction");
	}

	Matrix result(row, column);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
		}

	}

	return result;
}

// 矩阵乘法
Matrix Matrix::operator*(const Matrix& other)
{
	if (column != other.row)
	{
		throw std::invalid_argument("Matrix dimensions do not match for multiplication");
	}

	Matrix result(this->row, other.column);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < other.column; ++j)
		{
			result.matrix[i][j] = 0;
			for (int k = 0; k < this->column; ++k)
			{
				result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
			}

		}

	}

	return result;
}

// 矩阵与标量乘法
Matrix Matrix::operator*(float num)
{
	Matrix result(row, column);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			result.matrix[i][j] = matrix[i][j] * num;
		}

	}

	return result;
}

void Matrix::operator=(const Matrix& other)
{
	this->row = other.row;
	this->column = other.column;
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->column; j++)
		{
			this->matrix[i][j] = other.matrix[i][j];
		}

	}

}

bool Matrix::operator==(const Matrix& other)
{
	if (this->row != other.row || this->column != other.column)return false;
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->column; j++)
		{
			if (this->matrix[i][j] != other.matrix[i][j])
				return false;
		}

	}

	return true;
}

Transform::Transform()
{
	position = Vector2(0, 0);
}

Transform::Transform(const Transform& other)
{
	this->position = other.position;
}

Transform::Transform(Vector2 position)
{
	this->position = position;
}

Vector2 Transform::getPosition()
{
	return this->position;
}

float Transform::getDistance(const Transform& other)
{
	return this->position.destance(other.position);
}

Circle::Circle(float radius, Vector2 position) :Transform()
{
	this->radius = radius;
	this->position = position;
}

Circle::Circle(const Circle& other)
{
	this->position = other.position;
	this->radius = other.radius;
}

float Circle::getAreaSize()
{
	return PI * this->radius * this->radius;
}

void Circle::move(Vector2 dest)
{
	this->position = dest;
}

Vector2 Circle::getLeftTopPosition()
{
	return Vector2(this->position.x - this->radius, this->position.y - this->radius);
}


bool Circle::isTriggerEnter(const Triangle& other)
{
	//圆形与三角形的碰撞检测
	float a = this->position.destance(other.pointA) - radius;
	float b = this->position.destance(other.pointB) - radius;
	float c = this->position.destance(other.pointC) - radius;
	float p = (a + b + c) / 2;
	float s = sqrt(p * (p - a) * (p - b) * (p - c));
	if (s == 0)
		return true;
	else
		return false;
}

bool Circle::isTriggerEnter(const Rectangle& other)
{
	//圆形与矩形的碰撞检测
	float x = this->position.x;
	float y = this->position.y;
	float x1 = other.position.x - other.width / 2;
	float x2 = other.position.x + other.width / 2;
	float y1 = other.position.y - other.height / 2;
	float y2 = other.position.y + other.height / 2;
	if (x + radius >= x1 && x - radius <= x2 && y + radius >= y1 && y - radius <= y2)
		return true;
	else
		return false;
}

bool Circle::isTriggerEnter(const Diamond& other)
{
	//圆形与菱形粗略的碰撞检测
	float x = this->position.x;
	float y = this->position.y;
	float x1 = other.position.x - other.lengthX / 2;
	float x2 = other.position.x + other.lengthX / 2;
	float y1 = other.position.y - other.lengthY / 2;
	float y2 = other.position.y + other.lengthY / 2;
	if (x + radius >= x1 && x - radius <= x2 && y + radius >= y1 && y - radius <= y2)
		return true;
	else
		return false;
}

bool Circle::isTriggerEnter(const Circle& other)
{
	//圆形与圆形的碰撞检测
	if (this->position.destance(other.position) <= this->radius + other.radius)
		return true;
	else
		return false;
}

float Rectangle::getAreaSize()
{
	return this->height * this->width;
}

void Rectangle::move(Vector2 dest)
{
	this->position = dest;
}

Vector2 Rectangle::getLeftTopPosition()
{
	return Vector2(this->position.x - this->width / 2, this->position.y - this->height / 2);
}

bool Rectangle::isTriggerEnter(const Triangle& other)
{
	//矩形与三角形的碰撞检测
	float x1 = this->position.x - this->width / 2;
	float x2 = this->position.x + this->width / 2;
	float y1 = this->position.y - this->height / 2;
	float y2 = this->position.y + this->height / 2;
	if (other.pointA.x >= x1 && other.pointA.x <= x2 && other.pointA.y >= y1 && other.pointA.y <= y2)
		return true;
	else
		if (other.pointB.x >= x1 && other.pointB.x <= x2 && other.pointB.y >= y1 && other.pointB.y <= y2)
			return true;
		else
			if (other.pointC.x >= x1 && other.pointC.x <= x2 && other.pointC.y >= y1 && other.pointC.y <= y2)
				return true;
			else
				return false;
}

bool Rectangle::isTriggerEnter(const Rectangle& other)
{
	//矩形与矩形的碰撞检测
	float x1 = this->position.x - this->width / 2;
	float x2 = this->position.x + this->width / 2;
	float y1 = this->position.y - this->height / 2;
	float y2 = this->position.y + this->height / 2;
	float x3 = other.position.x - other.width / 2;
	float x4 = other.position.x + other.width / 2;
	float y3 = other.position.y - other.height / 2;
	float y4 = other.position.y + other.height / 2;
	if (x1 <= x4 && x2 >= x3 && y1 <= y4 && y2 >= y3)
		return true;
	else
		return false;
}

bool Rectangle::isTriggerEnter(const Diamond& other)
{
	//矩形与菱形的碰撞检测
	float x1 = this->position.x - this->width / 2;
	float x2 = this->position.x + this->width / 2;
	float y1 = this->position.y - this->height / 2;
	float y2 = this->position.y + this->height / 2;
	float x3 = other.position.x - other.lengthX / 2;
	float x4 = other.position.x + other.lengthX / 2;
	float y3 = other.position.y - other.lengthY / 2;
	float y4 = other.position.y + other.lengthY / 2;
	if (x1 <= x4 && x2 >= x3 && y1 <= y4 && y2 >= y3)
		return true;
	else
		return false;
}

bool Rectangle::isTriggerEnter(const Circle& other)
{
	//矩形与圆形的碰撞检测
	float x1 = this->position.x - this->width / 2;
	float x2 = this->position.x + this->width / 2;
	float y1 = this->position.y - this->height / 2;
	float y2 = this->position.y + this->height / 2;
	if (other.position.x >= x1 && other.position.x <= x2 && other.position.y >= y1 && other.position.y <= y2)
		return true;
	else
		return false;
}

Rectangle::Rectangle(float width, float height, Vector2 position) :Transform()
{
	this->width = width;
	this->height = height;
	this->position = position;
}

Rectangle::Rectangle(const Rectangle& other)
{
	this->position = other.position;
	this->width = other.width;
	this->height = other.height;
}

float Triangle::getAreaSize()
{
	float a = this->pointA.destance(this->pointB);
	float b = this->pointB.destance(this->pointC);
	float c = this->pointC.destance(this->pointA);
	float p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

bool Triangle::isTriggerEnter(const Triangle& other)
{
	//三角形与三角形的碰撞检测
	float x1 = this->pointA.x;
	float y1 = this->pointA.y;
	float x2 = this->pointB.x;
	float y2 = this->pointB.y;
	float x3 = this->pointC.x;
	float y3 = this->pointC.y;
	float x4 = other.pointA.x;
	float y4 = other.pointA.y;
	float x5 = other.pointB.x;
	float y5 = other.pointB.y;
	float x6 = other.pointC.x;
	float y6 = other.pointC.y;
	float a = (x1 - x2) * (y4 - y1) - (x4 - x1) * (y1 - y2);
	float b = (x1 - x2) * (y5 - y1) - (x5 - x1) * (y1 - y2);
	float c = (x1 - x2) * (y6 - y1) - (x6 - x1) * (y1 - y2);
	if (a * b > 0 && a * c > 0)
		return true;
	else
	{
		a = (x2 - x3) * (y4 - y2) - (x4 - x2) * (y2 - y3);
		b = (x2 - x3) * (y5 - y2) - (x5 - x2) * (y2 - y3);
		c = (x2 - x3) * (y6 - y2) - (x6 - x2) * (y2 - y3);
		if (a * b > 0 && a * c > 0)
			return true;
		else
		{
			a = (x3 - x1) * (y4 - y3) - (x4 - x3) * (y3 - y1);
			b = (x3 - x1) * (y5 - y3) - (x5 - x3) * (y3 - y1);
			c = (x3 - x1) * (y6 - y3) - (x6 - x3) * (y3 - y1);
			if (a * b > 0 && a * c > 0)
				return true;
			else
				return false;
		}

	}

}

bool Triangle::isTriggerEnter(const Rectangle& other)
{
	//三角形与矩形的碰撞检测
	float x1 = this->pointA.x;
	float y1 = this->pointA.y;
	float x2 = this->pointB.x;
	float y2 = this->pointB.y;
	float x3 = this->pointC.x;
	float y3 = this->pointC.y;
	float x4 = other.position.x - other.width / 2;
	float x5 = other.position.x + other.width / 2;
	float y4 = other.position.y - other.height / 2;
	float y5 = other.position.y + other.height / 2;
	if (x1 >= x4 && x1 <= x5 && y1 >= y4 && y1 <= y5)
		return true;
	else
		if (x2 >= x4 && x2 <= x5 && y2 >= y4 && y2 <= y5)
			return true;
		else
			if (x3 >= x4 && x3 <= x5 && y3 >= y4 && y3 <= y5)
				return true;
			else
				return false;
}

bool Triangle::isTriggerEnter(const Diamond& other)
{
	//三角形与菱形的碰撞检测
	float x1 = this->pointA.x;
	float y1 = this->pointA.y;
	float x2 = this->pointB.x;
	float y2 = this->pointB.y;
	float x3 = this->pointC.x;
	float y3 = this->pointC.y;
	float x4 = other.position.x - other.lengthX / 2;
	float x5 = other.position.x + other.lengthX / 2;
	float y4 = other.position.y - other.lengthY / 2;
	float y5 = other.position.y + other.lengthY / 2;
	if (x1 >= x4 && x1 <= x5 && y1 >= y4 && y1 <= y5)
		return true;
	else
		if (x2 >= x4 && x2 <= x5 && y2 >= y4 && y2 <= y5)
			return true;
		else
			if (x3 >= x4 && x3 <= x5 && y3 >= y4 && y3 <= y5)
				return true;
			else
				return false;
}

bool Triangle::isTriggerEnter(const Circle& other)
{
	//三角形与圆形的碰撞检测
	float x1 = this->pointA.x;
	float y1 = this->pointA.y;
	float x2 = this->pointB.x;
	float y2 = this->pointB.y;
	float x3 = this->pointC.x;
	float y3 = this->pointC.y;
	float x = other.position.x;
	float y = other.position.y;
	float a = (x - x1) * (y2 - y1) - (x2 - x1) * (y - y1);
	float b = (x - x2) * (y3 - y2) - (x3 - x2) * (y - y2);
	float c = (x - x3) * (y1 - y3) - (x1 - x3) * (y - y3);
	if (a * b > 0 && a * c > 0)
		return true;
	else
		return false;
}

Triangle::Triangle(Vector2 pointA, Vector2 pointB, Vector2 pointC)
{
	//计算三角形外接圆中心坐标
	Vector2 center;
	// 计算中点坐标
	Vector2 midpointAB = { (pointA.x + pointB.x) / 2, (pointA.y + pointB.y) / 2 }
	;
	Vector2 midpointBC = { (pointB.x + pointC.x) / 2, (pointB.y + pointC.y) / 2 }
	;
	// 计算边的斜率
	double slopeAB = (pointB.y - pointA.y) / (pointB.x - pointA.x);
	double slopeBC = (pointC.y - pointB.y) / (pointC.x - pointB.x);
	// 计算中垂线的斜率
	double perpendicularSlopeAB = -1 / slopeAB;
	double perpendicularSlopeBC = -1 / slopeBC;
	// 计算中垂线的截距
	double interceptAB = midpointAB.y - perpendicularSlopeAB * midpointAB.x;
	double interceptBC = midpointBC.y - perpendicularSlopeBC * midpointBC.x;
	// 计算圆心坐标
	center.x = (interceptBC - interceptAB) / (perpendicularSlopeAB - perpendicularSlopeBC);
	center.y = perpendicularSlopeAB * center.x + interceptAB;
	this->position = center;
	this->pointA = pointA;
	this->pointB = pointB;
	this->pointC = pointC;
}

Triangle::Triangle(Vector2 center, float coLength)
{
	this->position = center;
	this->pointA = Vector2(center.x, center.y + coLength);
	this->pointB = Vector2(center.x + coLength * sqrt(3) / 2, center.y - coLength / 2);
	this->pointC = Vector2(center.x - coLength * sqrt(3) / 2, center.y - coLength / 2);
}

Triangle::Triangle(const Triangle& other)
{
	this->position = other.position;
	this->pointA = other.pointA;
	this->pointB = other.pointB;
	this->pointC = other.pointC;
}

void Triangle::move(Vector2 dest)
{
	Vector2 offset = dest - this->position;
	this->pointA += offset;
	this->pointB += offset;
	this->pointC += offset;
	this->position = dest;
}

Vector2 Triangle::getPositionA()
{
	return this->pointA;
}

Vector2 Triangle::getPositionB()
{
	return this->pointB;
}

Vector2 Triangle::getPositionC()
{
	return this->pointC;
}

Vector2 Triangle::getLeftTopPosition()
{
	float minX = min(this->pointA.x, min(this->pointB.x, this->pointC.x));
	float minY = min(this->pointA.y, min(this->pointB.y, this->pointC.y));
	return Vector2(minX, minY);
}

float Diamond::getAreaSize()
{
	return this->lengthX * this->lengthY / 2;
}

void Diamond::move(Vector2 dest)
{
	this->position = dest;
}

Vector2 Diamond::getLeftTopPosition()
{
	return Vector2(this->position.x - this->lengthX / 2, this->position.y - this->lengthY / 2);
}

bool Diamond::isTriggerEnter(const Triangle& other)
{
	//菱形与三角形的碰撞检测
	float x1 = this->position.x - this->lengthX / 2;
	float x2 = this->position.x + this->lengthX / 2;
	float y1 = this->position.y - this->lengthY / 2;
	float y2 = this->position.y + this->lengthY / 2;
	if (other.pointA.x >= x1 && other.pointA.x <= x2 && other.pointA.y >= y1 && other.pointA.y <= y2)
		return true;
	else
		if (other.pointB.x >= x1 && other.pointB.x <= x2 && other.pointB.y >= y1 && other.pointB.y <= y2)
			return true;
		else
			if (other.pointC.x >= x1 && other.pointC.x <= x2 && other.pointC.y >= y1 && other.pointC.y <= y2)
				return true;
			else
				return false;
}

bool Diamond::isTriggerEnter(const Rectangle& other)
{
	//菱形与矩形的碰撞检测
	float x1 = this->position.x - this->lengthX / 2;
	float x2 = this->position.x + this->lengthX / 2;
	float y1 = this->position.y - this->lengthY / 2;
	float y2 = this->position.y + this->lengthY / 2;
	float x3 = other.position.x - other.width / 2;
	float x4 = other.position.x + other.width / 2;
	float y3 = other.position.y - other.height / 2;
	float y4 = other.position.y + other.height / 2;
	if (x1 <= x4 && x2 >= x3 && y1 <= y4 && y2 >= y3)
		return true;
	else
		return false;
}

bool Diamond::isTriggerEnter(const Diamond& other)
{
	//菱形与菱形的碰撞检测
	float x1 = this->position.x - this->lengthX / 2;
	float x2 = this->position.x + this->lengthX / 2;
	float y1 = this->position.y - this->lengthY / 2;
	float y2 = this->position.y + this->lengthY / 2;
	float x3 = other.position.x - other.lengthX / 2;
	float x4 = other.position.x + other.lengthX / 2;
	float y3 = other.position.y - other.lengthY / 2;
	float y4 = other.position.y + other.lengthY / 2;
	if (x1 <= x4 && x2 >= x3 && y1 <= y4 && y2 >= y3)
		return true;
	else
		return false;
}

bool Diamond::isTriggerEnter(const Circle& other)
{
	//菱形与圆形的碰撞检测
	float x1 = this->position.x - this->lengthX / 2;
	float x2 = this->position.x + this->lengthX / 2;
	float y1 = this->position.y - this->lengthY / 2;
	float y2 = this->position.y + this->lengthY / 2;
	float x = other.position.x;
	float y = other.position.y;
	if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
		return true;
	else
		return false;
}

Diamond::Diamond(float lengthX, float lengthY, Vector2 position) : Transform()
{
	this->lengthX = lengthX;
	this->lengthY = lengthY;
	this->position = position;
}

Diamond::Diamond(const Diamond& other)
{
	this->position = other.position;
	this->lengthX = other.lengthX;
	this->lengthY = other.lengthY;
}

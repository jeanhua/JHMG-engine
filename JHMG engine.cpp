#include "JHMG engine.h"

gameObject::gameObject(jhObject2D::circle* transform, LPCTSTR file, int width, int height, bool visible)
{
	this->transform.circle = transform;
	this->transformType = 'c';
	IMAGE* img = new IMAGE;
	loadimage(img, file, width, height, true);
	this->image = img;
	this->mouseAction = new MouseAction;
	this->mouseAction->beginPosition = transform->getLeftTopPosition();
	this->mouseAction->endPosition = transform->getLeftTopPosition() + jhVector2(width, height);
	this->visible = visible;
}

gameObject::gameObject(jhObject2D::rectangle* transform, LPCTSTR file, int width, int height, bool visible)
{
	this->transform.rectangle = transform;
	this->transformType = 'r';
	IMAGE* img = new IMAGE;
	loadimage(img, file, width, height, true);
	this->image = img;
	this->mouseAction = new MouseAction;
	this->mouseAction->beginPosition = transform->getLeftTopPosition();
	this->mouseAction->endPosition = transform->getLeftTopPosition() + jhVector2(width, height);
	this->visible = visible;
}

gameObject::gameObject(jhObject2D::diamond* transform, LPCTSTR file, int width, int height, bool visible)
{
	this->transform.diamond = transform;
	this->transformType = 'd';
	IMAGE* img = new IMAGE;
	loadimage(img, file, width, height, true);
	this->image = img;
	this->mouseAction = new MouseAction;
	this->mouseAction->beginPosition = transform->getLeftTopPosition();
	this->mouseAction->endPosition = transform->getLeftTopPosition() + jhVector2(width, height);
	this->visible = visible;
}

gameObject::gameObject(jhObject2D::triangle* transform, LPCTSTR file, int width, int height, bool visible)
{
	this->transform.triangle = transform;
	this->transformType = 't';
	IMAGE* img = new IMAGE;
	loadimage(img, file, width, height, true);
	this->image = img;
	this->mouseAction = new MouseAction;
	this->mouseAction->beginPosition = transform->getLeftTopPosition();
	this->mouseAction->endPosition = transform->getLeftTopPosition() + jhVector2(width, height);
	this->visible = visible;
}

void gameObject::setOnCollision(void(*onCollision)(gameObject* gameObject))
{
	this->onCollision = onCollision;
}

void gameObject::setGameLoopFunc(void(*gameLoopFunc)())
{
	this->gameLoopFunc = gameLoopFunc;
}

void gameObject::changeImage(LPCTSTR file,jhVector2 size)
{
	IMAGE* img = new IMAGE;
	loadimage(img, file, size.x, size.y, true);
	delete this->image;
	this->image = img;
}


gameUI::gameUI(jhVector2 position, jhVector2 size, jhString image, bool visible)
{
	this->position = position;
	this->size = size;
	IMAGE* img = new IMAGE;
	loadimage(img, image.to_char(), size.x, size.y, true);
	this->image = img;
	this->mouseAction = new MouseAction;
	this->mouseAction->beginPosition = position;
	this->mouseAction->endPosition = position + size;
	this->visible = visible;
}

void gameUI::changeImage(LPCTSTR file, jhVector2 size)
{
	IMAGE* img = new IMAGE;
	loadimage(img, file, size.x, size.y, true);
	delete this->image;
	this->image = img;
}


void gameSound::setSound(jhString music_file)
{
	this->music_file = music_file;
}

void gameSound::play()
{
	char command[256];
	sprintf(command, "open %s alias music", music_file.to_char());
	mciSendString(command, NULL, 0, NULL);
	mciSendString("play music", NULL, 0, NULL);
}

void gameSound::stop()
{
	mciSendString("close music", NULL, 0, NULL);
}

void gameSound::pause()
{
	mciSendString("pause music", NULL, 0, NULL);
}

void gameSound::resume()
{
	mciSendString("resume music", NULL, 0, NULL);
}

void gameSound::setVolume(int volume)
{
	char command[256];
	sprintf(command, "setaudio music volume to %d", volume);
	mciSendString(command, NULL, 0, NULL);
}

int gameSound::getVolume()
{
	char command[256];
	sprintf(command, "status music volume");
	char result[256];
	mciSendString(command, result, 256, NULL);
	int volume;
	sscanf(result, "%d", &volume);
	return volume;
}

void gameSound::setPosition(int position)
{
	char command[256];
	sprintf(command, "seek music to %d", position);
	mciSendString(command, NULL, 0, NULL);
}

int gameSound::getPosition()
{
	char command[256];
	sprintf(command, "status music position");
	char result[256];
	mciSendString(command, result, 256, NULL);
	int position;
	sscanf(result, "%d", &position);
	return position;
}

int gameSound::getLength()
{
	char command[256];
	sprintf(command, "status music length");
	char result[256];
	mciSendString(command, result, 256, NULL);
	int length;
	sscanf(result, "%d", &length);
	return length;
}

int gameSound::getState()
{
	char command[256];
	sprintf(command, "status music mode");
	char result[256];
	mciSendString(command, result, 256, NULL);
	if (strcmp(result, "playing") == 0)
	{
		return 1;
	}
	else if (strcmp(result, "paused") == 0)
	{
		return 2;
	}
	else if (strcmp(result, "stopped") == 0)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

void gameSound::close()
{
	mciSendString("close music", NULL, 0, NULL);
}

gameSound::~gameSound()
{
	mciSendString("close music", NULL, 0, NULL);
}

void Game::setWindowSize(jhVector2 windowSize)
{
	this->windowSize = windowSize;
}

void Game::setWindowTitle(jhString windowTitle)
{
	this->windowTitle = windowTitle;
}


void Game::initWindow()
{
	this->window = initgraph(windowSize.x, windowSize.y);
	SetWindowText(window, windowTitle.to_char());
	this->gameLoop();
}

void Game::setScene(gameScene* Scene)
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

void Game::gameLoop()
{
	clock_t endtime = 0, starttime = 0;
	//游戏循环
	BeginBatchDraw();
	while (1)
	{
		endtime = clock();
		//判断场景是否为空
		if (this->Scene == NULL)
		{
			throw invalid_argument("The scene is empty");
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
			//遍历物体
			for (auto it =this->Scene->gameObjects.p_first; it != NULL; it = it->p_next)
			{
				//打印物体
				if (it->value->visible)
				{
					if (it->value->transformType == 'c')
					{
						putimagePNG(it->value->transform.circle->getLeftTopPosition().x, it->value->transform.circle->getLeftTopPosition().y, it->value->image);
						it->value->mouseAction->beginPosition = it->value->transform.circle->getLeftTopPosition();
						it->value->mouseAction->endPosition = it->value->transform.circle->getLeftTopPosition() + jhVector2(it->value->image->getwidth(), it->value->image->getheight());
					}
					else if (it->value->transformType == 'r')
					{
						putimagePNG(it->value->transform.rectangle->getLeftTopPosition().x, it->value->transform.rectangle->getLeftTopPosition().y, it->value->image);
						it->value->mouseAction->beginPosition = it->value->transform.rectangle->getLeftTopPosition();
						it->value->mouseAction->endPosition = it->value->transform.rectangle->getLeftTopPosition() + jhVector2(it->value->image->getwidth(), it->value->image->getheight());
					}
					else if (it->value->transformType == 'd')
					{
						putimagePNG(it->value->transform.diamond->getLeftTopPosition().x, it->value->transform.diamond->getLeftTopPosition().y, it->value->image);
						it->value->mouseAction->beginPosition = it->value->transform.diamond->getLeftTopPosition();
						it->value->mouseAction->endPosition = it->value->transform.diamond->getLeftTopPosition() + jhVector2(it->value->image->getwidth(), it->value->image->getheight());
					}
					else if (it->value->transformType == 't')
					{
						putimagePNG(it->value->transform.triangle->getLeftTopPosition().x, it->value->transform.triangle->getLeftTopPosition().y, it->value->image);
						it->value->mouseAction->beginPosition = it->value->transform.triangle->getLeftTopPosition();
						it->value->mouseAction->endPosition = it->value->transform.triangle->getLeftTopPosition() + jhVector2(it->value->image->getwidth(), it->value->image->getheight());
					}
				}
				//调用物体循环函数
				if (it->value->gameLoopFunc != NULL)
					it->value->gameLoopFunc();
				//获取消息
				while (isMessage)
				{
					//调用鼠标事件
					it->value->mouseAction->getMouseMessage(msg);
					//获取键盘输入
					Input.getMessage(msg);
					break;
				}
				//遍历其他物体计算碰撞
				if (it->value->onCollision != NULL)
					for (auto it2 =this->Scene->gameObjects.p_first; it2 != NULL; it2 = it2->p_next)
					{
						if (it != it2)
						{
							if (it2->value->transformType == 'c')
							{
								if (it->value->transform.circle->isTriggerEnter(*it2->value->transform.circle))
									it->value->onCollision(it2->value);
							}
							else if (it2->value->transformType == 'r')
							{
								if (it->value->transform.circle->isTriggerEnter(*it2->value->transform.rectangle))
									it->value->onCollision(it2->value);
							}
							else if (it2->value->transformType == 'd')
							{
								if (it->value->transform.circle->isTriggerEnter(*it2->value->transform.diamond))
									it->value->onCollision(it2->value);
							}
							else if (it2->value->transformType == 't')
							{
								if (it->value->transform.circle->isTriggerEnter(*it2->value->transform.triangle))
									it->value->onCollision(it2->value);
							}
						}
					}
			}
			//清除消息缓存
			flushmessage(-1);
			//遍历界面
			for (auto it =this->Scene->gameUIs.p_first; it != NULL; it = it->p_next)
			{
				if (it->value->visible)
					putimagePNG(it->value->position.x, it->value->position.y, it->value->image);
			}
			//遍历界面文本
			for (auto it = this->Scene->gameUITexts.p_first; it != NULL; it = it->p_next)
			{
				if (it->value->visible)
					outtextxy(it->value->position.x, it->value->position.y, it->value->text.to_char());
			}
			//清除缓存
			FlushBatchDraw();
			deltaTime = endtime - starttime;
			starttime = clock();
		}
	}
	EndBatchDraw();
}

jhVector2 Game::getWindowSize()
{
	return windowSize;
}

jhString Game::getWindowTitle()
{
	return windowTitle;
}

gameScene* Game::getScene()
{
	return Scene;
}

void gameScene::addGameObject(jhString name, gameObject* gameObject_pre)
{
	if (this->gameTotalMap[name] >= 100)
	{
		throw invalid_argument("The name already exists");
		return;
	}
	this->gameObjects.addList(gameObject_pre);
	this->gameObjectsMap[name] = gameObject_pre;
	this->gameTotalMap[name] += 100;
}

void gameScene::removeGameObject(jhString name)
{
	for (auto it = this->gameObjects.p_first; it != NULL; it = it->p_next)
	{
		if (it->value == gameObjectsMap[name])
		{
			delete it->value->image;
			it->value->image = NULL;
			delete it->value->mouseAction;
			it->value->mouseAction = NULL;
			delete it->value;
			it->value = NULL;
			gameScene::gameObjectsMap.erase(name);
			this->gameObjects.deleteList(it);
			this->gameTotalMap[name] -= 100;
			return;
		}
	}
}

gameObject* gameScene::getGameObject(jhString name)
{
	return this->gameObjectsMap[name];
}

jhString gameScene::getName(gameObject* gameObject)
{
	for (auto it : gameObjectsMap)
	{
		if (it.second == gameObject)
		{
			return it.first;
		}
	}
}

void gameScene::addGameUI(jhString name, gameUI* gameUI)
{
	if (this->gameTotalMap[name] % 100 >= 10)
	{
		throw invalid_argument("The name already exists");
		return;
	}
	this->gameUIs.addList(gameUI);
	this->gameUIMap[name] = gameUI;
	this->gameTotalMap[name] += 10;
}

void gameScene::addGameUIText(jhString name, gameUIText* text)
{
	if (this->gameTotalMap[name] % 10 >= 1)
	{
		throw invalid_argument("The name already exists");
		return;
	}
	this->gameUITexts.addList(text);
	this->gameUITextsMap[name] = text;
	this->gameTotalMap[name] += 1;
}

void gameScene::removeGameUI(jhString name)
{
	for (auto it = this->gameUIs.p_first; it != NULL; it = it->p_next)
	{
		if (it->value == gameUIMap[name])
		{
			delete it->value->image;
			it->value->image = NULL;
			delete it->value->mouseAction;
			it->value->mouseAction = NULL;
			delete it->value;
			it->value = NULL;
			this->gameUIs.deleteList(it);
			this->gameTotalMap[name] -= 10;
			return;
		}
	}
}

void gameScene::removeGameUIText(jhString name)
{
	for (auto it = this->gameUITexts.p_first; it != NULL; it = it->p_next)
	{
		if (it->value == gameUITextsMap[name])
		{
			delete it->value;
			this->gameUITexts.deleteList(it);
			this->gameTotalMap[name] -= 1;
			return;
		}
	}
}

gameUI* gameScene::getGameUI(jhString name)
{
	return this->gameUIMap[name];
}

gameUIText* gameScene::getGameUIText(jhString name)
{
	return this->gameUITextsMap[name];
}

void gameScene::setGameLoopFunc(void(*gameLoop)())
{
	this->gameLoop = gameLoop;
}

void gameInput::getMessage(const ExMessage& msg)
{

	if (msg.message == WM_KEYDOWN)
	{
		this->key = msg.vkcode;
	}

}

char gameInput::getKey()
{
	auto tmpKey = key;
	key = 0;
	return tmpKey;
}

gameUIText::gameUIText(jhString text, jhVector2 position, bool visible)
{
	this->text = text;
	this->position = position;
	this->visible = visible;
}

void MouseAction::getMouseMessage(const ExMessage& msg)
{
	if (msg.message == WM_LBUTTONDOWN)
	{
		if (msg.x >= beginPosition.x && msg.x <= endPosition.x && msg.y >= beginPosition.y && msg.y <= endPosition.y)
		{
			if (onClick != NULL)
				onClick(MouseMessage::leftDown, jhVector2(msg.x, msg.y));
		}
	}
	if (msg.message == WM_LBUTTONUP)
	{
		if (msg.x >= beginPosition.x && msg.x <= endPosition.x && msg.y >= beginPosition.y && msg.y <= endPosition.y)
		{
			if (onClick != NULL)
				onClick(MouseMessage::leftUp, jhVector2(msg.x, msg.y));
		}
	}
	if (msg.message == WM_RBUTTONDOWN)
	{
		if (msg.x >= beginPosition.x && msg.x <= endPosition.x && msg.y >= beginPosition.y && msg.y <= endPosition.y)
		{
			if (onClick != NULL)
				onClick(MouseMessage::rightDown, jhVector2(msg.x, msg.y));
		}
	}
	if (msg.message == WM_RBUTTONUP)
	{
		if (msg.x >= beginPosition.x && msg.x <= endPosition.x && msg.y >= beginPosition.y && msg.y <= endPosition.y)
		{
			if (onClick != NULL)
				onClick(MouseMessage::rightUp, jhVector2(msg.x, msg.y));
		}
	}
}

void MouseAction::setClickFunc(void(*onClick)(int mouseMessage, jhVector2 position))
{
	this->onClick = onClick;
}

gameInputBox::gameInputBox(jhString* inputText, jhString title, jhString prompt, jhString defaultText,int max, jhVector2 size)
{
	this->inputText = inputText;
	this->title = title;
	this->prompt = prompt;
	this->defaultText = defaultText;
	this->maxInput = max;
	this->size = size;
}

void gameInputBox::show()
{
	InputBox(inputText->to_char(), this->maxInput, this->prompt.to_char(), this->title.to_char(), this->defaultText.to_char(), this->size.x, this->size.y);
}

gameMessageBox::gameMessageBox(jhString title, jhString message)
{
	this->title = title;
	this->message = message;
}

void gameMessageBox::show()
{
	MessageBox(NULL, message.to_char(), title.to_char(), MB_OK);
}

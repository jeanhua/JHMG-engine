#include "JHMG engine.h"

gameObject::gameObject(jhObject2D::circle* transform, LPCTSTR file, int width, int height, bool visible)
{
	this->transform.circle = transform;
	this->transformType ='c';
	IMAGE* img = new IMAGE;
	loadimage(img, file,width,height,true);
	this->image = img;
	this->visible = visible;
}

gameObject::gameObject(jhObject2D::rectangle* transform, LPCTSTR file, int width, int height, bool visible)
{
	this->transform.rectangle = transform;
	this->transformType = 'r';
	IMAGE* img = new IMAGE;
	loadimage(img, file,width,height,true);
	this->image = img;
	this->visible = visible;
}

gameObject::gameObject(jhObject2D::diamond* transform, LPCTSTR file, int width, int height, bool visible)
{
	this->transform.diamond = transform;
	this->transformType = 'd';
	IMAGE* img = new IMAGE;
	loadimage(img, file,width,height,true);
	this->image = img;
	this->visible = visible;
}

gameObject::gameObject(jhObject2D::triangle* transform, LPCTSTR file, int width, int height, bool visible)
{
	this->transform.triangle = transform;
	this->transformType = 't';
	IMAGE* img = new IMAGE;
	loadimage(img, file,width,height,true);
	this->image = img;
	this->visible = visible;
}

void gameObject::setOnCollision(void(*onCollision)(gameObject* gameObject))
{
	this->onCollision = onCollision;
}


gameUI::gameUI(jhVector2 position, jhVector2 size, jhString image, bool visible)
{
	this->position = position;
	this->size = size;
	IMAGE* img = new IMAGE;
	loadimage(img, image.to_char(),size.x,size.y,true);
	this->image = img;
	this->visible = visible;
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

void Game::setGameLoopFunc(void(*func)())
{
	this->gameLoopFunc = func;
}

void Game::initWindow()
{
	this->window = initgraph(windowSize.x, windowSize.y);
	SetWindowText(window, windowTitle.to_char());
	this->gameLoop();
}

void Game::setTargetFrame(int targetFrame)
{
	this->targetFrame = targetFrame;
}

void Game::gameLoop()
{
	clock_t endtime = 0, starttime = 0;
	//游戏循环
	BeginBatchDraw();
	while (1)
	{
		endtime = clock();
		//按帧循环
		while (endtime - starttime >= 1000 / targetFrame)
		{
			cleardevice();
			//遍历物体
			for (auto it = gameObjects.p_first; it != NULL; it = it->p_next)
			{
				if(it->value->visible)
					if(it->value->transformType=='c')
						putimagePNG(it->value->transform.circle->getLeftTopPosition().x, it->value->transform.circle->getLeftTopPosition().y, it->value->image);
				else if(it->value->transformType=='r')
						putimagePNG(it->value->transform.rectangle->getLeftTopPosition().x, it->value->transform.rectangle->getLeftTopPosition().y, it->value->image);
				else if(it->value->transformType=='d')
						putimagePNG(it->value->transform.diamond->getLeftTopPosition().x, it->value->transform.diamond->getLeftTopPosition().y, it->value->image);
				else if(it->value->transformType=='t')
						putimagePNG(it->value->transform.triangle->getLeftTopPosition().x, it->value->transform.triangle->getLeftTopPosition().y, it->value->image);
				//遍历其他物体计算碰撞
				if(it->value->onCollision!=NULL)
				for(auto it2 = gameObjects.p_first; it2 != NULL; it2 = it2->p_next)
				{
					if (it != it2)
					{
						if (it2->value->transformType == 'c')
						{
							if (it->value->transform.circle->isTrigleEnter(*it2->value->transform.circle))
								it->value->onCollision(it2->value);
						}
						else if (it2->value->transformType == 'r')
						{
							if (it->value->transform.circle->isTrigleEnter(*it2->value->transform.rectangle))
								it->value->onCollision(it2->value);
						}
						else if (it2->value->transformType == 'd')
						{
							if (it->value->transform.circle->isTrigleEnter(*it2->value->transform.diamond))
								it->value->onCollision(it2->value);
						}
						else if (it2->value->transformType == 't')
						{
							if (it->value->transform.circle->isTrigleEnter(*it2->value->transform.triangle))
								it->value->onCollision(it2->value);
						}
					}
				}
			}
			//遍历界面
			for (auto it = gameUIs.p_first; it != NULL; it = it->p_next)
			{
				if (it->value->visible)
				putimagePNG(it->value->position.x, it->value->position.y, it->value->image);
			}
			//执行自定义函数
			if(gameLoopFunc!=NULL)
			gameLoopFunc();
			//获取键盘输入
			Input.getMessage();
			//清除缓存
			FlushBatchDraw();
			flushmessage();
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

void Game::addGameObject(jhString name, gameObject* gameObject_pre)
{
	this->gameObjects.addList(gameObject_pre);
	this->gameObjectsMap[name] = gameObject_pre;
}

void Game::removeGameObject(jhString name)
{
	for (auto it = this->gameObjects.p_first; it != NULL; it = it->p_next)
	{
		if (it->value == gameObjectsMap[name])
		{
			delete it->value->image;
			it->value->image = NULL;
			delete it->value;
			it->value= NULL;
			Game::gameObjectsMap.erase(name);
			this->gameObjects.deleteList(it);
			return;
		}
	}
}

gameObject* Game::getGameObject(jhString name)
{
	return gameObjectsMap[name];
}

jhString Game::getName(gameObject* gameObject)
{
	for(auto it:gameObjectsMap)
	{
		if(it.second==gameObject)
		{
			return it.first;
		}
	}
}

void Game::addGameUI(jhString name, gameUI* gameUI)
{
	this->gameUIs.addList(gameUI);
	this->gameUIMap[name] = gameUI;
}

void Game::removeGameUI(jhString name)
{
	for (auto it = this->gameUIs.p_first; it != NULL; it = it->p_next)
	{
		if (it->value == gameUIMap[name])
		{
			delete it->value->image;
			delete it->value;
			this->gameUIs.deleteList(it);
			return;
		}
	}
}

gameUI* Game::getGameUI(jhString name)
{
	return gameUIMap[name];
}

void gameInput::getMessage()
{
	while (peekmessage(&msg))
	{
		if (msg.message == WM_KEYDOWN)
		{
			this->key = msg.vkcode;
		}
	}
}

char gameInput::getKey()
{
	auto tmpKey = key;
	key = 0;
	return tmpKey;
}

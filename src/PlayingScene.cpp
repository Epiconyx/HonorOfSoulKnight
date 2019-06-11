#include "PlayingScene.h"


Scene* PlayingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("HelloWorld.png");//���뾫��
	sprite->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(sprite);

	//ע�����
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);//��ֹ���´���
	listener->onTouchBegan = [](Touch* t, Event* e) 
	{
		//��ȡ�¼��󶨵�target��Ŀ�꣩
		auto target = static_cast<Sprite*>(e->getCurrentTarget());
		//��ȡ��ǰ������������԰�ťλ�õ�����
		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		//������Χ�жϼ�⣬�ж������ݵ������Ƿ����������������
		if (rect.containsPoint(locationInNode))
		{
			//��ʾ��ǰ�����λ��
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(150);
			return true;
		}
		return false
;
	};

	listener->onTouchMoved = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//��ʾ��ǰ���������λ��
		log("x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
		target->setPosition(touch->getLocation().x, touch->getLocation().y);
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		log("sprite onTouchesEnded.. ");
		target->setOpacity(255);
	};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);

    return true;
}
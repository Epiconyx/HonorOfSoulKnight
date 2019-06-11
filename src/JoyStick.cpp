#include "JoyStick.h"

USING_NS_CC;

bool JoyStick::init()
{
	if (!Layer::init()) {
		return false;
	}

	/*1. ����ҡ�˵ı���*/
	rocker_bg = Sprite::create("joystickBg.png");
	rocker_bg->setPosition(Vec2(150, 150));
	addChild(rocker_bg);

	/*2. ����ҡ��*/
	rocker = Sprite::create("joystick.png");
	rocker->setPosition(Vec2(150, 150));
	addChild(rocker);

	return true;
}

/*��ǰ���󱻼��뵽����ڵ��ϻ���ø÷���*/
void JoyStick::onEnter()
{
	/*���ȵ��ø����onEnter����*/
	Layer::onEnter();

	/*�������㴥���ļ���, ������auto*/
	listener = EventListenerTouchOneByOne::create();

	/*����ʹ��lambda���ʽ��������������������̫��, �������ǻ���ʹ�ûص�����*/
	listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);

	/*ע�����*/
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

/*��ǰ����Ӹ������Ƴ�ʱ����ø÷���*/
void JoyStick::onExit()
{
	/*�ӷַ������Ƴ�ע��ļ���*/
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

	/*�����ø����onExit()����*/
	Layer::onExit();
}

bool JoyStick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*��������ʼ��ʱ�� ����������λ�ú��������ĵ�λ�õľ��� < Բ�İ뾶 ���ǲ���Move*/

	/*��ȡԲ�ĵ�Ͱ뾶*/
	float radius = rocker_bg->getContentSize().width / 2;
	Vec2 center = rocker_bg->getPosition();

	if (touch->getLocation().distance(center) > radius) {
		return false;
	}
	else {
		rocker->setPosition(Vec2(touch->getLocation()));
		return true;
	}

}

void JoyStick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*�������ƶ���ʱ�� ����������λ�ú��������ĵ�λ�õľ��� < Բ�İ뾶 */

	/*��ȡԲ�ĵ�Ͱ뾶*/
	float radius = rocker_bg->getContentSize().width / 2;
	Vec2 center = rocker_bg->getPosition();
	/*��ȡ������λ��*/
	Vec2 touch_pos = touch->getLocation();
	float dis = touch_pos.distance(center);
	angle = acos((touch_pos.x - center.x) / dis);
	if (touch_pos.y > center.y) {
		checkDirection(angle);
	}
	else {
		checkDirection(-angle);
	}

	if (dis <= radius) {
		rocker->setPosition(Vec2(touch_pos));
	}
	else {
		/*������ϰ�Բ*/
		if (touch_pos.y > center.y) {
			rocker->setPosition(Vec2(center.x + radius * cos(angle), center.y + radius * sin(angle)));
		}
		else {
			rocker->setPosition(Vec2(center.x + radius * cos(angle), center.y - radius * sin(angle)));
		}
	}


}

void JoyStick::checkDirection(float angle)
{
	/*�ҷ���*/
	if (angle >= -M_PI / 8.0 && angle <= M_PI / 8.0) {
		dir = RIGHT;
	}
	/*�ұ��� -�˷�֮�� �� �˷�֮��*/
	if (angle >= -(M_PI / 8.0) && angle <= M_PI / 8.0) {
		dir = RIGHT;
	}
	/*���Ϸ��� �˷�֮�� �� �˷�֮����*/
	else if (angle >= M_PI / 8.0 && angle < 3 * M_PI / 8.0) {
		dir = R_UP;
	}
	/*�Ϸ��� �˷�֮���� �� �˷�֮����*/
	else if (angle >= 3 * M_PI / 8.0 && angle <= 5 * M_PI / 8.0) {
		dir = UP;
	}
	/*���Ϸ��� �˷�֮5�� �� �˷�֮����*/
	else if (angle > 5 * M_PI / 8.0 && angle < 7 * M_PI / 8.0) {
		dir = L_UP;
	}
	/*����*/
	else if ((angle >= 7 * M_PI / 8.0 && angle <= M_PI) || (angle <= -7 * M_PI / 8.0 && angle >= -M_PI)) {
		dir = LEFT;
	}
	/*���·���*/
	else if (angle > -7 * M_PI / 8.0 && angle < -5 * M_PI / 8.0) {
		dir = L_DOWN;
	}
	/*�·���*/
	else if (angle >= -5 * M_PI / 8.0 && angle <= -3 * M_PI / 8.0) {
		dir = DOWN;
	}
	/*���·���*/
	else if (angle > -3 * M_PI / 8.0 && angle < -M_PI / 8.0) {
		dir = R_DOWN;
	}

}

void JoyStick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*�ڽ�������ʱ����ҡ�˹�Ϊԭ��λ��*/
	rocker->setPosition(rocker_bg->getPosition());
	dir = STAY;
}

Sprite* JoyStick::getRocker()
{
	return rocker;
}
Sprite* JoyStick::getRockerBg()
{
	return rocker_bg;
}

float JoyStick::getAngle()
{
	return angle;
}

RDIRECTION JoyStick::getDir()
{
	return dir;
}
/*
#include "HRocker.h"

using namespace cocos2d;

//����һ����ʱ������ʱ����������λ��
void HRocker::updatePos(float dt) {
	jsSprite->setPosition(ccpAdd(jsSprite->getPosition(), ccpMult(ccpSub(currentPoint, jsSprite->getPosition()), 0.5)));
}

bool HRocker::init()
{
	if (!Layer::init())
	{
		return false;
	}
	rocker_bg = Sprite
}
//����ҡ��
void HRocker::Active()
{
	if (!active) {
		active = true;
		schedule(schedule_selector(HRocker::updatePos));//���ˢ�º���
		//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
		touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);

		touchListener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
		// ע���¼���������
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	}
	else {
	}
}
//���ҡ��
void   HRocker::Inactive()
{
	if (active) {
		active = false;
		this->unschedule(schedule_selector(HRocker::updatePos));//ɾ��ˢ��
		_eventDispatcher->removeEventListener(touchListener);//ɾ��ί��
	}
	else {
	}
}
//ҡ�˷�λ
Vec2 HRocker::getDirection()
{

	return ccpNormalize(ccpSub(centerPoint, currentPoint));
}
//ҡ������
float HRocker::getVelocity()
{
	return ccpDistance(centerPoint, currentPoint);
}
HRocker* HRocker::HRockerWithCenter(Vec2 point, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole) {
	HRocker *jstick = HRocker::create();
	jstick->initWithCenter(point, aRadius, aJsSprite, aJsBg, _isFollowRole);
	return jstick;
}
bool HRocker::onTouchBegan(Touch* touch, Event* event)
{
	if (!active)
		return false;
	this->setVisible(true);
	Vec2 touchPoint = touch->getLocationInView();
	touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
	if (!isFollowRole) {
		if (ccpDistance(touchPoint, centerPoint) > radius) {
			return false;
		}
	}
	currentPoint = touchPoint;
	if (isFollowRole) {
		centerPoint = currentPoint;
		jsSprite->setPosition(currentPoint);
		this->getChildByTag(88)->setPosition(currentPoint);
	}
	return true;
}
void  HRocker::onTouchMoved(Touch* touch, Event* event)
{
	Vec2 touchPoint = touch->getLocationInView();
	touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
	if (ccpDistance(touchPoint, centerPoint) > radius)
	{
		currentPoint = ccpAdd(centerPoint, ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)), radius));
	}
	else {
		currentPoint = touchPoint;
	}
}
void HRocker::checkDirection(float angle)
{
	/*�ҷ���
	if (angle >= -M_PI / 4.0 && angle <= M_PI / 4.0) {
		dir = RIGHT;
	}
	/*�Ϸ��� 
	else if (angle >= M_PI / 4.0 && angle < 3 * M_PI / 4.0) {
		dir = UP;
	}
	/*����
	else if ((angle >= 3 * M_PI / 4.0 && angle <= M_PI) || (angle <= -3 * M_PI / 4.0 && angle >= -M_PI)) {
		dir = LEFT;
	}
	/*�·���
	else if (angle >= -3 * M_PI / 4.0 && angle <= -M_PI / 4.0) {
		dir = DOWN;
	}

}
void  HRocker::onTouchEnded(Touch* touch, Event* event)
{
	currentPoint = centerPoint;
	if (isFollowRole) {
		this->setVisible(false);
	}
}
/*HRocker* HRocker::initWithCenter(Vec2 aPoint, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole) {
	isFollowRole = _isFollowRole;
	active = false;
	radius = aRadius;
	if (!_isFollowRole) {
		centerPoint = aPoint;
	}
	else {
		centerPoint = ccp(0, 0);
	}
	currentPoint = centerPoint;

	jsSprite = aJsSprite;
	jsSprite->setPosition(centerPoint);
	aJsBg->setPosition(centerPoint);
	aJsBg->setTag(88);
	this->addChild(aJsBg);
	this->addChild(jsSprite);
	if (isFollowRole) {
		this->setVisible(false);
	}
	this->Active();
	return this;
}
float HRocker::getAngle()
{
	return angle;
}
RDIRECTION HRocker::getDir()
{
	return dir;
}*/
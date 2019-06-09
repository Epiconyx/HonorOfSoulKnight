#include "Hero.h"  
USING_NS_CC;
USING_NS_CC_EXT;
Hero::Hero(void)
{
	IsRunning = false;//û�ڷŶ���  
	HeroDirection = false;//�����˶�  
	Hero_name = NULL;
}

Hero::~Hero(void)
{

}
void Hero::InitHeroSprite(char *hero_name)
{
	Hero_name = hero_name;
	this->m_HeroSprite = CCSprite::create(hero_name);
	this->addChild(m_HeroSprite);
}
//�������ţ��������ܡ����������������˵�  
void Hero::SetAnimation(const char *name_plist, const char *name_png,unsigned int num, bool run_directon)
{
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;
		m_HeroSprite->setFlipX(run_directon);
	}
	if (IsRunning)
		return;
	//��ͼƬ���ص�����֡�����  
	CCSpriteFrameCache *m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	m_frameCache->addSpriteFramesWithFile(name_plist, name_png);
	CCAnimation* animation = CCAnimation::create();
	char nameBuf[100];
	for (int i = 0; i < num; i++)
	{
		memset(nameBuf, 0, sizeof(nameBuf));
		sprintf(nameBuf, "%d.png", i);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(nameBuf));
    }
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;

	}
	animation->setLoops(-1);//��ʾ����ѭ������  
	animation->setDelayPerUnit(0.1f);//ÿ����ͼƬ��ʱ�����ͼƬ��ĿԽ�٣������С��ԽС  

	 //��������װ��һ������  
	CCAnimate* act = CCAnimate::create(animation);


	m_HeroSprite->runAction(act);
	IsRunning = true;

}
void Hero::StopAnimation()
{
	if (!IsRunning)
		return;
	m_HeroSprite->stopAllActions();//��ǰ����ֹͣ���ж���  

	//�ָ�����ԭ���ĳ�ʼ����ͼ   
	this->removeChild(m_HeroSprite, TRUE);//��ԭ���ľ���ɾ����  
	m_HeroSprite = CCSprite::create(Hero_name);//�ָ�����ԭ������ͼ����  
	m_HeroSprite->setFlipX(HeroDirection);
	this->addChild(m_HeroSprite);
	IsRunning = false;
	IsRunning = false;
}

#ifndef HERO_H
#define HERO_H
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Hero:public cocos2d::CCNode
{
public:
	Hero(void);
	~Hero(void);
	//����ͼƬ������Ӣ��
	void InitHeroSprite(char *hero_name);
	//���ö�����numΪͼƬ��Ŀ��run_directionΪ����������false����
	//name_eachΪname_png��ÿһС��ͼƬ���ƹ����Ĳ���
	void SetAnimation(const char *name_plist, const char *name_png,const unsigned int num, bool run_dirction);
	//ֹͣ����
	void StopAnimation();
	//�ж��Ƿ����ܶ���
	bool IsRunning;
	//Ӣ���˶��ķ���
	bool HeroDirection;
	CREATE_FUNC(Hero);

private:
	CCSprite* m_HeroSprite;//����
	char *Hero_name;//���������ʼ״̬�ľ���ͼƬ����
};
#endif //HERO_H

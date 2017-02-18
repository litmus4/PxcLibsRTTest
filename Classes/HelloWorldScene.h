#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class CSubRun;
namespace PxcUtil
{
	class CThread;
}
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	std::string InitRun1();
	std::string InitRun2();
	std::string InitThreadMain();
	std::string InitThreadSub();
	std::string InitRun3();
	std::string InitRun4();

	virtual void update(float dt);
	void TickSubThread();

private:
	cocos2d::Label* m_pMainLabel;
	float m_fMainTime;
	int m_iMainCount;
	cocos2d::Label* m_pSubLabel;
	PxcUtil::CThread* m_pSubThread;
	CSubRun* m_pSubRun;
};

#endif // __HELLOWORLD_SCENE_H__

#include "AppDelegate.h"
#include "AppMacros.h"

#include "PinballScene.h"
#include "HelloWorldScene.h"
#include "BlockGameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);
	std::vector<std::string> searchPath;

	bool is_ios = false;

	// デザインサイズの変更
	if( is_ios ){
		pEGLView->setDesignResolutionSize(designResolutionSize.width , designResolutionSize.height , kResolutionNoBorder);
		CCSize frameSize = pEGLView->getFrameSize();

		if( frameSize.height < mediumResource.size.height ){
			//[L]ディレクトリ
			searchPath.push_back(largeResource.directory);
			pDirector->setContentScaleFactor(MIN(largeResource.size.height / designResolutionSize.height,largeResource.size.width / designResolutionSize.width));
		}
		else if( frameSize.height < smallResource.size.height ){
			//[L]ディレクトリ
			searchPath.push_back(mediumResource.directory);
			pDirector->setContentScaleFactor(MIN(mediumResource.size.height / designResolutionSize.height,mediumResource.size.width / designResolutionSize.width));
		}
		else {
			//[L]ディレクトリ
			searchPath.push_back(mediumResource.directory);
			pDirector->setContentScaleFactor(MIN(smallResource.size.height / designResolutionSize.height,smallResource.size.width / designResolutionSize.width));
		}

		CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
	}
	else {
		// アンドロイドはmediumのサイズを利用
		searchPath.push_back(mediumResource.directory);
		CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

		pEGLView->setDesignResolutionSize(android_designResolutionSize.width , android_designResolutionSize.height , kResolutionNoBorder);

	}





	// turn on display FPS
	pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	//CCScene *pScene = BlockGameScene::scene();
	CCScene *pScene = PinballScene::scene();

	// run
	pDirector->runWithScene(pScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->startAnimation();
	// �ύX�`�F�b�N

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

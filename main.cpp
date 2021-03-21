#include "incl.h"

GameObject* (*old_PlayerObject_create)(GameObject*, int, int, CCLayer*);
GameObject* playerObject_create(GameObject* self, int i1, int i2, CCLayer* layer) {
	if(self != nullptr) {
		GameObject* ret = old_PlayerObject_create(self, i1, i2, layer);
		ret->runAction(CCRepeatForever::create(CCSequence::create(
			CCTintTo::create(0.5, 255,   0,	  0), 
			CCTintTo::create(0.5, 255, 255,   0), 
			CCTintTo::create(0.5, 0  , 255,   0),
			CCTintTo::create(0.5, 0  , 255, 255), 
			CCTintTo::create(0.5, 0  ,   0, 255), 
			CCTintTo::create(0.5, 255,   0, 255), 
			nullptr)));
		CCNode* a = (CCNode*)ret;
		CCNode* b = (CCNode*)a->getChildren()->objectAtIndex(0);
		CCNode* c = (CCNode*)b->getChildren()->objectAtIndex(0);
		c->runAction(CCRepeatForever::create(CCSequence::create(
			CCTintTo::create(0.5, 0  , 255, 255), 
			CCTintTo::create(0.5, 0  ,   0, 255), 
			CCTintTo::create(0.5, 255,   0, 255), 
			CCTintTo::create(0.5, 255,   0,	  0), 
			CCTintTo::create(0.5, 255, 255,   0), 
			CCTintTo::create(0.5, 0  , 255,   0),
			nullptr)));
		return ret;
	}
	return old_PlayerObject_create(self, i1, i2, layer);
}

__attribute__((constructor))
void libmod_main() {
	create_hook("_ZN12PlayerObject6createEiiPN7cocos2d7CCLayerE", playerObject_create, old_PlayerObject_create);
	inlineHookAll();
}

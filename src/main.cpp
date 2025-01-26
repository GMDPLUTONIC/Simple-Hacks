#include <Geode/Geode.hpp>
#include <Geode/binding/MenuLayer.hpp>
#include <Geode/loader/GameEvent.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

class $modify(SimpleHacksLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
		return false;
		}

		log::error("Lil Darkie once said: Drink Piss You Nasty Slut Yeah Yeah");

		auto simpleHacksBtn = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_gpgBtn_001.png"),
			this,
			menu_selector(SimpleHacksLayer::onSimpleHacksBtn)
		);

		auto menu = this->getChildByID("side-menu");
		menu->addChild(simpleHacksBtn);

		simpleHacksBtn->setID("simpleHacksBtn"_spr);

		menu->updateLayout();

		return true;
	}

	void onSimpleHacksBtn(CCObject*) {
        FLAlertLayer::create("Simple Hacks:", "This Mod Adds Some Simple Hacks To The Game Like: Noclip, Icon Hack, Verify Hack, And More!", "Close")->show();
	}
};

	#include <Geode/modify/PlayLayer.hpp>
    class $modify(NoclipLayer, PlayLayer) {
        void destroyPlayer(PlayerObject* player, GameObject* object) override {
            if (object == m_anticheatSpike) {
                return PlayLayer::destroyPlayer(player, object);
            }
        }
    };

	#include <Geode/modify/GameManager.hpp>
	#include <Geode/modify/GameStatsManager.hpp>
	class $modify(IconHackLayer, GameStatsManager) {
        bool isItemUnlocked(UnlockType type, int key) {
            if (GameStatsManager::isItemUnlocked(type, key));
            return true;
        }
    };

    #include <Geode/modify/EditLevelLayer.hpp>

    class $modify(VerifyHackLayer, EditLevelLayer) {
        bool init(GJGameLevel* gl) {
            gl->m_isVerified = true;
            return EditLevelLayer::init(gl);
        }
    };
    
	#include <Geode/modify/GameLevelManager.hpp>

	class $modify(AllMainLevelsLayer, GameLevelManager) {

        GJGameLevel* getMainLevel(int levelID, bool dontGetLevelString) {
            auto level = GameLevelManager::getMainLevel(levelID, dontGetLevelString);
            if (level->m_requiredCoins > 0) {
                level->m_requiredCoins = 0;
            }
            return level;
        }
    };
	
	#include <Geode/modify/GJBaseGameLayer.hpp>

	class $modify(NoLevelKickLayer, GJBaseGameLayer) {

        bool shouldExitHackedLevel() { return false; }
    };

    #include <Geode/modify/SliderTouchLogic.hpp>

    class $modify(NoSliderLimitLayer, SliderTouchLogic) {

        void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override {
            auto touchPos = this->convertTouchToNodeSpace(touch);
            auto position = touchPos - this->m_position;
            if (this->m_rotated) {
                auto clamped = position.y;
                this->m_thumb->setPosition({0.f, clamped});
            } else {
                auto clamped = position.x;
                this->m_thumb->setPosition({clamped, 0.f});
            }

            if (this->m_activateThumb)
                this->m_thumb->activate();

            if (auto* slider = this->m_slider)
                slider->updateBar();
        }
    };
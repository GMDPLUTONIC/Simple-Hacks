#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		auto simpleNoclipButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_gpgBtn_001.png"),
			this,
			menu_selector(MyMenuLayer::onSimpleNoclipButton)
		);

		auto menu = this->getChildByID("side-menu");
		menu->addChild(simpleNoclipButton);

		simpleNoclipButton->setID("simple-noclip-button"_spr);

		menu->updateLayout();

		return true;
	}

	void onSimpleNoclipButton(CCObject*) {
		FLAlertLayer::create("Simple Noclip", "This Mod Adds Noclip To Your Game.", "Close")->show();
	}

};

	#include <Geode/modify/PlayLayer.hpp>
            class $modify(NoclPlayLayerHook, PlayLayer) {
            void destroyPlayer(PlayerObject* player, GameObject* object) override {
            if (object == m_anticheatSpike)
                return PlayLayer::destroyPlayer(player, object);
                }
            };
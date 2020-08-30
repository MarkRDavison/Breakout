#include <Scenes/TitleScene.hpp>
#include <zeno/Graphics.hpp>
#include <Definitions.hpp>

namespace brk {

	TitleScene::TitleScene(
		ze::Logger& _logger,
		ze::SceneTransitionManager& _sceneTransitionManager) 
	:
		m_Logger(_logger),
		m_SceneTransitionManager(_sceneTransitionManager) {

	}
	void TitleScene::update(float _delta) {

	}
	bool TitleScene::handleEvent(const ze::Event& _event) {
		if (_event.type == ze::Event::EventType::KeyDown) {
			if (_event.key.key == ze::Keyboard::Key::Q &&
				_event.key.control) {
				m_Logger.log(ze::Severity::Info, "Exiting application from % scene", "Intro");
				m_SceneTransitionManager.exitApplication();
				return true;
			}
			if (_event.key.key == ze::Keyboard::Key::S) {
				m_Logger.log(ze::Severity::Info, "Transitioning from % to %", "Title", "Game");
				m_SceneTransitionManager.pushSceneTransition(Definitions::GameSceneId);
				return true;
			}
		}
		return false;
	}
	void TitleScene::render(const ze::RenderTarget& _target, ze::RenderInfo _info) const {
		ze::CircleShape c(64.0f);
		c.setInternalColour(ze::Colour::Yellow);
		c.setTranslation(ze::Vector2f(_target.getSize()) / 2.0f);
		c.render(_target, _info);
	}

}
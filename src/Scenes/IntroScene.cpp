#include <Scenes/IntroScene.hpp>
#include <zeno/Graphics.hpp>
#include <Definitions.hpp>

namespace brk {

	IntroScene::IntroScene(
		ze::Logger& _logger,
		ze::SceneTransitionManager& _sceneTransitionManager) 
	:
		m_Logger(_logger),
		m_SceneTransitionManager(_sceneTransitionManager) {

	}
	void IntroScene::update(float _delta) {
		m_Time += _delta;
		if (m_Time > 2.0f) {
			m_Logger.log(ze::Severity::Info, "Transitioning from % to %", "Intro", "Title");
			m_SceneTransitionManager.pushSceneTransition(Definitions::TitleSceneId);
		}
	}
	bool IntroScene::handleEvent(const ze::Event& _event) {
		if (_event.type == ze::Event::EventType::KeyDown) {
			if (_event.key.key == ze::Keyboard::Key::Q &&
				_event.key.control) {
				m_Logger.log(ze::Severity::Info, "Exiting application from % scene", "Intro");
				m_SceneTransitionManager.exitApplication();
				return true;
			}
		}
		return false;
	}
	void IntroScene::render(const ze::RenderTarget& _target, ze::RenderInfo _info) const {
		ze::CircleShape c(64.0f);
		c.setInternalColour(ze::Colour::Magenta);
		c.setTranslation(ze::Vector2f(_target.getSize()) / 2.0f);
		c.render(_target, _info);
	}

}
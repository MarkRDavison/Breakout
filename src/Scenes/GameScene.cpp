#include <Scenes/GameScene.hpp>
#include <zeno/Graphics.hpp>
#include <Definitions.hpp>

namespace brk {

	GameScene::GameScene(
		ze::Logger& _logger,
		ze::SceneTransitionManager& _sceneTransitionManager,
		ze::IInputManager& _inputManager,
		ze::IInputActionManager& _inputActionManager)
	:
		m_Logger(_logger),
		m_SceneTransitionManager(_sceneTransitionManager),
		m_InputManager(_inputManager),
		m_InputActionManager(_inputActionManager) {

	}
	void GameScene::update(float _delta) {
		m_Game->update(_delta);
		m_GameRenderer->update(_delta);
		m_InputActionManager.updateCachedInputs();
	}
	bool GameScene::handleEvent(const ze::Event& _event) {
		if (_event.type == ze::Event::EventType::KeyDown) {
			if (_event.key.key == ze::Keyboard::Key::Q &&
				_event.key.control) {
				m_Logger.log(ze::Severity::Info, "Exiting application from % scene", "Intro");
				m_SceneTransitionManager.exitApplication();
				return true;
			}
			if (_event.key.key == ze::Keyboard::Key::BackSpace) {
				m_Logger.log(ze::Severity::Info, "Transitioning from % to %", "Game", "Title");
				m_SceneTransitionManager.pushSceneTransition(Definitions::TitleSceneId);
				return true;
			}
		}
		return false;
	}
	void GameScene::render(const ze::RenderTarget& _target, ze::RenderInfo _info) const {
		const float scale = 16.0f;
		const ze::Vector2f size(_target.getSize());
		const auto aspect = (size.x / size.y);

		ze::RenderInfo info(_info);
		info.projection = ze::Mat4x4::Orthographic3D(
			-aspect * scale, +aspect * scale,
			+1.0f * scale, -1.0f * scale,
			+1.0f, -1.0f);

		m_GameRenderer->render(_target, info);
	}

	void GameScene::initialize() {
		m_Game = new Game(m_InputActionManager);
		m_GameRenderer = new GameRenderer(m_Game);

		const ze::Vector2u size{ 3,1 };
		const ze::Vector2u cellsSize{ 24, 8 };

		m_Game->gameBounds.x = (Definitions::CellSize + Definitions::CellGap) * static_cast<float>(cellsSize.x) + Definitions::CellGap;
		m_Game->gameBounds.y = m_Game->gameBounds.x;

		for (unsigned y = 0; y < cellsSize.y; y += size.y) {
			for (unsigned x = 0; x < cellsSize.x; x += size.x) {
				Brick* b = new Brick;
				b->hp = (rand() % 3) + 1;
				if (b->hp == 1) {
					b->colour = ze::Colour::Blue;
				}
				if (b->hp == 2) {
					b->colour = ze::Colour::Green;
				}
				if (b->hp == 3) {
					b->colour = ze::Colour::Red;
				}
				b->bounds = Game::getBrickBounds(size, ze::Vector2u(x, y));
				m_Game->bricks.push_back(std::shared_ptr<Brick>(b));
			}
		}

		Paddle* p = new Paddle();
		p->position.x = m_Game->gameBounds.x / 2.0f;
		p->position.y = -m_Game->gameBounds.y + Definitions::CellSize / 2.0f + Definitions::CellGap;
		p->ball = std::make_shared<Ball>();
		m_Game->paddles.push_back(std::shared_ptr<Paddle>(p));
	}
}
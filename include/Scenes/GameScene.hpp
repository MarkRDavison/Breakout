#ifndef INCLUDED_BREAKOUT_SCENES_GAME_SCENE_HPP_
#define INCLUDED_BREAKOUT_SCENES_GAME_SCENE_HPP_

#include <zeno/Core.hpp>
#include <zeno/Game.hpp>

#include <Game/Game.hpp>
#include <Game/GameRenderer.hpp>

namespace brk {

	class GameScene : public ze::Scene {
	public:
		GameScene(
			ze::Logger& _logger,
			ze::SceneTransitionManager& _sceneTransitionManager,
			ze::IInputManager& _inputManager,
			ze::IInputActionManager& _inputActionManager);
		~GameScene() override = default;

		void update(float _delta) override;
		bool handleEvent(const ze::Event& _event) override;
		void render(const ze::RenderTarget& _target, ze::RenderInfo _info) const override;

		void initialize();

	private:
		ze::Logger& m_Logger;
		ze::SceneTransitionManager& m_SceneTransitionManager;
		ze::IInputManager& m_InputManager;
		ze::IInputActionManager& m_InputActionManager;

		Game* m_Game{ nullptr };
		GameRenderer* m_GameRenderer{ nullptr };
	};

}

#endif // INCLUDED_BREAKOUT_SCENES_GAME_SCENE_HPP_
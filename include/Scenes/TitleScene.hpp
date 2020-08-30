#ifndef INCLUDED_BREAKOUT_SCENES_TITLE_SCENE_HPP_
#define INCLUDED_BREAKOUT_SCENES_TITLE_SCENE_HPP_

#include <zeno/Core.hpp>
#include <zeno/Game.hpp>

namespace brk {

	class TitleScene : public ze::Scene {
	public:
		TitleScene(
			ze::Logger& _logger,
			ze::SceneTransitionManager& _sceneTransitionManager);
		~TitleScene() override = default;

		void update(float _delta) override;
		bool handleEvent(const ze::Event& _event) override;
		void render(const ze::RenderTarget& _target, ze::RenderInfo _info) const override;

	private:
		ze::Logger& m_Logger;
		ze::SceneTransitionManager& m_SceneTransitionManager;
	};

}

#endif // INCLUDED_BREAKOUT_SCENES_TITLE_SCENE_HPP_
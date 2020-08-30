#ifndef INCLUDED_BREAKOUT_GAME_GAME_RENDERER_HPP_
#define INCLUDED_BREAKOUT_GAME_GAME_RENDERER_HPP_

#include <Game/Game.hpp>
#include <zeno/Graphics.hpp>

namespace brk {

	class GameRenderer : public ze::Renderable {
	public:
		GameRenderer(const Game* _game);

		void update(float _delta);
		void render(const ze::RenderTarget& _target, ze::RenderInfo _info) const override;

		const Game* game;
	};

}

#endif // INCLUDED_BREAKOUT_GAME_GAME_RENDERER_HPP_
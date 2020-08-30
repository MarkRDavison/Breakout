#ifndef INCLUDED_BREAKOUT_GAME_GAME_HPP_
#define INCLUDED_BREAKOUT_GAME_GAME_HPP_

#include <Definitions.hpp>

#include <Game/Entities/Ball.hpp>
#include <Game/Entities/Brick.hpp>
#include <Game/Entities/Paddle.hpp>

#include <zeno/Game/InputActionManager.hpp>

#include <memory>
#include <vector>

namespace brk {

	class Game {
	public:
		Game(ze::IInputActionManager& _inputActionManager);
		void update(float _delta);

		void updateBall(std::shared_ptr<Ball>& _ball, float _delta);

		static ze::FloatRect getBrickBounds(const ze::Vector2u& _brickSize, const ze::Vector2u& _startingCoordinates);

		ze::IInputActionManager& m_InputActionManager;

		std::vector<std::shared_ptr<Ball>> balls;
		std::vector<std::shared_ptr<Brick>> bricks;
		std::vector<std::shared_ptr<Paddle>> paddles;

		ze::Vector2f gameBounds;
	};

}

#endif // INCLUDED_BREAKOUT_GAME_GAME_HPP_
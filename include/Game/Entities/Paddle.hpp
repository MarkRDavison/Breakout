#ifndef INCLUDED_BREAKOUT_GAME_ENTITIES_PADDLE_HPP_
#define INCLUDED_BREAKOUT_GAME_ENTITIES_PADDLE_HPP_

#include <Definitions.hpp>
#include <Game/Entities/Ball.hpp>
#include <memory>

namespace brk {

	struct Paddle {
		ze::Vector2f position;
		ze::Vector2f size{ Definitions::CellSize * 3,Definitions::CellSize };

		enum class SizeState{
			Little,
			Normal,
			Big
		} sizeState{ SizeState::Normal };

		std::shared_ptr<Ball> ball;
	};

}

#endif // INCLUDED_BREAKOUT_GAME_ENTITIES_PADDLE_HPP_
#ifndef INCLUDED_BREAKOUT_GAME_ENTITIES_BALL_HPP_
#define INCLUDED_BREAKOUT_GAME_ENTITIES_BALL_HPP_

#include <Definitions.hpp>
#include <zeno/Graphics/Colour.hpp>

namespace brk {

	struct Ball {

		ze::Colour colour{ ze::Colour::Magenta };
		ze::Vector2f position;
		ze::Vector2f previousPosition;
		float radius{ Definitions::CellSize / 2.0f };
		float speed{ 24.0f };
		ze::Vector2f direction;

		bool outOfBounds{ false };
		int damage{ 2 };
	};

}

#endif // INCLUDED_BREAKOUT_GAME_ENTITIES_BALL_HPP_
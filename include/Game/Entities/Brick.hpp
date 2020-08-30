#ifndef INCLUDED_BREAKOUT_GAME_ENTITIES_BRICK_HPP_
#define INCLUDED_BREAKOUT_GAME_ENTITIES_BRICK_HPP_

#include <Definitions.hpp>

#include <zeno/Graphics/Colour.hpp>

namespace brk {

	struct Brick {

		ze::FloatRect bounds;
		ze::Colour colour{ ze::Colour::Blue };

		int hp{ 1 };
	};

}

#endif // INCLUDED_BREAKOUT_GAME_ENTITIES_BRICK_HPP_
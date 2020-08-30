#ifndef INCLUDED_BREAKOUT_GAME_ENTITIES_POWERUP_HPP_
#define INCLUDED_BREAKOUT_GAME_ENTITIES_POWERUP_HPP_

#include <Definitions.hpp>
#include <zeno/Graphics/Colour.hpp>

namespace brk {

	struct Powerup {

		ze::Colour colour{ ze::Colour::Yellow };
		ze::Vector2f position;
		ze::Vector2f previousPosition;
		float speed{ 8.0f };
		bool requiresRemoval{ false };
		enum class Type {
			BigPaddle,
			SmallPaddle
		} type;
	};

}

#endif // INCLUDED_BREAKOUT_GAME_ENTITIES_POWERUP_HPP_
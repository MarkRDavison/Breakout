#include <Game/Game.hpp>
#include <zeno/Core/VectorMath.hpp>
#include <algorithm>

namespace brk {

	Game::Game(ze::IInputActionManager& _inputActionManager) :
		m_InputActionManager(_inputActionManager) {

	}

	void Game::update(float _delta) {

		for (auto& p : paddles) {
			float offset = 0.0f;
			if (m_InputActionManager.isActionInvoked("Left")) {
				offset -= 1.0f;
			}
			if (m_InputActionManager.isActionInvoked("Right")) {
				offset += 1.0f;
			}

			if (offset != 0.0f) {
				p->position.x += offset * _delta * 16.0f;

				if (p->position.x - p->size.x / 2.0f - Definitions::CellGap < 0.0f) {
					p->position.x = Definitions::CellGap + p->size.x / 2.0f;
				}

				if (p->position.x + p->size.x / 2.0f + Definitions::CellGap > gameBounds.x) {
					p->position.x = gameBounds.x - p->size.x / 2.0f - Definitions::CellGap;
				}
			}

			if (p->ball && m_InputActionManager.isActionInvoked("Launch")) {
				p->ball->position = p->position + ze::Vector2f(0.0f, p->size.y / 2.0f + p->ball->radius);
				p->ball->direction = ze::normalise(ze::Vector2f(1.0f, 1.0f));
				balls.push_back(p->ball);
				p->ball = {};
			}
		}

		bool ballsOutOfBounds = false;
		for (auto& b : balls) {
			b->previousPosition = b->position;
			updateBall(b, _delta);
			if (b->outOfBounds) {
				ballsOutOfBounds = true;
			}

			if (ballsOutOfBounds) {
				balls.erase(std::remove_if(balls.begin(), balls.end(), [](const std::shared_ptr<Ball>& _ball) -> bool { return _ball->outOfBounds; }), balls.end());
				if (balls.empty()) {
					std::cout << "Balls all gone." << std::endl;
				}
			}
		}

		bricks.erase(std::remove_if(bricks.begin(), bricks.end(), [](const std::shared_ptr<Brick>& _brick) -> bool { return _brick->hp <= 0; }), bricks.end());
	}
	void Game::updateBall(std::shared_ptr<Ball>& _ball, float _delta) {
		const float start_delta = _delta;
		float minXDelta = std::numeric_limits<float>::max();
		float maxXDelta = std::numeric_limits<float>::max();
		float minYDelta = std::numeric_limits<float>::max();
		float maxYDelta = std::numeric_limits<float>::max();

		if (_ball->direction.x < 0.0f) {
			const float min = 0.0f + _ball->radius;

			const float nextX = _ball->position.x + _ball->direction.x * _ball->speed * _delta;

			if (nextX < min) {
				const float maxDelta = (min - _ball->position.x) / (_ball->direction.x * _ball->speed);

				_delta = maxDelta;
				minXDelta = maxDelta;
			}
		}
		if (_ball->direction.x > 0.0f) {
			const float max = gameBounds.x - _ball->radius;

			const float nextX = _ball->position.x + _ball->direction.x * _ball->speed * _delta;

			if (nextX > max) {
				const float maxDelta = (max - _ball->position.x) / (_ball->direction.x * _ball->speed);

				_delta = maxDelta;
				maxXDelta = maxDelta;
			}
		}

		if (_ball->direction.y > 0.0f) {
			const float max = 0.0f - _ball->radius;

			const float nextY = _ball->position.y + _ball->direction.y * _ball->speed * _delta;

			if (nextY > max) {
				const float maxDelta = (max - _ball->position.y) / (_ball->direction.y * _ball->speed);

				_delta = std::min(_delta, maxDelta);
				maxYDelta = maxDelta;
			}
		}
		if (_ball->direction.y < 0.0f) {
			if (_ball->position.y + _ball->radius < -gameBounds.y) {
				_delta = start_delta;
				_ball->outOfBounds = true;
				return;
			}
		}

		for (auto& b : bricks) {
			if (b->hp <= 0) { continue; }
			ze::FloatRect brickBounds(b->bounds);

			ze::Vector2f nextPos = _ball->position + _ball->direction * _ball->speed * _delta;

			const float nearestX = std::max(brickBounds.left, std::min(nextPos.x, brickBounds.left + brickBounds.width));
			const float nearestY = std::max(brickBounds.bot, std::min(nextPos.y, brickBounds.bot + brickBounds.height));

			const auto distance = ze::Vector2f(nextPos.x - nearestX, nextPos.y - nearestY);

			const auto length = ze::length(distance);
			const auto penDepth = _ball->radius - length;
			const auto penVect = ze::normalise(distance) * penDepth;
			 
			if (penDepth > 0.0f) {
				b->hp -= _ball->damage;
				if (b->hp == 1) {
					b->colour = ze::Colour::Blue;
				}
				if (b->hp == 2) {
					b->colour = ze::Colour::Green;
				}
				if (b->hp == 3) {
					b->colour = ze::Colour::Red;
				}

				const auto offset = (nextPos - _ball->direction * penDepth) - _ball->position;

				const float maxMove = ze::length(offset);

				const float delta_used = (maxMove / (_ball->speed * _delta)) * _delta;

				_delta = delta_used;

				// TODO: Need to adjust bounce angles better

				if (penVect.x < 0.0f) {
					maxXDelta = _delta;
				}
				if (penVect.x > 0.0f) {
					minXDelta = 0.0f;
				}
				if (penVect.y > 0.0f) {
					minYDelta = _delta;
				}
				if (penVect.y < 0.0f) {
					maxYDelta = _delta;
				}
			}
		}

		for (auto& p : paddles) {
			ze::FloatRect paddleBounds(p->position - p->size / 2.0f, p->size);

			ze::Vector2f nextPos = _ball->position + _ball->direction * _ball->speed * _delta;

			const float nearestX = std::max(static_cast<float>(paddleBounds.left), std::min(nextPos.x, static_cast<float>(paddleBounds.left) + paddleBounds.width));
			const float nearestY = std::max(static_cast<float>(paddleBounds.bot), std::min(nextPos.y, static_cast<float>(paddleBounds.bot) + paddleBounds.height));

			const auto distance = ze::Vector2f(nextPos.x - nearestX, nextPos.y - nearestY);

			const auto length = ze::length(distance);
			const auto penDepth = _ball->radius - length;
			const auto penVect = ze::normalise(distance) * penDepth;

			if (penDepth > 0.0f) {
				const auto offset = (nextPos - _ball->direction * penDepth) - _ball->position;

				const float maxMove = ze::length(offset);

				const float delta_used = (maxMove / (_ball->speed * _delta)) * _delta;

				_delta = delta_used;

				// TODO: Need to adjust bounce angles better

				if (penVect.x < 0.0f) {
					maxXDelta = _delta;
				}
				if (penVect.x > 0.0f) {
					minXDelta = 0.0f;
				}
				if (penVect.y > 0.0f) {
					minYDelta = _delta;
				}
				if (penVect.y < 0.0f) {
					maxYDelta = _delta;
				}
			}

		}

		_ball->position += _ball->direction * _ball->speed * _delta;

		if (maxXDelta == _delta ||
			minXDelta == _delta) {
			_ball->direction.x *= -1.0f;
		}
		if (maxYDelta == _delta ||
			minYDelta == _delta) {
			_ball->direction.y *= -1.0f;
		}

		if (start_delta != _delta) {
			updateBall(_ball, start_delta - _delta);
		}
	}

	ze::FloatRect Game::getBrickBounds(const ze::Vector2u& _brickSize, const ze::Vector2u& _startingCoordinates) {
		const float left =
			Definitions::CellGap +
			Definitions::CellGap * _startingCoordinates.x +
			Definitions::CellSize * _startingCoordinates.x;

		const float bottom =
			(-Definitions::CellGap-Definitions::CellSize) * static_cast<float>(_startingCoordinates.y + 1);

		const float width =
			Definitions::CellSize * static_cast<float>(_brickSize.x) +
			Definitions::CellGap * static_cast<float>(_brickSize.x - 1);

		const float height =
			Definitions::CellSize * static_cast<float>(_brickSize.y) +
			Definitions::CellGap * static_cast<float>(_brickSize.y - 1);

		return ze::FloatRect(left, bottom, width, height);		
	}
}
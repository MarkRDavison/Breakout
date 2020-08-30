#include <Game/GameRenderer.hpp>
#include <Definitions.hpp>
#include <cassert>

namespace brk {

	GameRenderer::GameRenderer(const Game* _game) :
		game(_game) {

	}
	void GameRenderer::update(float _delta) {

	}
	void GameRenderer::render(const ze::RenderTarget& _target, ze::RenderInfo _info) const {
		ze::RenderInfo info(_info);
		info.view.translate(ze::Vector3f(ze::Vector2f(-game->gameBounds.x / 2.0f, +game->gameBounds.y / 2.0f), 0.0f));

		ze::RectangleShape bounds(game->gameBounds);
		bounds.setInternalColour(ze::Colour::Cyan);
		bounds.setOutlineColour(ze::Colour::Red);
		bounds.setOutlineThickness(Definitions::CellGap);
		bounds.translate(ze::Vector2f(0.0f, -game->gameBounds.y));

		bounds.render(_target, info);

		ze::VertexArray v(ze::DrawType::Triangles);

		const auto& appendBrick = [](ze::VertexArray& _array, ze::FloatRect _brickBounds, ze::Colour _colour) {
			_array.appendVertex(ze::Vertex(ze::Vector2f(_brickBounds.left, _brickBounds.bot), _colour));
			_array.appendVertex(ze::Vertex(ze::Vector2f(_brickBounds.left + _brickBounds.width, _brickBounds.bot), _colour));
			_array.appendVertex(ze::Vertex(ze::Vector2f(_brickBounds.left + _brickBounds.width, _brickBounds.bot + _brickBounds.height), _colour));

			_array.appendVertex(ze::Vertex(ze::Vector2f(_brickBounds.left, _brickBounds.bot), _colour));
			_array.appendVertex(ze::Vertex(ze::Vector2f(_brickBounds.left + _brickBounds.width, _brickBounds.bot + _brickBounds.height), _colour));
			_array.appendVertex(ze::Vertex(ze::Vector2f(_brickBounds.left, _brickBounds.bot + _brickBounds.height), _colour));
		};

		for (const auto& b : game->bricks) {
			appendBrick(v, b->bounds, b->colour);
		}

		for (const auto& p : game->paddles) {
			appendBrick(v, ze::FloatRect(p->position - p->size / 2.0f, p->size), ze::Colour::Black);

			if (p->ball) {
				ze::CircleShape ball(p->ball->radius);
				ball.setInternalColour(ze::Colour::Black);
				ball.setTranslation(p->position + ze::Vector2f(0.0f, p->size.y / 2.0f + p->ball->radius));
				ball.render(_target, info);
			}
		}

		v.create();
		v.render(_target, info);

		for (const auto& b : game->balls) {
			ze::CircleShape ball(b->radius);
			ball.setInternalColour(b->colour);
			ball.setTranslation(b->position);
			ball.render(_target, info);
		}

		for (const auto& p : game->powerups) {
			ze::CircleShape powerup(0.5f);
			powerup.setInternalColour(p->colour);
			powerup.setTranslation(p->position);
			powerup.render(_target, info);
		}
	}

}
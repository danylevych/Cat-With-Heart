#include "Entity.h"

Entity::Entity(const sf::Vector2f& spawnPos)
	: spawnPos(spawnPos)
	, sprite()
{
	sprite.setPosition(spawnPos);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

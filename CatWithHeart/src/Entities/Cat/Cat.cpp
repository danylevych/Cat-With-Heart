#include "Cat.h"

#include "../../Utilities/Context/Context.h"

Cat::Cat(const sf::Vector2f& spawnPos)
	: AnimatedEntity(spawnPos, 
					 Context::GetInstance().textures.Get(TextureID::Cat), 
					 sf::seconds(0.15f))
{	}


sf::Vector2u Cat::GetOriginSize() const
{
	return animationTextures[0]->getSize();
}

// We bring the update method to public section
// so we need to redefine its behavior.
void Cat::Update(sf::Time deltaTime)
{
	AnimatedEntity::Update(deltaTime);
}

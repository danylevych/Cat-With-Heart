#include "Click.h"

#include "../../Utilities/Context/Context.h"


Click::Click(const sf::Vector2f& spawnPos)
    : AnimatedEntity(spawnPos,
                     Context::GetInstance().textures.Get(TextureID::ClickEffect),
                     sf::seconds(0.1f))
{   }

sf::Vector2u Click::GetOriginSize() const
{
    return animationTextures[0]->getSize();
}


// We bring the update method to public section
// so we need to redefine its behavior.
void Click::Update(sf::Time deltaTime)
{
    AnimatedEntity::Update(deltaTime);
}

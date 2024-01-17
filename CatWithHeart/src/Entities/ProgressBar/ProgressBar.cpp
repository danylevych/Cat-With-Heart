#include "ProgressBar.h"

#include "../../Utilities/Context/Context.h"

ProgressBar::ProgressBar()
	: Entity(sf::Vector2f())
	, textures(Context::GetInstance().textures.Get(TextureID::ProgressBar))
	, currentState(0)
{	
	sprite.setTexture(*textures[currentState]);
}

sf::Vector2u ProgressBar::GetOriginSize() const
{
	return textures.at(0)->getSize();
}

void ProgressBar::Update(sf::Time deltaTime)
{
	if (currentState < textures.size())
	{
		sprite.setTexture(*textures[currentState]);
	}
}

void ProgressBar::SetProgress(float_t progress)
{
	if (progress < 0) // Progress can't be negative number.
	{
		return;
	}

	currentState = static_cast<size_t>(progress * 100 / textures.size());

	Update(sf::Time::Zero);
}

bool ProgressBar::IsComplete() const
{
	return currentState == textures.size() - 1;
}

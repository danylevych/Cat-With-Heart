#include "Heart.h"

#include <string>
#include <stdexcept>


Heart::Heart(const sf::Vector2f& spawnPos, float_t startScale, float_t zoomedScale, sf::Time animTime)
	: Entity(spawnPos)
	, texture()
	, startScale(startScale)
	, zoomedScale(zoomedScale)
	, animeTime(animTime)
{
	std::string path = "data/textures/heart/heart.png";
	if (!texture.loadFromFile(path))
	{
		throw std::runtime_error("Opening file: '" + path + "' failed.");
	}

	sprite.setTexture(texture);
}

sf::Vector2u Heart::GetOriginSize() const
{
	return texture.getSize();
}

void Heart::Update(sf::Time deltaTime)
{
    static sf::Time timeAnim = sf::Time::Zero;
    static bool isZoomed = true;

    timeAnim += deltaTime;

    if (timeAnim >= animeTime)
    {
        isZoomed = !isZoomed;
        timeAnim = sf::Time::Zero;
    }

    float progress = timeAnim / animeTime; // Get the progress.

    if (isZoomed)
    {
        sf::Vector2f scale = getScale();
        scale.x = startScale + progress * (zoomedScale - startScale);
        scale.y = startScale + progress * (zoomedScale - startScale);
        setScale(scale);
    }
    else
    {
        sf::Vector2f scale = getScale();
        scale.x = zoomedScale - progress * (zoomedScale - startScale);
        scale.y = zoomedScale - progress * (zoomedScale - startScale);
        setScale(scale);
    }
}

void Heart::SetStartAnimeScale(float_t startScale)
{
	this->startScale = startScale;
}

void Heart::SetZoomedAnimeScale(float_t zoomedScale)
{
	this->zoomedScale = zoomedScale;
}

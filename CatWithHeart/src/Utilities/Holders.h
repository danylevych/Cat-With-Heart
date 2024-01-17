#pragma once

#include "ResourceHolder/ResourceHolder.h"


#include <SFML/Graphics/Font.hpp>
#include "../Enums/FontID.h"

using FontsHolder = ResourceHolder<FontID, sf::Font>;

#include <SFML/Graphics/Texture.hpp>
#include "../Enums/TextureID.h"

using TexturesHolder = ResourceHolder<TextureID, std::vector<sf::Texture>>;

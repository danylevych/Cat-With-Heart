#pragma once

#include "../Entity/Entity.h"
#include <vector>
#include <memory>


class ProgressBar : public Entity
{
private:
	size_t currentState;
	std::vector<std::unique_ptr<sf::Texture>>& textures;

public:
	ProgressBar();
	virtual ~ProgressBar() override = default;

public:
	//////////////////////////////////////////////////
	// \brief
	//		Method that returns the origin size
	//		of the entity.
	// 
	//////////////////////////////////////////////////
	virtual sf::Vector2u GetOriginSize() const;

private:
	//////////////////////////////////////////////////
	// \brief
	//		Update the state of the entity.
	// 
	//////////////////////////////////////////////////
	virtual void Update(sf::Time deltaTime);

public:
	//////////////////////////////////////////////////
	// \brief
	//	Set the progress and change the animation.
	// 
	//////////////////////////////////////////////////
	void SetProgress(float_t progress);

	//////////////////////////////////////////////////
	// \brief
	//	     Return the state of the loading.
	// 
	//////////////////////////////////////////////////
	bool IsComplete() const;
};


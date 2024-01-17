#pragma once

#include "../State/State.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../../Entities/ProgressBar/ProgressBar.h"


///////////////////////////////////////////////////
// \brief
//    Represent the loading state of the game.
// 
///////////////////////////////////////////////////
class LoadState : public State
{
public:
	using Ptr = std::unique_ptr<LoadState>;

private:
	sf::Text loadingLabel;
	ProgressBar progressBar;

	const sf::Time LOADING_TIME = sf::seconds(7.f);
	const sf::Time FREQUENCY_LABEL_UPDATE = sf::seconds(0.3f);

public:
	LoadState(StateStack& stack, Context& context);

	virtual ~LoadState() override = default;

public: // Overriden section.
	virtual void Draw() override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void HandleInput(const sf::Event& event) override;

public: // Initialize section.
	///////////////////////////////////////////////////
	// \brief
	//	   Initialize the progress bsr properies.
	// 
	///////////////////////////////////////////////////
	void InitProgressBar();

	///////////////////////////////////////////////////
	// \brief
	//			Initialize the loading lable.
	// 
	///////////////////////////////////////////////////
	void InitLoadingLabel();

private: // Helper functional.
	///////////////////////////////////////////////////
	// \brief
	//		    Update the progress bar.
	// 
	///////////////////////////////////////////////////
	void UpdateProgressBar(sf::Time deltaTime);

	///////////////////////////////////////////////////
	// \brief
	//		    Update the loading text.
	// 
	///////////////////////////////////////////////////
	void UpdateLoadingLabel(sf::Time deltaTime);
};
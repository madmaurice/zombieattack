#ifndef ANIMATED_HPP
#define ANIMATED_HPP

#include <SFML/Graphics.hpp>

#include "Animation.h"

/**
 * Base class for animated class
 */
class Animated
{
public:
	Animated(sf::Sprite& sprite, const Animation& animation);

	void Reset();

	/**
	 * Update subrect of the animated sprite
	 * @param frametime: Time of current frame
	 */
	void Update(float frametime);


	void SetAnimation(const Animation& animation);
	const Animation* GetAnimation() const;

private:
    sf::Sprite& _sprite;
	const Animation* animation_;
	int frame_; // current frame index
	float timer_;
};

#endif // ANIMATED_HPP


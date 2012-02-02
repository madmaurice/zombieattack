#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>


class Animation
{
public:
	Animation();

	/**
	 * Wait time between frame
	 * @param delay: Time in seconds
	 */
	void SetDelay(float delay);

	inline float GetDelay() const
	{ return delay_; }

  void SetLoop(bool loop);

	inline bool GetLoop() const
	{ return loop_; }

	float GetDuration() const;

	/**
	 * Add a frame into the animation
	 * @param subrect: Rectangle of the frame
	 */
	void AddFrame(const sf::IntRect& subrect);
	void AddFrame(int left, int up, int width, int height);

	/**
	 * Get a frame of the animation
	 * @param num_frame: Number of the frame ask
	 * @return Rectangle of the frame
	 */
	inline const sf::IntRect& GetFrame(int num_frame) const
	{ return subrects_[num_frame]; }

	/**
	 * Get the number of frame of this animation
	 */
	inline int GetSize() const
	{ return subrects_.size(); }

	void SetImage(const sf::Image& image);

	const sf::Image& GetImage() const;

private:
	std::vector<sf::IntRect> subrects_;
	const sf::Image* image_;
	float delay_;
  bool loop_;
};

#endif // ANIMATION_HPP


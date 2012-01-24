#ifndef EFFECT_SYSTEM_HPP
#define EFFECT_SYSTEM_HPP

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>

/**
 * Manage on screen effect
 */
class EffectSystem
{
public:
	/**
	 * Instance accessor
	 */
	static EffectSystem& GetInstance();

	/**
	 * Add an body part explosion 
	 * @param pos: sfx origin
	 * @param count: number of parts
	 */
	void bodyPartExplosion(const sf::Vector2f& pos, int count);


	/**
	 * Update all on screen effect
	 */
	void update(float frametime);

	/**
	 * Erase all effects
	 */
	void reset();

	void draw(sf::RenderTarget& target) const;
private:
	EffectSystem();
	~EffectSystem();

	typedef std::vector<sf::Image> ImageVect;
  ImageVect _bodyPartImg;

	/**
	 * Flying body part effect
	 */
	class BodyPart
	{
	public:
		BodyPart(sf::Vector2f pos, ImageVect& availableParts);
		~BodyPart() {};
		bool update(float frametime);

		void draw(sf::RenderTarget& target) const;
    void onComplete();
	private:
    bool _rotateClockwise;
		sf::Sprite _sprite;
    sf::Vector2f _pos;
    sf::Vector2f _velocity;
    float _rotation;
    float _speed;
		float _timer;
		float _lifetime;
	};

	typedef std::list<BodyPart> EffectList;
	EffectList _effectList;

};

#endif // EFFECT_SYSTEM_HPP


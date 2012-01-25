#include <SFML/System.hpp>
#include <iostream>

#include "EffectSystem.h"
#include "Resources.h"



EffectSystem& EffectSystem::GetInstance()
{
	static EffectSystem self;
	return self;
}


EffectSystem::EffectSystem() 
{ 
  //Load all body part images

  _bodyPartImg.push_back(&Resources::GetImage("body/body1.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body2.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body3.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body4.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body5.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body6.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body7.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body8.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body9.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body10.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body11.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body12.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body13.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body14.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body15.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body16.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body17.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body18.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body19.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body20.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body21.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body22.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body23.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body24.png"));
  _bodyPartImg.push_back(&Resources::GetImage("body/body25.png"));
}


EffectSystem::~EffectSystem()
{
	reset();
}


void EffectSystem::bodyPartExplosion(const sf::Vector2f& pos, int count)
{
  for (; count > 0; --count)
	{
    _effectList.push_front(BodyPart(*this, pos, _bodyPartImg));
  }
}


void EffectSystem::update(float frametime)
{
	EffectList::iterator it;
	for (it = _effectList.begin(); it != _effectList.end(); it++)
	{
    //If the effect return true it mean it's done
    //TODO code onComplete (transfer body part on bg...)
		if (it->update(frametime))
		{
			//delete *it;
      it->onComplete();
			it = _effectList.erase(it);
		}
	}
}


void EffectSystem::draw(sf::RenderTarget& target) const
{
	EffectList::const_iterator it = _effectList.begin();
	for (; it != _effectList.end(); ++it)
	{
		(*it).draw(target);
	}
}

void EffectSystem::drawBg(sf::RenderTarget& target) const
{
	BgSpriteVect::const_iterator it = _bgSprites.begin();
	for (; it != _bgSprites.end(); ++it)
	{
    target.Draw(*it);
	}
}

void EffectSystem::reset()
{
	EffectList::iterator it;
	//for (it = _effectList.begin(); it != _effectList.end(); ++it)
	//{
	//	delete *it;
	//}
	_effectList.clear();
}

void EffectSystem::addToBackground(sf::Sprite& sprite)
{
  _bgSprites.push_back(sprite);
}

// Body part explosion
#define BODY_MIN_LIFETIME      1.0f
#define BODY_MAX_LIFETIME      4.0f
#define BODY_SPEED_MIN         30.0f
#define BODY_SPEED_MAX         50.0f
#define BODY_TO_BG_PROB        75

EffectSystem::BodyPart::BodyPart(EffectSystem& eSystem, const sf::Vector2f pos, ImageVect& availableParts) : _effectSytem(eSystem), _pos(pos) 
{
  //get random available image
  int numBodyImage = availableParts.size();
  int imgIndex = sf::Randomizer::Random(0, numBodyImage -1);
  _sprite.SetImage(*availableParts.at(imgIndex));
  _sprite.Resize(20, 20);

  _sprite.SetPosition(_pos.x, _pos.y);

  //set random speed
  _speed = sf::Randomizer::Random(BODY_SPEED_MIN, BODY_SPEED_MAX);

  _rotation = sf::Randomizer::Random(0.0f, 360.0f);

  if (sf::Randomizer::Random(0.0f,1.0f) >= 0.5) {
    _rotateClockwise = true;
  }
  else {
    _rotateClockwise = false;
  }

  //set random velocity
	float angle = sf::Randomizer::Random( 0.0f, 6.2832f );
  _velocity.x = sf::Randomizer::Random( 0.0f, cos( angle ) );
  _velocity.y = sf::Randomizer::Random( 0.0f, sin( angle ) );

  //TODO maybe??
  //float scale = sf::Randomizer::Random(0.5f, 1.2f);
  //sprite_.SetScale(scale, scale);
	
	_lifetime = sf::Randomizer::Random(BODY_MIN_LIFETIME, BODY_MAX_LIFETIME);
	_timer = 0.f;
}


bool EffectSystem::BodyPart::update(float frametime)
{
	_timer += frametime;

  _pos.x = _velocity.x * _speed * frametime;
  _pos.y = _velocity.y * _speed * frametime;

  _sprite.Move(_pos.x, _pos.y);

  //TODO decrease speed over time??

  //Rotate the sprite
  if (_rotateClockwise) {
    _rotation += sf::Randomizer::Random(2, 5);
  }
  else {
    _rotation -= sf::Randomizer::Random(2, 5);
  }

  if (_rotation >= 360)
    _rotation = 0;

  _sprite.SetRotation(-_rotation);

	// Transpanrancy
	//sprite_.SetColor(sf::Color(255, 255, 255, (int) (255 - 255 * _timer / _lifetime)));
	return _timer >= _lifetime;
}

void EffectSystem::BodyPart::onComplete()
{
  //TODO
  if(sf::Randomizer::Random( 0, 100) <= BODY_TO_BG_PROB)
  {
    _effectSytem.addToBackground(_sprite);
  }
}


void EffectSystem::BodyPart::draw(sf::RenderTarget& target) const
{
  target.Draw(_sprite);
}

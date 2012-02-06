#include "Animated.h"
#include <iostream>

Animated::Animated(sf::Sprite& sprite) : _sprite(sprite)
{
}

Animated::Animated(sf::Sprite& sprite, const Animation& animation) : _sprite(sprite)
{
	SetAnimation(animation);
	_sprite.SetImage(animation_->GetImage());
	_sprite.SetSubRect(animation_->GetFrame(0));
}

void Animated::Reset()
{
	if (animation_ != NULL)
	{
		_sprite.SetImage(animation_->GetImage());
		_sprite.SetSubRect(animation_->GetFrame(0));
	  frame_ = 0;
	}
}


bool Animated::Update(float frametime)
{
	timer_ -= frametime;
  if (!animation_->GetLoop() && frame_ == animation_->GetSize() -1)
  {
    return false;
  }
  else if (timer_ <= 0)
	{
		timer_ = animation_->GetDelay();
		frame_ = (frame_ + 1) % animation_->GetSize();
		_sprite.SetSubRect(animation_->GetFrame(frame_));

	}

  return true;
}


void Animated::SetAnimation(const Animation& animation)
{
	animation_ = &animation;
	timer_ = animation.GetDelay();
  Reset();
}


const Animation* Animated::GetAnimation() const
{
	return animation_;
}

#include "Animated.h"


Animated::Animated(sf::Sprite& sprite, const Animation& animation) : _sprite(sprite)
{
	SetAnimation(animation);
}


void Animated::Reset()
{
	if (animation_ != NULL)
	{
		_sprite.SetImage(animation_->GetImage());
		_sprite.SetSubRect(animation_->GetFrame(0));
	}
}


void Animated::Update(float frametime)
{
	timer_ -= frametime;
	if (timer_ <= 0)
	{
		timer_ = animation_->GetDelay();
		frame_ = (frame_ + 1) % animation_->GetSize();
		_sprite.SetSubRect(animation_->GetFrame(frame_));
	}
}


void Animated::SetAnimation(const Animation& animation)
{
	animation_ = &animation;
	timer_ = animation.GetDelay();
	frame_ = 0;
}


const Animation* Animated::GetAnimation() const
{
	return animation_;
}

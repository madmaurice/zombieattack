#include "Bullet.h"
#include "Collision.h"

Bullet::Bullet(sf::Sprite adjusted_sprite, bool isBeam) : Entity(1, 1), _isBeam(isBeam)
{
  avatar = adjusted_sprite;
  speed *= 10;
  ignore = 1;
  type = FRIEND;
}

Bullet::~Bullet() {}

void Bullet::move(float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible, std::vector<Bullet*> &bullets, int me) 
{
  int _x = this->getSprite().GetPosition().x;
  int _y = this->getSprite().GetPosition().y;
  int _w  = avatar.GetSize().x;
  int _h = avatar.GetSize().y;

  float velocity = speed * ElapsedTime;

  if (!_isBeam)
  {

    int *available = collisions(objects, possible);
    if(facing == LEFT) 
    {
      _x += -velocity;
      if (_x > 0 && available[LEFT])
        avatar.Move(-velocity, 0);
      else 
      {
        delete bullets[me];
        bullets.erase(bullets.begin() + me);
      }
    }
    else if(facing == RIGHT) 
    {    
      _x += velocity;
      if (_x + _w < SCREEN_WIDTH && available[RIGHT])
        avatar.Move(velocity, 0);
      else 
      {
        delete bullets[me];
        bullets.erase(bullets.begin() + me);
      }
    }
    else if(facing == UP) 
    {
      _y += -velocity;
      if (_y > 0 && available[UP]) 
        avatar.Move(0, -velocity);   
      else 
      {
        delete bullets[me];
        bullets.erase(bullets.begin() + me);
      }
    }
    else if(facing == DOWN) 
    {
      _y += velocity;
      if (_y + _h < SCREEN_HEIGHT && available[DOWN])
        avatar.Move(0, velocity);
      else 
      {
        delete bullets[me];
        bullets.erase(bullets.begin() + me);
      }
    }  
    
    delete[] available;
  }
  else
  {
    for (unsigned int i = 0; i < objects.size(); i++)
    {
      if(objects[i]->getType() == FOE)
      {
        if (facing == LEFT)
        {
          //For left beam, BoundingBoxTest fail somehow...
          if(Collision::PixelPerfectTest(avatar, objects[i]->getSprite()))
            objects[i]->takeDamage(objects, i, getAttack());
        }
        else
        {
          if(Collision::BoundingBoxTest(avatar, objects[i]->getSprite()))
            objects[i]->takeDamage(objects, i, getAttack());
        }
      }
    }

    if(facing == LEFT) 
    {
      _x += -velocity;
      if (_x > 0)
        avatar.Move(-velocity, 0);
      else 
      {
        delete bullets[me];
        bullets.erase(bullets.begin() + me);
      }
    }
    else if(facing == RIGHT) 
    {    
      _x += velocity;
      if (_x + _w < SCREEN_WIDTH )
        avatar.Move(velocity, 0);
      else 
      {
        delete bullets[me];
        bullets.erase(bullets.begin() + me);
      }
    }
    else if(facing == UP) 
    {
      _y += -velocity;
      if (_y > 0 ) 
        avatar.Move(0, -velocity);   
      else 
      {
        delete bullets[me];
        bullets.erase(bullets.begin() + me);
      }
    }
    else if(facing == DOWN) 
    {
      _y += velocity;
      if (_y + _h < SCREEN_HEIGHT)
        avatar.Move(0, velocity);
      else 
      {
        delete bullets[me];
        bullets.erase(bullets.begin() + me);
      }
    }  
  }
}

void Bullet::drawEdge(sf::RenderWindow& window)
{
  int _x = avatar.GetPosition().x;
  int _y = avatar.GetPosition().y;
  int _w  = avatar.GetSize().x;
  int _h = avatar.GetSize().y;

  sf::Shape rect = sf::Shape::Rectangle(0, 0, _w, _h, sf::Color::Black, 2, sf::Color::Black); 
  rect.Rotate(avatar.GetRotation());
  rect.SetPosition(_x, _y);
  rect.EnableFill(false);
  window.Draw(rect);
}

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Bullet.h"

class Player : public Entity {

 public:
  Player();
  ~Player();
  
  void drawRage(sf::RenderWindow& window);
  void shoot(float ElapsedTime);
  std::vector<Bullet*> bullets;
  bool enemy(Object *subject);
  void takeDamage(std::vector<Object*> objects, int me, int damage);
  void addKill(int num = 1);
  inline int getKill() const
  { return kills; }

 private:

  void addRage(unsigned int num);

  const sf::Font& font;
  sf::String rageStr;
  unsigned int rage;
  int kills;
  int inventory;
  sf::Clock rageClock;
  sf::Shape rageMeter;
  sf::Shape rageMeterBox;
  sf::Image bullet_pic;
  sf::Sprite bullet_sprite;
  sf::SoundBuffer bite_wav;
  sf::SoundBuffer gun_wav;
  float last_shot;
  static const float SHOOT_DELAY;
  static const unsigned int MAX_RAGE;
  static const unsigned int KILL_RAGE;
  static const unsigned int HIT_RAGE;
  static const float HIT_DELAY;
};


#endif
  

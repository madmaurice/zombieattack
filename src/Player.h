#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Bullet.h"
#include "Animated.h"
#include "Animation.h"
#include "SpatialHash.h"

class Player : public Entity {

 public:
  Player();
  ~Player();
  
  void handleInput(sf::RenderWindow& App, float ElapsedTime, std::vector<Object*>& objects, SpatialHash& grid);
  void update(sf::RenderWindow& window);
  void draw(sf::RenderWindow& window);
  void enableRage();
  void shoot(float ElapsedTime);
  std::vector<Bullet*> bullets;
  bool enemy(Object *subject);
  void takeDamage(std::vector<Object*> objects, int me, int damage);
  void addKill(int num = 1);
  inline int getKill() const
  { return kills; }
  bool playDeath(sf::RenderWindow& window);
  virtual bool isPlayer();
  virtual bool isRageMode();

 private:
  void switchForm(bool saiyan);


  //Normal walk vector
  ImgVect nup;
  ImgVect ndown;
  ImgVect nleft;
  ImgVect nright;

  //Saiyan walk vectors
  ImgVect sup;
  ImgVect sdown;
  ImgVect sleft;
  ImgVect sright;
  
  //old sprite
  sf::Sprite saveSprite;

  void addRage(unsigned int num);
  void updateRageMode();

  bool rageMode;

  const sf::Font& font;
  sf::String rageStr;
  int rage;
  int kills;
  int inventory;
  sf::Clock rageClock;
  sf::Shape rageMeter;
  sf::Shape rageMeterBox;
  sf::Image bullet_pic;
  sf::Image beam_pic;
  sf::SoundBuffer bite_wav;
  sf::SoundBuffer gun_wav;
  sf::SoundBuffer kaioken_wav;
  sf::Sound kaioken;
  float last_shot;
  static const float SHOOT_DELAY;
  static const int MAX_RAGE;
  static const int KILL_RAGE;
  static const int HIT_RAGE;
  static const int RAGE_DECREASE;
  static const float RAGE_DECREASE_DELAY;
  static const float HIT_DELAY;

  //Saiyan
  bool isAnimated;
  sf::Image saiyanSheet;
  sf::Sprite saiyanSprite;
  Animation saiyanAnim;
  Animated saiyan;

  //Death
  sf::Image death_sheet;
  sf::Sprite death_sprite;
  Animation deathAnim;
  Animated death;
};


#endif
  

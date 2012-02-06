#ifndef BOSS_H
#define BOSS_H

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Particle.h"

class Boss : public Entity {

 public:
  Boss(ParticleSystem& pSys, int x = 0, int y = 0, int level = 1);
  ~Boss();  

  virtual void aggro(Object &target, float ElapsedTime, std::vector<Object*> objects, std::vector<int> possible, float running_time);
  virtual void takeDamage(std::vector<Object*> objects, int me, int damage);
  bool alive(std::vector<Object*> &objects, int me, float running_time);

 private:
  int inventory;
  float last_time;
  float death_time;
  sf::SoundBuffer zombie_wav;  
  sf::SoundBuffer zombie_attacked_wav;  
  ParticleSystem& partSystem;
  static const float SFX_DELAY;
  static const float DEATH_DELAY;
};

#endif
  

#include "Entity.h"
#include <iostream>

class Bullet : public Entity {

 public:
  Bullet(sf::Sprite adjusted_sprite, bool isBeam = true);
  ~Bullet();

  void move(float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible, std::vector<Bullet*> &bullets, int me);
  void drawEdge(sf::RenderWindow& window);
  
 protected:
  bool _isBeam;
};

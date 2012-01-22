#ifndef PEAK_H
#define PEAK_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum State {
    READY,
	MOVE_LEFT,
	DESTINATION,
	MOVE_RIGHT
};

class Peak 
{

 public:
  Peak(sf::RenderWindow& window);
  ~Peak();
  
  sf::Sprite& getSprite();
  void update();

 private:
  State _state;
  bool atDestination();
  bool outOfScreen();
  bool isEnable();
  void move();
  void wait();

  int _frameLimit; //Limit number of frame
  sf::Sound _toastySound;
  sf::SoundBuffer _toastyBuf;
  sf::RenderWindow& _window;
  sf::Image _picImg;
  sf::Sprite _picSprite;
  float _timeSinceShown;
  float _timeShown; //Time at destination
  int _xMove;
  static const int FRAME_DELAY;
  static const float SHOW_DELAY;
  static const float DEST_DELAY;
  static const float PROB;
  static const int X_POS;
  static const int Y_POS;
};

#endif
  

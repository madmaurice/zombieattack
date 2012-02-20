#ifndef PEAK_H
#define PEAK_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

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

  bool _isBubble; //Indicate if it's a bubble or toasty
  int _frameLimit; //Limit number of frame
  sf::Sound _toastySound;
  sf::SoundBuffer _toastyBuf;
  sf::RenderWindow& _window;
  sf::Image _picImg;
  sf::Image _arghImg;
  sf::Image _crisImg;
  sf::Image _fkImg;
  sf::Image _ostiImg;

  sf::Clock toastyClock;
  unsigned int _bubIndex;

	typedef std::vector<sf::Image*> ImageVect;
  ImageVect _bubbleVect;

  sf::Sprite _bubbleSprite;
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
  static const float BUBBLE_DELAY_MULT;
  static const int BUBBLE_X_POS;
  static const int BUBBLE_Y_POS;
};

#endif
  

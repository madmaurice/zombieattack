#ifndef CREDITS_H
#define CREDITS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Credits 
{

 public:
  Credits(sf::RenderWindow& window);
  ~Credits();
  
  sf::Sprite& getSprite();
  bool showCredits();
  void update();

 private:
  enum State {
      START,
    SCROLLING,
    WAIT_TITLE,
    END
  };

  bool scrollingDone();
  void processEvent();
  void scroll();

  State _state;

  //Display
  sf::RenderWindow& _window;
  sf::Image _bgImage;
  sf::Sprite _bgSprite;
  int _bgRectTop;
  int _bgRectBottom;
  bool _show;

  int _imgWidth;
  int _imgHeight;

  static const int SCROLL_DELAY;
  static const int ZOOM_LEVEL;
  static const int X_POS;
  static const int Y_POS;

};

#endif
  

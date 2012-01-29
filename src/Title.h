#ifndef TITLE_H
#define TITLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Title 
{

 public:
  Title(sf::RenderWindow& window);
  ~Title();
  
  sf::Sprite& getSprite();
  void update();
  bool showTitle();

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

  //Sound
  sf::Music _bgMusic;

  static const int SCROLL_DELAY;
  static const int ZOOM_LEVEL;
  static const int X_POS;
  static const int Y_POS;

};

#endif
  

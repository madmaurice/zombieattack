#include <iostream>
#include "Credits.h"
#include "Screen.h"

const int Credits::SCROLL_DELAY = 1;
const int Credits::X_POS = 16;
const int Credits::Y_POS = 0;
const int Credits::ZOOM_LEVEL = 3;

Credits::Credits(sf::RenderWindow& window) : _window(window)
{
  if (!_bgImage.LoadFromFile("../resources/backgrounds/credits.png")) {
    std::cout << "Error loading image title.png" << std::endl;
  }

  _imgWidth = _bgImage.GetWidth();
  _imgHeight = _bgImage.GetHeight();

  _bgSprite.SetImage(_bgImage);
  _bgSprite.SetPosition(X_POS, Y_POS);
  _bgSprite.Resize(_imgWidth * ZOOM_LEVEL, _imgHeight * ZOOM_LEVEL);

  _bgRectBottom = 470;
  _bgRectTop = -230;

  _bgSprite.SetSubRect(sf::IntRect(0, _bgRectTop, _imgWidth, _bgRectBottom));

  _state = START;
  _show = true;
}

Credits::~Credits() {}

bool Credits::showCredits()
{
    return _show;
}

void Credits::update()
{
  processEvent();

  switch (_state)
  {
    case START:
      _window.Draw(_bgSprite);
      _state = SCROLLING;
      break;
    case SCROLLING:
      scroll();
      if (scrollingDone())
        _state = WAIT_TITLE;

      _window.Draw(_bgSprite);
      break;
    case WAIT_TITLE:
      _state = END;
      _window.Draw(_bgSprite);
      break;
    case END:
      _window.Draw(_bgSprite);
      _show = false;
      break;
  }

}

void Credits::processEvent()
{
    if(_window.GetInput().IsKeyDown(sf::Key::Return))
    {
      _show = false;
    }
}

void Credits::scroll()
{
  static int numScroll = 0;

  if (numScroll >= SCROLL_DELAY)
  {
    numScroll = 0;

    _bgRectBottom++;
    _bgRectTop++;
    _bgSprite.SetSubRect(sf::IntRect(0, _bgRectTop, _bgImage.GetWidth(), _bgRectBottom));
  }
  else {
    numScroll++;
  }
}

bool Credits::scrollingDone()
{
    return _bgRectBottom >= 1310;
}

sf::Sprite& Credits::getSprite()
{
    return _bgSprite;
}


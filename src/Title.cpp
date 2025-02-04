#include <iostream>
#include "Title.h"
#include "Screen.h"

const int Title::SCROLL_DELAY = 1;
const int Title::X_POS = 16;
const int Title::Y_POS = 0;
const int Title::ZOOM_LEVEL = 3;

Title::Title(sf::RenderWindow& window) : _window(window)
{
  if (!_bgImage.LoadFromFile("../resources/backgrounds/title.png")) {
    std::cout << "Error loading image title.png" << std::endl;
  }

  if (!_bgTitleImg.LoadFromFile("../resources/backgrounds/titleName.png")) {
    std::cout << "Error loading image titleName.png" << std::endl;
  }
  _bgTitleSprite.SetImage(_bgTitleImg);
  _bgTitleSprite.Resize(_bgTitleImg.GetWidth() * ZOOM_LEVEL, _bgTitleImg.GetHeight() * ZOOM_LEVEL);
  _bgTitleSprite.SetPosition(120, 40);

  if (!_bgMusic.OpenFromFile("../resources/music/Title_Part_1.ogg")) {
    std::cout << "Error loading music Title 1" << std::endl; 
  }

  if (!_megaFont.LoadFromFile("../resources/fonts/megaman_2.ttf", 50)) {
    std::cout << "Fail megaman font" << std::endl;
  }
  _enterText.SetFont(_megaFont);
  _enterText.SetColor(sf::Color(255,255,255));
  _enterText.SetSize(25.0f);
  _enterText.SetPosition(140, 400);
  _enterText.SetText("Press Enter");

  unsigned int imgWidth = _bgImage.GetWidth();
  unsigned int imgHeight = _bgImage.GetHeight();

  _bgSprite.SetImage(_bgImage);
  _bgSprite.SetPosition(X_POS, Y_POS);
  _bgSprite.Resize(imgWidth * ZOOM_LEVEL, imgHeight * ZOOM_LEVEL);

  _bgRectBottom = imgHeight;
  _bgRectTop = (_bgRectBottom * ZOOM_LEVEL - SCREEN_HEIGHT) / ZOOM_LEVEL;

  _bgSprite.SetSubRect(sf::IntRect(0, _bgRectTop, imgWidth, _bgRectBottom));

  _state = START;
  _show = true;
}

Title::~Title() {}

bool Title::showTitle()
{
    return _show;
}

void Title::update()
{
  processEvent();

  switch (_state)
  {
    case START:
      _state = SCROLLING;
      _bgMusic.Play();
      _window.Draw(_bgSprite);
      break;
    case SCROLLING:
      scroll();
      if (scrollingDone())
        _state = WAIT_TITLE;

      _window.Draw(_bgSprite);
      break;
    case WAIT_TITLE:
      _state = END;
      _bgMusic.Stop();
      if (!_bgMusic.OpenFromFile("../resources/music/Title_Part_2.ogg")) {
        std::cout << "Error loading music Title 2" << std::endl; 
      }
      _bgMusic.Play();
      _window.Draw(_bgSprite);
      break;
    case END:
      _window.Draw(_bgSprite);
      _window.Draw(_bgTitleSprite);
      _window.Draw(_enterText);
      break;
  }

}

void Title::processEvent()
{
    if(_window.GetInput().IsKeyDown(sf::Key::Return))
    {
      _show = false;
      _bgMusic.Stop();
    }
}

void Title::scroll()
{
  static int numScroll = 0;

  if (numScroll >= SCROLL_DELAY)
  {
    numScroll = 0;
    _bgRectBottom--;
    _bgRectTop--;
    _bgSprite.SetSubRect(sf::IntRect(0, _bgRectTop, _bgImage.GetWidth(), _bgRectBottom));
  }
  else {
    numScroll++;
  }
}

bool Title::scrollingDone()
{
    return _bgRectTop <= 0;
}

sf::Sprite& Title::getSprite()
{
    return _bgSprite;
}


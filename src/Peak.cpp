#include <iostream>
#include "Peak.h"
#include "Screen.h"

const int Peak::FRAME_DELAY = 10;
const int Peak::X_POS = 620;
const int Peak::Y_POS = 500;
const float Peak::PROB = 1.0;
const float Peak::SHOW_DELAY = 2.0;
const float Peak::DEST_DELAY = 1.0;

Peak::Peak(sf::RenderWindow& window) : _window(window)
{
  if (!_picImg.LoadFromFile("../resources/Oli.png")) {
    std::cout << "Error loading image Oli png" << std::endl;
  }

  if (!_toastyBuf.LoadFromFile("../resources/sfx/toasty.wav")) {
    std::cout << "Error loading sfx" << std::endl; 
  }
  _toastySound.SetBuffer(_toastyBuf);
  _toastySound.SetVolume(50.f);
  _picSprite.SetImage(_picImg);
  _picSprite.SetPosition(SCREEN_WIDTH, Y_POS);
  _timeSinceShown = 0;
  _timeShown = 0;
  _state = READY;
  _frameLimit = FRAME_DELAY;

  //Screen width - X_POS / 3
  _xMove = 60;
}

Peak::~Peak() {}

void Peak::update()
{
    if (isEnable())
    {
        move();
        _timeSinceShown = 0;
        _window.Draw(_picSprite);
    }
    else 
    {
        float frameTime = _window.GetFrameTime();
        _timeSinceShown += frameTime;
        _timeShown = 0;
    }
}

bool Peak::atDestination()
{
    int posX = _picSprite.GetPosition().x;

    return posX <= X_POS;
}

bool Peak::outOfScreen()
{
    int posX = _picSprite.GetPosition().x;

    return posX >= SCREEN_WIDTH;
}

void Peak::move()
{
    float frameTime = _window.GetFrameTime();
    switch (_state) {
        case READY:
            _timeShown = 0;
            _state = MOVE_LEFT;
            break;
        case MOVE_LEFT:
            if (atDestination())
            {
                _state = DESTINATION;
                _frameLimit = 0;
                _toastySound.Play();
            }
            else
            {
                if (_frameLimit >= FRAME_DELAY)
                {
                    int posX = _picSprite.GetPosition().x;
                    int newPosX = posX - _xMove;
                    _picSprite.SetPosition(newPosX, Y_POS);
                }
                else 
                {
                    _frameLimit++;
                }
            }
            break;
        case DESTINATION:
            _timeShown += frameTime;

            if (_timeShown >= DEST_DELAY)
            {
                _state = MOVE_RIGHT;
            }

            break;
        case MOVE_RIGHT:
            if (outOfScreen())
            {
                _state = READY;
                _frameLimit = 0;
            }
            else
            {
                if (_frameLimit >= FRAME_DELAY)
                {
                    int posX = _picSprite.GetPosition().x;
                    int newPosX = posX + _xMove;
                    _picSprite.SetPosition(newPosX, Y_POS);
                }
                else 
                {
                    _frameLimit++;
                }
            }
            break;
        default:
            break;
    }
}

bool Peak::isEnable()
{
    //TODO probability
    if (_state == READY)
    {
        return _timeSinceShown > SHOW_DELAY;
    }
    else
    {
        return true;
    }
}

sf::Sprite& Peak::getSprite()
{
    return _picSprite;
}


#include <iostream>
#include "Peak.h"
#include "Screen.h"

const int Peak::FRAME_DELAY = 10;
const int Peak::X_POS = 640;
const int Peak::Y_POS = 500;
const float Peak::PROB = 1.0;
const float Peak::SHOW_DELAY = 10;
const float Peak::DEST_DELAY = 1.0;
const float Peak::BUBBLE_DELAY_MULT = 2.0;
const int Peak::BUBBLE_X_POS = 520;
const int Peak::BUBBLE_Y_POS = 500;

Peak::Peak(sf::RenderWindow& window) : _window(window)
{
  if (!_picImg.LoadFromFile("../resources/Oli.png")) {
    std::cout << "Error loading image Oli png" << std::endl;
  }
  if (!_arghImg.LoadFromFile("../resources/sprites/speech/Argh.png")) {
    std::cout << "Error loading image bubble" << std::endl;
  }
  if (!_crisImg.LoadFromFile("../resources/sprites/speech/Crisse.png")) {
    std::cout << "Error loading image bubble" << std::endl;
  }
  if (!_fkImg.LoadFromFile("../resources/sprites/speech/Fuck.png")) {
    std::cout << "Error loading image bubble" << std::endl;
  }
  if (!_ostiImg.LoadFromFile("../resources/sprites/speech/Osti.png")) {
    std::cout << "Error loading image bubble" << std::endl;
  }

  //Fill vector of bubbles
  _bubbleVect.push_back(&_fkImg);
  _bubbleVect.push_back(&_arghImg);
  _bubbleVect.push_back(&_ostiImg);
  _bubbleVect.push_back(&_crisImg);

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

  _isBubble = false;
  _bubIndex = 0;

  toastyClock.Reset();
}

Peak::~Peak() {}

void Peak::update()
{
    if (isEnable())
    {
        move();
        _timeSinceShown = 0;
        _window.Draw(_picSprite);

        if (_isBubble && _state == DESTINATION)
          _window.Draw(_bubbleSprite);
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
          {
            _timeShown = 0;
            _state = MOVE_LEFT;

            if (toastyClock.GetElapsedTime() > 30)
            {
              //Decide if this is a bubble or toasty
              if (sf::Randomizer::Random(0,100) >= 75)
              {
                _isBubble = true;
              }
              else
              {
                toastyClock.Reset();
                _isBubble = false;
              }
            }
            else
            {
              _isBubble = true;
            }

            break;
          }
        case MOVE_LEFT:
            {
              if (atDestination())
              {
                  _state = DESTINATION;
                  _frameLimit = 0;

                  if (_isBubble)
                  {
                    int bubbleIndex;
                    //Use _bubIndex if < vector size
                    if (_bubIndex < _bubbleVect.size() -1)
                    {
                      bubbleIndex = _bubIndex;
                      _bubIndex++;
                    }
                    else
                    {
                      bubbleIndex = sf::Randomizer::Random(0, _bubbleVect.size() -1);
                    }

                    //Get bubble sprite
                    _bubbleSprite = sf::Sprite(*_bubbleVect[bubbleIndex]);
                    _bubbleSprite.SetPosition(BUBBLE_X_POS, BUBBLE_Y_POS);
                  }
                  else
                  {
                    _toastySound.Play();
                  }
              }
              else
              {
                  if (_frameLimit >= FRAME_DELAY)
                  {
                      int posX = _picSprite.GetPosition().x;
                      int newPosX = posX - _xMove;

                      if (newPosX > X_POS)
                        newPosX = X_POS;

                      _picSprite.SetPosition(newPosX, Y_POS);
                  }
                  else 
                  {
                      _frameLimit++;
                  }
              }
              break;
            }
        case DESTINATION:
            {
              _timeShown += frameTime;

              float delay = DEST_DELAY;

              if (_isBubble)
                delay *= BUBBLE_DELAY_MULT;

              if (_timeShown >= delay)
              {
                  _state = MOVE_RIGHT;
              }

              break;
            }
        case MOVE_RIGHT:
            {
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
            }
        default:
            break;
    }
}

bool Peak::isEnable()
{
    if (_state == READY)
    {
        return _timeSinceShown > SHOW_DELAY && (sf::Randomizer::Random(0,10) >= 8);
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


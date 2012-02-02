#include <iostream>

#include "Player.h"
#include "Resources.h"
#include "Screen.h"

const float Player::SHOOT_DELAY = 0.25;
const int Player::MAX_RAGE = 100;
const int Player::KILL_RAGE = 2;
const int Player::HIT_RAGE = 5;
const float Player::HIT_DELAY = 2;
const int Player::RAGE_DECREASE = 5;
const float Player::RAGE_DECREASE_DELAY = 1;

Player::Player() : Entity(10000, 1), font(Resources::GetFont("megaman_2.ttf")), death(death_sprite){
  
  down.push_back(&Resources::GetImage("Oli_walkFront1.png"));
  down.push_back(&Resources::GetImage("Oli_walkFront2.png"));
  down.push_back(&Resources::GetImage("Oli_walkFront3.png"));

  up.push_back(&Resources::GetImage("Oli_walkBack1.png"));
  up.push_back(&Resources::GetImage("Oli_walkBack2.png"));
  up.push_back(&Resources::GetImage("Oli_walkBack3.png"));

  right.push_back(&Resources::GetImage("Oli_walkRight1.png"));
  right.push_back(&Resources::GetImage("Oli_walkRight2.png"));
  right.push_back(&Resources::GetImage("Oli_walkRight3.png"));

  left.push_back(&Resources::GetImage("Oli_walkLeft1.png"));
  left.push_back(&Resources::GetImage("Oli_walkLeft2.png"));
  left.push_back(&Resources::GetImage("Oli_walkLeft3.png"));

  for(unsigned int i = 0; i < 3; ++i)
    down[i]->CreateMaskFromColor(sf::Color(255, 255, 255));
  for(unsigned int i = 0; i < 3; ++i)
    up[i]->CreateMaskFromColor(sf::Color(255, 255, 255));
  for(unsigned int i = 0; i < 3; ++i)
    left[i]->CreateMaskFromColor(sf::Color(255, 255, 255));
  for(unsigned int i = 0; i < 3; ++i)
    right[i]->CreateMaskFromColor(sf::Color(255, 255, 255));

  avatar.SetImage(*down[0]);
  avatar.SetColor(sf::Color(255, 255, 255, 255));

  type = FRIEND;

  int _x = SCREEN_WIDTH/2-avatar.GetSize().x/2;
  int _y = SCREEN_HEIGHT/2-avatar.GetSize().y/2;
  
  avatar.SetPosition(_x, _y);
		     
  speed *= 2;
  frame_buffer = 0;
  facing = DOWN;
  last_shot = 0.0;  

  if (!bullet_pic.LoadFromFile("../resources/sprites/bullet.png")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!beam_pic.LoadFromFile("../resources/sprites/beam.png")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!bite_wav.LoadFromFile("../resources/sfx/bite.wav")) {
    std::cout << "Error loading sfx" << std::endl; 
    exit(EXIT_SUCCESS);
  }

  if (!gun_wav.LoadFromFile("../resources/sfx/gun.wav")) {
    std::cout << "Error loading sfx" << std::endl; 
    exit(EXIT_SUCCESS);
  }

  if (!death_sheet.LoadFromFile("../resources/sprites/Death.png")) {
    std::cout << "Error loading sfx" << std::endl; 
    exit(EXIT_SUCCESS);
  }

  rage = 0;
  kills = 0;

  rageMode = false;

  rageStr.SetFont(font);
  rageStr.SetColor(sf::Color(255, 255, 255));
  rageStr.SetSize(12.f);
  rageStr.SetPosition(45, 75);
  rageStr.SetText("R A G E");

  rageClock.Reset();

  //Init rage meter
  rageMeterBox = sf::Shape::Rectangle(0, 0, 100, 15, sf::Color::Black, 2, sf::Color::Black); 
  rageMeterBox.SetPosition(25,75);
  rageMeterBox.EnableFill(false);
  rageMeter = sf::Shape::Rectangle(0, 0, rage, 15, sf::Color::Red); 
  rageMeter.SetPosition(25,75);

  //Set up animation
  int width = 113;
  int height = 113;

  deathAnim.SetImage(death_sheet);
  deathAnim.AddFrame(sf::IntRect(1, 1, width, height));
  deathAnim.AddFrame(sf::IntRect(115, 1, 115+width, height));
  deathAnim.AddFrame(sf::IntRect(229, 1, 229+width, height));
  deathAnim.AddFrame(sf::IntRect(343, 1, 343+width, height));
  deathAnim.AddFrame(sf::IntRect(457, 1, 457+width, height));
  deathAnim.AddFrame(sf::IntRect(571, 1, 571+width, height));
  deathAnim.SetDelay(0.15f);

  death.SetAnimation(deathAnim);
  death_sprite.SetPosition(SCREEN_WIDTH/4, SCREEN_HEIGHT/4);
  death_sprite.Resize(width * 3, height * 3);
}

Player::~Player() {}

void Player::shoot(float running_time) {

  sf::Sprite bullet_sprite;
  if (rageMode)
  {
    bullet_sprite.SetImage(beam_pic);
  }
  else
  {
    bullet_sprite.SetImage(bullet_pic);
  }

  if ((running_time - last_shot) > SHOOT_DELAY) {

    int _x = this->getSprite().GetPosition().x;
    int _y = this->getSprite().GetPosition().y;
    int _w = avatar.GetSize().x;
    int _h = avatar.GetSize().y;

    int _sw = bullet_sprite.GetSize().x;
    int _sh = bullet_sprite.GetSize().y;
    // to ignore player
    int sprite_offset = 10;

    if (facing == DOWN) {
      bullet_sprite.Rotate(180);
      bullet_sprite.SetPosition(_x+_w/2 + _sw/2, _y+_h + sprite_offset + _sh/2);
      Bullet *tmp = new Bullet(bullet_sprite, rageMode);
      tmp->setFacing(DOWN);
      bullets.push_back(tmp);
      bullet_sprite.Rotate(180);
    }
    else if (facing == UP) {
      bullet_sprite.SetPosition(_x + _w/2 - _sw/2, _y-sprite_offset - _sh/2);
      Bullet *tmp = new Bullet(bullet_sprite, rageMode);
      tmp->setFacing(UP);
      bullets.push_back(tmp);
    }
    else if (facing == LEFT) {
      bullet_sprite.Rotate(90);
      bullet_sprite.SetPosition(_x-sprite_offset- _sw/2, _y + _h/2 + _sh/2);
      Bullet *tmp = new Bullet(bullet_sprite, rageMode);
      tmp->setFacing(LEFT);
      bullets.push_back(tmp);
      bullet_sprite.Rotate(270);
    }
    else if (facing == RIGHT) {
      bullet_sprite.Rotate(270);
      bullet_sprite.SetPosition(_x + _w + sprite_offset + _sw/2, _y + _h/2 - _sh/2);
      Bullet *tmp = new Bullet(bullet_sprite, rageMode);
      tmp->setFacing(RIGHT);
      bullets.push_back(tmp);
      bullet_sprite.Rotate(90);
    }
    sound.SetBuffer(gun_wav); 
    sound.SetVolume(50.f);
    sound.Play();
    last_shot = running_time;
  }
}

void Player::enableRage()
{
  if (rage >= MAX_RAGE && rageMode == false)
  {
    rageMode = true;
    rageClock.Reset();
    //TODO animation + sound
  }
}

void Player::update(sf::RenderWindow& window)
{
  //Need to decrease rage?
  if (rageMode)
  {
    updateRageMode();
  }

  rageMeter = sf::Shape::Rectangle(0, 0, rage, 15, sf::Color::Red); 
  rageMeter.SetPosition(25,75);
  window.Draw(rageMeterBox);
  window.Draw(rageMeter);
  window.Draw(rageStr);
}

void Player::takeDamage(std::vector<Object*> objects, int me, int damage) {

  if (sound.GetStatus() != sf::Sound::Playing) {
    sound.SetBuffer(bite_wav); 
    sound.SetVolume(200.f);
    sound.Play();
  }
  if (!rageMode)
  {
    health -= damage;

    if (rageClock.GetElapsedTime() >= HIT_DELAY)
    {
      rageClock.Reset();
      addRage(HIT_RAGE);
    }
  }
}

void Player::addKill(int num)
{
  kills+= num;
  addRage(KILL_RAGE);
}

bool Player::enemy(Object *subject)
{
    return false;
}

void Player::updateRageMode()
{
  if (rageClock.GetElapsedTime() >= RAGE_DECREASE_DELAY)
  {
    rage -= RAGE_DECREASE;
    if (rage < 0)
    {
      rage = 0;
      rageMode = false;
    }

    rageClock.Reset();
  }
}

void Player::addRage(unsigned int num)
{
  if (!rageMode)
  {
    rage += num;

    if (rage > MAX_RAGE)
      rage = MAX_RAGE;
  }
}

bool Player::playDeath(sf::RenderWindow& window)
{
  window.Clear();
  bool result = death.Update(window.GetFrameTime());
  window.Draw(death_sprite);

  return result;
}

#include "Music.h"
#include <iostream>


const std::string basePath = "../resources/music/";


const std::string normal = "dark_encounter.ogg";
const std::string boss = "vbogey.ogg";
const std::string gameover = "credits.ogg";

//Rage tune
const std::string onepiece = "one_piece.ogg";
const std::string naruto = "naruto.ogg";
const std::string bang = "bang.ogg";


Music& Music::GetInstance()
{
	static Music self;
	return self;
}

Music::Music()
{
  _currentSong = "";
  _lastSong = "";
}

Music::~Music()
{
}

void Music::stop()
{
  if (_bgMusic.GetStatus() == sf::Sound::Playing)
  {
    _bgMusic.Stop();
  }
}

void Music::playLast()
{
  playingRage = false;
  changeSong(_lastSong);
}

void Music::playNormal()
{
  if(!playingRage)
  {
    changeSong(normal);
    _lastSong = normal;
  }
}

void Music::playBoss()
{
  if (!playingRage)
  {
    changeSong(boss);
    _lastSong = boss;
  }
}

void Music::playGameOver()
{
  changeSong(gameover);
}

std::string Music::getSong()
{
  return _currentSong;
}

void Music::playRageMode()
{
  playingRage = true;
  int num = sf::Randomizer::Random(1,3);
  std::string song;
  float vol= 60.0f;

  switch (num)
  {
    case 1:
      song = onepiece;
      break;
    case 2:
      song = naruto;
      vol = 40.0f;
      break;
    case 3:
      song = bang;
      vol = 70.0f;
      break;
  }

  changeSong(song, vol);
}

void Music::changeSong(const std::string& song, float volume)
{
  if (_currentSong != "")
    stop();

  if (!_bgMusic.OpenFromFile(basePath + song)) {

    std::cout << "Error loading music " << song << std::endl; 
    return;
  }
  _bgMusic.SetVolume(volume);

  _currentSong = song;

  _bgMusic.Play();
}

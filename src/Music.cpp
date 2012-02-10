#include "Music.h"
#include <iostream>


const std::string basePath = "../resources/music/";


const std::string normal = "cry_of_the_planet.ogg";
const std::string boss = "cry_of_the_planet.ogg";
const std::string gameover = "previously_lost.mp3";

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
    std::cout << "Stoping" << std::endl;
    _bgMusic.Stop();
  }
}

void Music::playLast()
{
  std::cout << "Last : " << _lastSong << std::endl;
  changeSong(_lastSong);
}

void Music::playNormal()
{
  changeSong(normal);
}

void Music::playBoss()
{
  changeSong(boss);
}

void Music::playGameOver()
{
  changeSong(gameover);
}

void Music::playRageMode()
{
  int num = sf::Randomizer::Random(1,3);
  std::string song;

  _lastSong = _currentSong;

  switch (num)
  {
    case 1:
      song = onepiece;
      break;
    case 2:
      song = naruto;
      break;
    case 3:
      song = bang;
      break;
  }

  changeSong(song);
}

void Music::changeSong(const std::string& song)
{
  if (_currentSong != "")
    stop();

  if (!_bgMusic.OpenFromFile(basePath + song)) {

    std::cout << "Error loading music " << song << std::endl; 
    return;
  }

  _currentSong = song;

  _bgMusic.Play();
}

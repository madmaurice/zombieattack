#ifndef MUSIC_H
#define MUSIC_H

#include <SFML/Audio.hpp>

class Music 
{

 public:
	/**
	 * Instance accessor
	 */
	static Music& GetInstance();
  
  void stop();
  void playLast();
  void playNormal();
  void playBoss();
  void playGameOver();
  void playRageMode();

  std::string getSong();

 private:

  Music();
  ~Music();

  void changeSong(const std::string& song, float volume = 60.0f);
  bool playingRage;

  //Sound
  sf::Music _bgMusic;
  std::string _currentSong;
  std::string _lastSong;
};

#endif
  

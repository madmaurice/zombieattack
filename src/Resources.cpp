#include "Resources.h"
#include <iostream>


//Init static fields
const std::string Resources::_path = "../resources";
Resources::ImageMap Resources::_imgMap;
Resources::FontMap Resources::_fontMap;
Resources::SoundMap Resources::_soundMap;

const std::string imgBasePath = "/sprites/";
const std::string soundBasePath = "/sfx/";
const std::string musicBasePath = "/music/";


sf::Image& Resources::GetImage(const std::string& name)
{
	ImageMap::iterator it = _imgMap.find(name);
	if (it == _imgMap.end())
	{
		sf::Image& img = _imgMap[name];
		if (!img.LoadFromFile(_path + imgBasePath + name))
      std::cout << "Failed to load Image : " << name << std::endl;
		img.SetSmooth(false);
		return img;
	}
	return it->second;
}


const sf::Font& Resources::GetFont(const std::string& name, int size)
{
	FontMap::iterator it = _fontMap.find(name);
	if (it == _fontMap.end())
	{
		sf::Font& font = _fontMap[name];
		font.LoadFromFile(_path + "/fonts/" + name, size);
		return font;
	}
	return it->second;
}


const sf::SoundBuffer& Resources::GetSoundBuffer(const std::string& name)
{
	SoundMap::iterator it = _soundMap.find(name);
	if (it == _soundMap.end())
	{
		sf::SoundBuffer& sound = _soundMap[name];
		sound.LoadFromFile(_path + soundBasePath + name);
		return sound;
	}
	return it->second;
}


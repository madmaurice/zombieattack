#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**
 * Static class for loading resources
 */
class Resources
{
public:
	// Load an image
	static sf::Image& GetImage(const std::string& name);

	// Load a font
	static const sf::Font& GetFont(const std::string& name, int size=12);

	// Load a sound buffer
	static const sf::SoundBuffer& GetSoundBuffer(const std::string& name);

	// Unload allocated resources
	static void Unload();

private:
	static const std::string _path;

	typedef std::map<std::string, sf::Image> ImageMap;
	static ImageMap _imgMap;

	typedef std::map<std::string, sf::Font> FontMap;
	static FontMap _fontMap;

	typedef std::map<std::string, sf::SoundBuffer> SoundMap;
	static SoundMap _soundMap;
};

#endif // RESOURCES_HPP


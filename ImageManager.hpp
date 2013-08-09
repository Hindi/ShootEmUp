#pragma once
#include "stdafx.h"

/*! 
 *  \brief     Manages images loading
 *  \details   This class is used to manage the memory taken by images and to return textures from these images
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   A wrong filepath will give you an empty image.
 *  \copyright GNU Public License.
 */

class ImageManager
{
public:
    ImageManager();
    ~ImageManager();

	//! Return the image located at "filename" (may use loadImage())
    const sf::Image& getImage(const std::string& filename);
	//! Load in memory the image located at "filename"
    void loadImage(const std::string& filename);
	//! Return a reference to a texture of the full image located at "filename"
    const sf::Texture& getTexture(const std::string& filename);
	//! Return a reference to a texture of the image located at "filename" cut in the rectangle
    const sf::Texture& getTexture(const std::string& filename, sf::Rect<int> rect);	

private:
	//! Images list with their corresponding names
    std::map< std::string, sf::Image > m_images;
	//! Textures list
	std::vector<sf::Texture> m_textures;			
};

ImageManager::ImageManager() :
            m_images()
{

}

ImageManager::~ImageManager()
{
	m_images.clear();
}

const sf::Texture& ImageManager::getTexture( const std::string& filename )
{
	
	//Check if the image is already loaded
	for( std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); ++it)
		if( filename == it->first )
		{
			sf::Texture texture;
			texture.loadFromImage(it->second);
			m_textures.push_back(texture);
			return m_textures.back();
		}
	//If not, we load it
	loadImage(filename);
	return getTexture(filename);
}

const sf::Texture& ImageManager::getTexture(const std::string& filename, sf::Rect<int> rect)
{
	//Check if the image is already loaded
	for( std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); ++it)
		if( filename == it->first )
		{
			sf::Texture texture;
			texture.loadFromImage(it->second, rect);
			m_textures.push_back(texture);
			return m_textures.back();
		}
	//If not, we load it
	loadImage(filename);
	return getTexture(filename, rect);
}

const sf::Image& ImageManager::getImage( const std::string& filename )
{
	//Check if the image is already loaded
	for( std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); ++it)
		if( filename == it->first )
			return it->second;

	//If not, we load it
	loadImage(filename);
	return getImage(filename);
}

void ImageManager::loadImage( const std::string& filename )
{
	sf::Image image;

	//Loads the file in memory and saves it
	if( image.loadFromFile(filename) )
		m_images[filename] = image;
	else
	{
		std::cout << "GAME_ERROR: Image was not found. It is filled with an empty image.\n";
		m_images[filename] = image;
	}
}

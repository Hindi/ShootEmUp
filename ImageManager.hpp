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

	//! Return the image located at "filename"
    const sf::Image& getImage(const std::string& filename);
	//! Return a reference to a texture of the full image located at "filename"
    sf::Texture& getTexture(const std::string& filename);
	//! Return a reference to a texture of the image located at "filename" cut in the rectangle
    sf::Texture& getTexture(const std::string& filename, sf::Rect<int> rect);	

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

sf::Texture& ImageManager::getTexture( const std::string& filename )
{
	sf::Texture texture;
	texture.loadFromImage(getImage(filename));
	m_textures.push_back(texture);
	return m_textures.back();
}

sf::Texture& ImageManager::getTexture(const std::string& filename, sf::Rect<int> rect)
{
	sf::Texture texture;
	texture.loadFromImage(getImage(filename), rect);
	m_textures.push_back(texture);
	return m_textures.back();
}

const sf::Image& ImageManager::getImage( const std::string& filename )
{
	//Check weither the image is already loaded or not
	for( std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); ++it)
		if( filename == it->first )
			return it->second;

	//The image does not exist in memory, we need to load it
	sf::Image image;

	if( image.loadFromFile(filename) )
	{
		m_images[filename] = image;
		return m_images[filename];
	}
	else
		std::cout << "Image '" << filename <<"' was not found. It is filled with an empty image";
	return image;
}
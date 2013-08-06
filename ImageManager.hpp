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

	//Renvoie l'image demandée
    const sf::Image& getImage(const std::string& filename);
    //Va chercher le fichier et stocke l'image dans une liste
    void loadImage(const std::string& filename);
	//Renvoie l'image demandée sous forme de texture
    const sf::Texture& getTexture(const std::string& filename);
	//Découpe une image pour en extraire une texture
    const sf::Texture& getTexture(const std::string& filename, sf::Rect<int> rect);

private:
    //Image manager
    ImageManager& operator =(const ImageManager&);

    //Liste d'images avec le nom
    std::map< std::string, sf::Image > m_images;
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
	sf::Texture texture;
	//On regarde si l'image a été chargée en mémoire
	for( std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); ++it)
		if( filename == it->first )
		{
			texture.loadFromImage(it->second);
			return texture;
		}
	//Si non on la charge
	loadImage(filename);
	return getTexture(filename);
}

const sf::Texture& ImageManager::getTexture(const std::string& filename, sf::Rect<int> rect)
{
	sf::Texture texture;
	//On regarde si l'image a été chargée en mémoire
	for( std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); ++it)
		if( filename == it->first )
		{
			texture.loadFromImage(it->second, rect);
			return texture;
		}
	//Si non on la charge
	loadImage(filename);
	return getTexture(filename, rect);
}

const sf::Image& ImageManager::getImage( const std::string& filename )
{
	//On vérifie que l'image n'existe pas déjà
	for( std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); ++it)
		if( filename == it->first )
			return it->second;

	//L'image n'existe pas, on la créé et on la sauvegarde
	loadImage(filename);
	return getImage(filename);
}

void ImageManager::loadImage( const std::string& filename )
{
	sf::Image image;

	//On cherche l'image pour la garder en mémoire
	if( image.loadFromFile(filename) )
		m_images[filename] = image;
	else
	{
		std::cout << "GAME_ERROR: Image was not found. It is filled with an empty image.\n";
		m_images[filename] = image;
	}
}

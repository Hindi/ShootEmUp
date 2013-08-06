#include "stdafx.h"

#include "ImageManager.hpp"

/*! 
 *  \brief     The game itself
 *  \details   Stores user settings, gaming loops and game steps
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   None
 *  \copyright GNU Public License.
 */

class Game
{
public:
	Game();
	~Game();
	
	void StartGame();
	bool loadConfig();

private:
	template<typename T>
	void checkAndSave(std::string line, std::string reference, T &t);

	ImageManager m_imageManager;
	const std::string m_configFile;
	sf::Vector2i resolution;
	std::vector<std::string> configList;
};

void tokenize(const std::string& str,  std::vector< std::string>& tokens);

Game::Game():
	m_configFile("config.txt"),
	m_imageManager()
{

}

Game::~Game()
{

}

void Game::StartGame()
{
	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "SmartPong");
	sf::Sprite sprite;
	sf::Texture text = m_imageManager.getTexture("images/huk.png", sf::Rect<int>(0,0,10,10));
	sprite.setTexture(text);
	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
		window.draw(sprite);

        window.display();
		sf::sleep(sf::Time(sf::milliseconds(10)));
    }
}

template<typename T>
void Game::checkAndSave(std::string line, std::string reference, T &t)
{
	std::vector<std::string> tokens;
	tokenize(line, tokens);
	if(strcmp(tokens[0].c_str(), reference.c_str())==0)
    {
        std::istringstream buffer(tokens[1]);
        int value = atoi(tokens[1].c_str());
        t = value;
    }
}

bool Game::loadConfig()
{
	std::ifstream fichier(m_configFile, std::ios::in);
    if(fichier)  // If the file exists
    {
       std::string line;
        while(!strcmp(line.data(), "OVER")==0)
        {
            getline(fichier, line);
			configList.push_back(line);
        }
        fichier.close();
    }
    else
	{
        std::cout << "Config file not found !"  << std::endl;
		return false;
	}
	for(int l(0); l < configList.size(); ++l)
	{
		checkAndSave<int>(configList[l], "resolutionX", resolution.x);
		checkAndSave<int>(configList[l], "resolutionY", resolution.y);
	}
	return true;
}

void tokenize(const std::string& str,  std::vector< std::string>& tokens)
{
     std::string::size_type lastPos = str.find_first_not_of(" ", 0);
    //Le premier "non délimiteur"
     std::string::size_type pos = str.find_first_of(" ", lastPos);

    while ( std::string::npos != pos ||  std::string::npos != lastPos)
    {
        // On trouve un token, on l'ajoute au vecteur
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // On passe le délimiteur
        lastPos = str.find_first_not_of(" ", pos);
        // On repère le prochain token
        pos = str.find_first_of(" ", lastPos);
    }
    if(tokens.empty())
        tokens.push_back("empty");
}
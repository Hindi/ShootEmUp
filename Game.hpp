#include "stdafx.h"

#include "ImageManager.hpp"
#include "CollisionManager.hpp"
#include "InputManager.hpp"
#include "entities\EntityManager.hpp"
#include "entities\Entity.hpp"
#include "entities\Player.hpp"
#include "entities\ProjectileManager.hpp"

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
	
	//! Starts the game (creating the window included). Used after loadConfig().
	void StartGame();
	//! Loads the configuration file "config.txt" and saves the parameters
	bool loadConfig();

private:
	//! Used to check the lines in the config file and to save the parameter in the proper variable
	template<typename T>
	void checkAndSave(std::string line, std::string reference, T &t);

	//! The path to the config file
	const std::string m_configFile;
	//! The resolution of the window
	sf::Vector2i resolution;
	//! The configuration parameters list
	std::vector<std::string> configList;
};

void tokenize(const std::string& str,  std::vector< std::string>& tokens);

Game::Game():
	m_configFile("config.txt")
{

}

Game::~Game()
{

}

void Game::StartGame()
{
	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "ShootEmUp");
	ImageManager imageManager;
    sf::Event event;
	ProjectileManager ProjManager(imageManager, window);
	sf::Texture text;
	text.loadFromImage(imageManager.getImage("images/ball.png"));
	Player player(text, ProjManager);
	EntityManager entityManager(imageManager, window, player);
	CollisionManager collisionManager(entityManager, ProjManager, resolution);
	InputManager inputManager(entityManager, window, event);

	entityManager.createEnnemy(sf::Vector2f(100,100));
	entityManager.createEnnemy(sf::Vector2f(800,500));
	entityManager.createEnnemy(sf::Vector2f(800,00));
	entityManager.createEnnemy(sf::Vector2f(0,500));
	entityManager.createEnnemy(sf::Vector2f(000,000));
	entityManager.createEnnemy(sf::Vector2f(800,500));

	std::vector< std::shared_ptr<Entity> > ents = entityManager.canCollide(sf::Rect<float> (500,50,500,50));
	for(int e(0); e < ents.size(); ++e)
		std::cout << ents[e]->getPosition().x << " " << ents[e]->getPosition().y << std::endl;

	while (window.isOpen())
    {
        window.clear();

		inputManager.update();
		collisionManager.update();
		entityManager.update();
		ProjManager.update();

		entityManager.draw();
		ProjManager.draw();

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
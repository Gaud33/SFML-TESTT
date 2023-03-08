#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int bulletPosX , bulletPosY ;
int bulletSpeedX = 0, bulletSpeedY = 0;

int targetSizeX = 50, targetSizeY = 50;
int winTextPosX = -50, winTextPosY = -50;


int colorDisp = 10;
int main() {
	RenderWindow window(VideoMode(600, 600), "My Window");
	int targetSpeed = 1;

	//Background texture
	Texture targetText;
	if(!targetText.loadFromFile("Resources\\target.jpg")) {
		cout << "Failed to load target";
	}
	
	//Font for winscreen
	Font font;
	font.loadFromFile("Resources\\ArialTh.ttf");

	Text winText;
	Text instructions;

	// After completing game
	winText.setFont(font);
	winText.setString("YOU WIN!\n Press Escape to restart");
	winText.setFillColor(Color::Green);
	winText.setCharacterSize(30);
	winText.setPosition(Vector2f(150, 150));
	
	//instructions
	instructions.setFont(font);
	instructions.setString("Shoot= Space, Move= Arrow keys");
	instructions.setFillColor(Color::White);
	instructions.setCharacterSize(30);
	instructions.setPosition(Vector2f(20, 450));

	CircleShape bullet(5);
	bullet.setFillColor(Color::Magenta);
	RectangleShape target(Vector2f(targetSizeX, targetSizeY));
	target.setTexture(&targetText);

	
	CircleShape sprite(50);


	sprite.setPosition(sf::Vector2f(30, 30));
	
	bullet.setPosition(Vector2f(30, 30));
	target.setPosition(Vector2f(530, 270));


	while (window.isOpen()) {
		Event ev;
		

		while (window.pollEvent(ev)) {

			switch (ev.type)
			{
			case Event::Closed:
				window.close();

				break;

				
			
			}
			
		}
		//to get player and bullet to move together
		bulletPosX = sprite.getPosition().x;
		bulletPosY = sprite.getPosition().y;

		// once it moves out of bounds
		if (bullet.getPosition().x >= 590) {
			bullet.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y));
			
			//to kill speed
			bulletSpeedX = 0;
		}

		
		
		bullet.move(Vector2f(0.5 * bulletSpeedX, 0));
		target.move(Vector2f(0, 0.25 * targetSpeed));
	

		//To continuously bounce target up/down
		if (target.getPosition().y >= 600-target.getSize().x) {

			targetSpeed = -targetSpeed;
		}

		else if (target.getPosition().y <= 0) {
			targetSpeed = -targetSpeed;
		}

		// Player Movement code
		if (Keyboard::isKeyPressed (sf::Keyboard::Right))
		{
			if (sprite.getPosition().x <= 500) {
				sprite.move(sf::Vector2f(0.25, 0));
				bullet.move(sf::Vector2f(0.25, 0));
			}
		}

		 if (Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			 if (sprite.getPosition().x >= 0) {
				 sprite.move(sf::Vector2f(-0.25, 0));
				 bullet.move(sf::Vector2f(-0.25, 0));
			 }
		}

		 if (Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			 if (sprite.getPosition().y >= 0) {
				 sprite.move(sf::Vector2f(0, -0.25));
				 bullet.move(sf::Vector2f(0, -0.25));
			 }
		}

		 if (Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			 if (sprite.getPosition().y <= 500) {
				 sprite.move(sf::Vector2f(0, 0.25));
				 bullet.move(Vector2f(0, 0.25));
			 }
		}

		 //Reset
		 if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			sprite.setPosition(sf::Vector2f(30, 30));
			bullet.setPosition(Vector2f(bulletPosX, bulletPosY));
			targetSizeX = 50;
			targetSizeY = 50;
			target.setSize(Vector2f(targetSizeX, targetSizeY));
		}

		 //Bullet movement
		 if (Keyboard::isKeyPressed(Keyboard::Space)) {
			 bulletSpeedX = 1;
		 }

		 
		 //Collision detection with target
		 if (bullet.getGlobalBounds().intersects(target.getGlobalBounds())) {
			 
			 bulletSpeedX = 0;
			 bullet.setPosition(Vector2f(bulletPosX, bulletPosY));

			 //To visualize target has been shot
			 targetSizeX -= 10;
			 targetSizeY -= 10;
			 target.setSize(Vector2f(targetSizeX, targetSizeY));
	
			 
			 


		 }

		 if (target.getSize().x == 0) {
			 window.draw(winText);
		 }
		else window.clear();

		window.draw(sprite);
		window.draw(target);
		window.draw(bullet);
		window.draw(instructions);
		
		
		window.display();
	}
}

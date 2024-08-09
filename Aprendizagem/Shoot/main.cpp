/*
g++ -Wall -Wextra -Werror main.cpp -o app.exe -lsfml-graphics -lsfml-window -lsfml-system
./app.exe

g++ main.cpp -o main
./main
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <cstdlib>


int main (){

    srand(time(NULL));

    // Definir janela e suas propriedades
    sf::RenderWindow window;
    sf::Vector2u windSize(1024, 768);
    window.create(sf::VideoMode(windSize.x, windSize.y), "Shoot Game", sf::Style::Default);
    window.setFramerateLimit(144);

    // Deixar cursor invisivel
    window.setMouseCursorVisible(false);

        // Objetos

    // Jogador
    sf::CircleShape player;
    player.setFillColor(sf::Color(128, 0, 128));
    player.setRadius(50.f);
    player.setPosition(((windSize.x / 2) - player.getRadius()), (((windSize.y) - player.getRadius() * 2 ) - 10.f ));
    sf::Vector2f playerCenter;
    int shootTimer = 0;


    // Tiros
    sf::CircleShape bullet;
    bullet.setFillColor(sf::Color::Red);
    bullet.setRadius(5.f);

    // Array para ter varios tiros
    std::vector<sf::CircleShape> projectiles;
    projectiles.push_back(sf::CircleShape(bullet));

    // Inimigo
    sf::RectangleShape target;
    target.setFillColor(sf::Color::Green);
    target.setSize(sf::Vector2f(60.f, 60.f));

    // Array para ter varios inimigos
    std::vector<sf::RectangleShape> enemies;
    enemies.push_back(sf::RectangleShape(target));
    int enemySpawnTimer = 0;



    while(window.isOpen()){

        sf::Event event;

        while(window.pollEvent(event)){

            // Fechar janela clicando no X
            if(event.type == sf::Event::Closed){
                window.close();
            } 

            // Fechar janela caso aperte ESC
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
        }

            // updated
        
        // Spawn do player ser no meio inferior da tela
        playerCenter = sf::Vector2f((player.getPosition().x + player.getRadius() - bullet.getRadius()), (player.getPosition().y));

        // Atirando
        if ( shootTimer < 16 ){
            shootTimer++;
        }

        // Mexer o player deacordo com a posição X do mouse
        player.setPosition(sf::Mouse::getPosition(window).x, player.getPosition().y);


        // Sistema para atirar ao clicar no mouse
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer > 15){

            // Tiro sair do meio superior do player
            bullet.setPosition(playerCenter);

            // Adicionr o tiro ao array de projeteis
            projectiles.push_back(sf::CircleShape(bullet));
            
            shootTimer = 0;
        }

        // Enquanto tiver tiver tiros no array de projeteis, atirar
        for ( size_t i = 0; i < projectiles.size(); i++ ){
            projectiles[i].move(0.f, -10.f);

            // Remover o tiro do array quando o tiro sair da tela
            if ( projectiles[i].getPosition().y < 0 ){
                projectiles.erase(projectiles.begin() + i);
            }
        }
        
        // Regular tempo de spawn dos inimigos
        if ( enemySpawnTimer < 50 ){
            enemySpawnTimer++;
        }
        
        if ( enemySpawnTimer > 49){
            // Spawnar em um lugar aleatorio no eixo X na parte superior da tela
            target.setPosition(rand() % (windSize.x - static_cast<int>(target.getSize().x)), 0);

            // Adicionar o inimigo ao array de inimigos
            enemies.push_back(sf::RectangleShape(target));

            enemySpawnTimer = 0;
        }

        // Enquanto tiver inimigos no array, eles andam pra baixo
        for ( size_t i = 0; i < enemies.size(); i++ ){
            enemies[i].move(0.f, 5.f);

            // Remover inimigo do array ao sair da tela
            if ( enemies[i].getPosition().y > windSize.y){
                enemies.erase(enemies.begin() + i);
            }
        }

        // Colisão
        for ( size_t i = 0; i < projectiles.size(); i++ ){
            for ( size_t j = 0; j < enemies.size(); j++ ){
                // Se o tiro colidor com o inimigo, remover o tiro e o inimigo
                if ( projectiles[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())){
                    projectiles.erase(projectiles.begin() + i);
                    enemies.erase(enemies.begin() + j);
                    break;
                }

            }
        }


            // clean the window
        window.clear();


            // draw everthing ( shape's )
        
        // Projetar o player
        window.draw(player);

        // Projetar os inimigos
        for ( size_t i = 0; i < enemies.size(); i++){
            window.draw(enemies[i]);
        }

        // Projetar os tiros 
        for ( size_t i = 0; i < projectiles.size(); i++){
            window.draw(projectiles[i]);
        }

            // continue showing the window
        window.display();


    }

    return 0;

}
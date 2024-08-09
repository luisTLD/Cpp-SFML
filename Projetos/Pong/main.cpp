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
#include <cstdlib>

sf::Vector2f rectPosi(sf::RectangleShape& shape, const sf::Vector2f& position);
sf::Vector2f circlePosi(sf::CircleShape& shape, const sf::Vector2f& position);

int main () {

    bool spacePressed = false;
    bool firstTouch = false;
    bool gameOver = false;

    // para a bola nao contar mais de 1 toque por vez no player
    bool touch = true;

    // contar pontos
    int points = 0;
    int maxPoints = 0;

    // iniciar uma semente aleatoria
    std::srand(std::time(0));

    // definir a janela e suas propriedades
    sf::RenderWindow window;
    sf::Vector2u windSize(1280, 960);
    window.create(sf::VideoMode(windSize.x, windSize.y), "Pong", sf::Style::Default);
    window.setPosition(sf::Vector2i(250, 10));
    window.setFramerateLimit(144);

    // criar icone e suas cores
    const sf::Uint8 icon[] = {
                0,0,0,255, 0,0,0,255, 0,0,0,255,
                0,0,0,255, 0,255,0,0, 0,0,0,255,
                0,0,0,255, 0,0,0,255, 0,0,0,255,
    };

    // tamanho do icone
    sf::Vector2<unsigned> size; 
    size.x = 3;
    size.y = 3;

    // seta o icone para a janela
    window.setIcon(size.x, size.y, icon);

    // Definir fonte
    sf::Font font;
    if (!font.loadFromFile("KURIER.TTF")) 
    {
        // Erro ao carregar a fonte
        window.close(); 
    }

    // texto para o botao de retry
    sf::Text stringButton;
    stringButton.setFont(font);
    stringButton.setString("Jogar novamente");
    stringButton.setCharacterSize(31); 
    stringButton.setFillColor(sf::Color::Red);
    stringButton.setStyle(sf::Text::Bold);

    // texto para o botao endGame
    sf::Text closeGame;
    closeGame.setFont(font);
    closeGame.setCharacterSize(28);
    closeGame.setFillColor(sf::Color::Red);
    closeGame.setStyle(sf::Text::Bold);
    closeGame.setString("Fechar jogo");

    // texto para mostrar sua pontuação
    sf::Text stringPoint;
    stringPoint.setFont(font);
    stringPoint.setCharacterSize(30);
    stringPoint.setFillColor(sf::Color::Red);
    stringPoint.setStyle(sf::Text::Bold);
    sf::Text stringMaxPoint;
    stringMaxPoint.setFont(font);
    stringMaxPoint.setCharacterSize(60);
    stringMaxPoint.setFillColor(sf::Color::Red);
    stringMaxPoint.setStyle(sf::Text::Bold);

    // definir os objetos
    sf::CircleShape ball(25.f);
    sf::RectangleShape player(sf::Vector2f(175.f, 25.f));
    sf::RectangleShape bot(sf::Vector2f(175.f, 25.f));
    sf::RectangleShape downBorder(sf::Vector2f(windSize.x, 10));
    sf::RectangleShape upBorder(sf::Vector2f(windSize.x, 10));
    sf::RectangleShape retry(sf::Vector2f(300.f, 100.f));
    sf::RectangleShape endGame(sf::Vector2f(200.f, 80.f));

    // linha vermelha 
    downBorder.setFillColor(sf::Color::Red);
    upBorder.setFillColor(sf::Color::Red);

    // definir posição inicial dos objetos
    ball.setPosition(circlePosi(ball, sf::Vector2f(windSize.x / 2, windSize.y / 2)));
    player.setPosition(rectPosi(player,(sf::Vector2f(windSize.x/2, windSize.y - 50))));
    bot.setPosition(rectPosi(bot,(sf::Vector2f(windSize.x / 2, 50))));
    upBorder.setPosition(0, 0);
    downBorder.setPosition(0, windSize.y - downBorder.getSize().y);
    retry.setPosition((windSize.x / 2) - (retry.getSize().x / 2), (windSize.y / 2) - (retry.getSize().y / 2));
    endGame.setPosition((windSize.x / 2) - (endGame.getSize().x / 2), (windSize.y / 2) + (endGame.getSize().y));

    // Posicionar texto dentro dos objetos
    closeGame.setPosition(endGame.getPosition().x, endGame.getPosition().y + endGame.getSize().y / 4);
    stringButton.setPosition(retry.getPosition().x, retry.getPosition().y + retry.getSize().y / 4);
    stringPoint.setPosition(windSize.x/2 - 275, 60);
    stringMaxPoint.setPosition(windSize.x/2 - 275, 120);

    // vetor para definir a velocidade de movimento da bola
    sf::Vector2f ballSpeed(0.f, -6.f);

    while ( window.isOpen()) {

        sf::Event event;

        while(window.pollEvent(event)){

            // fechar janela clicando no X 
            if ( event.type == sf::Event::Closed ){
                window.close();
            }

            // fechar janela caso aperte ESC
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
                window.close();
            }

            // sistema para uma ação ao clicar no espaço ser realizada apenas 1 vez
            if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Space && !spacePressed ){
                    spacePressed = true;
                }
            }

        }

            // updated
        
        // moviemntação da bola + bot acompanhando
        ball.move(ballSpeed);
        bot.move(ballSpeed.x, 0);

        // verificar se a bola tocou nas laterais
        if ( ball.getPosition().x < 0 || (ball.getPosition().x + (ball.getRadius() * 2)) > windSize.x ){

            // inverter direção horizontal da bola
            ballSpeed.x *= -1;

            // aumentar a velocidade horizontal deacordo com a direção
            ballSpeed.x > 0 ? ballSpeed.x += 0.8 : ballSpeed.x -= 0.8;

        }
        
        // verificar se a bola tocou em cima ou embaixo
        if ( ball.getPosition().y < 0 || (ball.getPosition().y + (ball.getRadius() * 2) > windSize.y)){
            gameOver = true;
        }

        // verificar se a bola tocou no bot
        if ( ball.getGlobalBounds().intersects(bot.getGlobalBounds())){

            if(!firstTouch){
                if ( std::rand() % 2 == 0 ){
                ballSpeed.x = 6;
                }
                else{
                ballSpeed.x = -6;
                }
                firstTouch = true;
            }

            // deixar aleatorio a direção horizontal da bola ao tocar no bot
            if ( std::rand() % 2 == 0 ){
                ballSpeed.x = abs(ballSpeed.x);
            }
            else{
                ballSpeed.x = -1 * abs(ballSpeed.x);
            }

            // inverter direção vertical da bola
            ballSpeed.y *= -1;

            // aumentar velocidade vertical 
            ballSpeed.y += 0.2;

            // aumentar a velocidade horizontal deacordo com a direção
            ballSpeed.x > 0 ? ballSpeed.x += 0.4 : ballSpeed.x -= 0.4;

            touch = true;
        }

        // verificar se a bola tocou no player
        if ( ball.getGlobalBounds().intersects(player.getGlobalBounds()) && touch){

            // determinar direção deacordo com posição que toca na barra
            if ( (ball.getPosition().x + ball.getRadius()) > (player.getPosition().x + (player.getSize().x/2))){
                ballSpeed.x = abs(ballSpeed.x); 
            }
            if ( (ball.getPosition().x + ball.getRadius()) < (player.getPosition().x + (player.getSize().x/2))){
                ballSpeed.x = -1 * abs(ballSpeed.x); 
            }

            // inverter direção vertical da bola
            ballSpeed.y *= -1;

            // aumentar velocidade vertical
            ballSpeed.y -= 0.2;

            // aumentar a velocidade horizontal deacordo com a direção
            ballSpeed.x > 0 ? ballSpeed.x += 0.4 : ballSpeed.x -= 0.4;

            touch = false;
            points++;
        }

        // andar para esquerda
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x >=0){
            player.move(-10.f, 0);
        }   

        // andar para direita
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x <= ( windSize.x - player.getSize().x )) {
            player.move(10.f, 0);
        }

        // apertar espaço dar um dash para o lado 
        if ( spacePressed ){
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  ){
                player.move(-200.f, 0);
            }   
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                player.move(200.f, 0);
            }
            spacePressed = false;
        }

        // clean the window
        window.clear();

        // draw everthing ( shape's )
        window.draw(ball);
        window.draw(player);
        window.draw(bot);
        window.draw(upBorder);
        window.draw(downBorder);

        // continue showing the window
        window.display(); 
        
        // finalizar o jogo
        while ( gameOver ){

            // Quantidade de pontos
            if ( points > maxPoints ) maxPoints = points;
            stringPoint.setString("Pontos: " + std::to_string(points));
            stringMaxPoint.setString("Maior ponto: " + std::to_string(maxPoints));

            while(window.pollEvent(event)){

                // fechar janela clicando no X 
                if(event.type == sf::Event::Closed){
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed){

                    if (event.mouseButton.button == sf::Mouse::Left){

                        if (retry.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){

                            // Clicou no botao retry
                            gameOver = false;
                            ball.setPosition(circlePosi(ball, sf::Vector2f(windSize.x / 2, windSize.y / 2)));
                            player.setPosition(rectPosi(player,(sf::Vector2f(windSize.x/2, windSize.y - 50))));
                            bot.setPosition(rectPosi(bot,(sf::Vector2f(windSize.x / 2, 50))));
                            firstTouch = false;
                            ballSpeed.x = 0.f;
                            ballSpeed.y = -6.f;
                            points = 0;
                            
                        }

                        else if (endGame.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                            
                            // Encerrar jogo 
                            window.close();
                            
                        }
                    }
                }
            }
            

            // updated

            // clean the window
            window.clear();

            // draw everthing ( shape's )
            window.draw(retry);
            window.draw(endGame);
            window.draw(closeGame);
            window.draw(stringButton);
            window.draw(stringMaxPoint);
            window.draw(stringPoint);

            // continue showing the window
            window.display();


        }
        
    }

    return 0;

}


// funções para receber uma posição no plano 2D e retornar os pontos para centralizar um objeto
sf::Vector2f rectPosi(sf::RectangleShape& shape, const sf::Vector2f& position){
      return sf::Vector2f(position.x - (shape.getSize().x / 2), position.y - (shape.getSize().y / 2));
}

sf::Vector2f circlePosi(sf::CircleShape& shape, const sf::Vector2f& position){
    return sf::Vector2f(position.x - shape.getRadius(), position.y - shape.getRadius());
}

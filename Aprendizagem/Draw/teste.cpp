/*
g++ -Wall -Wextra -Werror teste.cpp -o app.exe -lsfml-graphics -lsfml-window -lsfml-system
.\app.exe

g++ teste.cpp -o teste
./teste
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <cstdlib>

/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Teste SFML");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
*/

int main (){

    // contador para o frame rate
    //      int c = 0; 
    
    const std::string title = "app"; 
    
    // cria uma janela NxM com nome de title
    sf::RenderWindow window(sf::VideoMode(640, 480), title, sf::Style::Default); 
    
    // window.create(sf::VideoMode(640, 480), title);
   
    // controla o framerate, quanto menor, mais lento
    window.setFramerateLimit(30); 

    // muda as dimensoes da janela
    // window.setSize(sf::Vector2u(400, 400));
    
    // muda o nome da janela
    // window.setTitle("New title"); 
    
    // array do tamanho de 36 elementos,  3(size) * 3(size) * 4(valores para a cor)
    // cada conjunto é uma cor
    const sf::Uint8 icon[] = {
            0,0,0,255, 0,0,0,255, 0,0,0,255,
            0,0,0,255, 0,0,0,255, 0,0,0,255,
            0,0,0,255, 0,0,0,255, 0,0,0,255,
    };

    
    sf::Vector2<unsigned> size; // sf::Vector2u
    size.x = 3;
    size.y = 3;

    // seta o icone para a janela
    window.setIcon(size.x, size.y, icon);

    // criar um poligono
    sf::ConvexShape convex;
    convex.setPosition(sf::Vector2f(400.f, 50.f));

    convex.setPointCount(5);

    convex.setPoint(0, sf::Vector2f(0, 0));
    convex.setPoint(1, sf::Vector2f(150, 10));
    convex.setPoint(2, sf::Vector2f(120, 90));
    convex.setPoint(3, sf::Vector2f(30, 100));
    convex.setPoint(4, sf::Vector2f(0, 50));

    // Vertex, criando uma linha
    sf::Vertex line[] = { sf::Vertex(sf::Vector2f(100.f, 400.f)), sf::Vertex(sf::Vector2f(50.f, 100.f)) };

    // criar um triangulo improvisado
    sf::CircleShape triangle;
    triangle.setRadius(50.f);
    triangle.setPointCount(3); // define o circulo com apenas 3 "vertices"
    triangle.setOutlineColor(sf::Color::Blue); // cor da borda
    triangle.setOutlineThickness(5.f); // espessura da borda

    // formato de circulo ( raio )
    sf::CircleShape shape(50.f);

    // define a cor do shape
    shape.setFillColor(sf::Color(255, 100, 200, 200));

    // cria um vetor de nome v
    sf::Vector2f v(50.f, 100.f); 
    // altera o valor x do vetor v
    // v.x = 10; 

    // fortmato de um retangulo ( alutura / largura )
    sf::RectangleShape rect(v);
    rect.setPosition(sf::Vector2f(400.f, 200.f));

    // eventos
    sf::Event event;

    while (window.isOpen()){
        
        while(window.pollEvent(event)){ // verificar se existe algum evento pendente
            if(event.type == sf::Event::Closed){ // se o evento de clicar em fechar a janela for verdadeiro
                window.close();
            }
        }


        // Update

            // Desenha o "shape" novamente N a + no eixo X e M a + no eixo Y
        shape.move(1.f, 0.f);

        // Draw
        

        // limpa janela
        window.clear();

        // draw everthing

        // Desenha a "figura" na tela, por definição na posição 0,0 que é no canto superior esquerdo
        window.draw(shape);
        window.draw(rect);
        window.draw(triangle);
        window.draw(line, 2, sf::Lines);
        window.draw(convex);

        // continua mostrando a janela
        window.display(); 

        //      std::cout << c << std::endl;
        //      c++;

    }

    return 0;
}


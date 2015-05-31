# g++ -c main.cpp -o main.o
# g++ -c Game.cpp -o Game.o
# g++ -c Ball.cpp -o Ball.o
# g++ -c Court.cpp -o Court.o
# g++ -c Paddle.cpp -o Paddle.o
# g++ -c ScoreDisplay.cpp -o ScoreDisplay.o

g++ -c *.cpp -std=c++11
g++ -o cong *.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
rm ./*.o

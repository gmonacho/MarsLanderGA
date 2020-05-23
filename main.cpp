#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Graphique.h"
#include "Population.h"
#include "Mars.h"
#include "Point.h"
#include "fun_array.h"
#define MAP_X 7000
#define MAP_Y 3000
#define WIN_X 1000
#define WIN_Y 600
#define POP	  300
#define GENES 200

void drawPopulation(Graphique& winSdl, Point<double>** currPop)
{
	int x1;
	int y1;
	int x2;
	int y2;

	winSdl.setDrawColor(100, 100, 150, 255);
	double	ratioX = WIN_X / (double)MAP_X;
	double	ratioY = WIN_Y / (double)MAP_Y;
	int i = 0;
	for (int i = 0; i < POP; i++)
	{
		for (int j = 0; j < GENES; j++)
		{
			if (currPop[i][j].getX() == 0)
				break;
			if (j % 2 == 0)
			{
				x1 = currPop[i][j].getX() * ratioX;
				y1 = WIN_Y - currPop[i][j].getY() * ratioY;
			}
			else
			{
				x2 = currPop[i][j].getX() * ratioX;
				y2 = WIN_Y - currPop[i][j].getY() * ratioY;
			}
			if (j != 0)
				winSdl.drawLine(x1, y1, x2, y2);
		}
	}
}

void drawMars(Graphique& winSdl, const std::vector<Point<double>>& surface)
{
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;


	winSdl.setDrawColor(200, 100, 100, 255);
	double	ratioX = WIN_X / (double)MAP_X;
	double	ratioY = WIN_Y / (double)MAP_Y;
	for (int i = 0; i < surface.size(); i++)
	{
		if (i % 2 == 0)
		{
			x1 = surface[i].getX() * ratioX;
			y1 = WIN_Y - surface[i].getY() * ratioY;
		}
		else
		{
			x2 = surface[i].getX() * ratioX;
			y2 = WIN_Y - surface[i].getY() * ratioY;
		}
		if (i != 0)
			winSdl.drawLine(x1, y1, x2, y2);
	}
}

int main(int ac, char** av)
{
	std::vector<double>		notes;
	for (int j = 0; j < 100; j++)
	{
		srand(time(nullptr));
		Graphique				winSdl = Graphique(WIN_X, WIN_Y);
		SDL_Event				event;
		// easy on right
		//Ship					startShip(Point<double>(2500, 2700), Vec<double>(0, 0), 550, 0, 0);
		// 2
		//Ship					startShip(Point<double>(6500, 2800), Vec<double>(-100, 0), 0, 90, 600);
		// 3
		Ship					startShip = Ship(Point<double>(6500, 2800), Vec<double>(-90, 0), 750, 90, 0);
		//4
		//Ship					startShip = Ship(Point<double>(500, 2700), Vec<double>(100, 0), 800, -90, 0);
		//t_ship					ship = t_ship{ 500, 2700, 100, 0, 0, -90, 800 };
		//t_ship					ship = t_ship{ 6500, 2700, -50, 0, 0, 90, 1000 };
		Population				pop = Population(startShip);
		Mars					mars = Mars();
		bool					loop = true;
		int						i = 0;
		Point<double>** currPop;

		currPop = reinterpret_cast<Point<double>**>(malloc(sizeof(Point<double>*) * POP));
		for (int i = 0; i < POP; i++)
		{
			currPop[i] = reinterpret_cast<Point<double>*>(malloc(sizeof(Point<double>) * GENES));
			for (int j = 0; j < GENES; j++)
				currPop[i][j].setX(0);
		}
		//currPop = NULL;
		while (loop && !pop.solutionFound())
		{
			winSdl.clear(30, 30, 30, 255);
			pop.nextGeneration(mars, currPop);
			//pop.nextGeneration(mars, nullptr);
			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				break;
			//std::cerr << pop.getAverageVx() << " " << pop.getAverageVy() << " " <<  pop.getAverageRotation() << " " << pop.getAverageMark() <<  std::endl;
			drawPopulation(winSdl, currPop);
			drawMars(winSdl, mars.getSurface());
			winSdl.present();
			i++;
			//std::cerr << "i = " << i << std::endl;
			//while (1)
			//{
			//	SDL_PollEvent(&event);
			//	if (event.type == SDL_KEYDOWN)
			//		if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			//			break;
			//}
			//SDL_Delay(100);
		}
		if (event.type == SDL_QUIT)
			break;
		notes.push_back(i);
	}
	std::cerr << "Average = " << arrayAverage(notes.data(), notes.size()) <<
		" Max = " << *std::max_element(notes.begin(), notes.end()) <<
		" Min = " << *std::min_element(notes.begin(), notes.end()) <<
		" Size = " << notes.size() << std::endl;
	return (0);
}

//
//int main()
//{
//	srand(time(nullptr));
//	Chrono 				chrono;
//	Mars				mars = Mars(-3.711);
//	GeneticPopulation 	pop = GeneticPopulation();
//	t_ship				ship;
//	t_ship				realShip;
//	int					turn = 0;
//
//	ship.power = 0;
//	while (1)
//	{
//		if (turn == 0)
//		{
//			cin >> ship.x >> ship.y >> ship.vx >> ship.vy >> ship.fuel >> ship.rotate >> ship.power; cin.ignore();
//			printShip(ship);
//			pop.setStartShip(ship);
//			pop.runAlgo(chrono, mars);
//			cerr << "first turn  time = " << chrono << endl;
//			printShip(pop.getBestShip());
//		}
//		else
//		{
//			cin >> realShip.x >> realShip.y >> realShip.vx >> realShip.vy >> realShip.fuel >> realShip.rotate >> realShip.power; cin.ignore();
//			printShip(realShip);
//		}
//		applyGene(&ship, pop.getBestGene(turn));
//		printShipAction(ship);
//		turn++;
//	}
//}

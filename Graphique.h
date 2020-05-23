#ifndef GRAPHIQUE_H
# define GRAPHIQUE_H
# include <SDL.h>

#pragma once
class Graphique
{
private:
    SDL_Window* win_ptr;
    SDL_Renderer* rend_ptr;

public:
    Graphique(int wx, int wy);

    ~Graphique();

    Graphique& drawLine(int x1, int y1, int x2, int y2);

    Graphique& clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    Graphique& present();

    Graphique& setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};

#endif
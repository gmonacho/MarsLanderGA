#include "Graphique.h"


Graphique::Graphique(int wx, int wy)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(wx, wy, SDL_WINDOW_SHOWN, &this->win_ptr, &this->rend_ptr);
}

Graphique::~Graphique()
{
    if (this->rend_ptr)
        SDL_DestroyRenderer(this->rend_ptr);
    if (this->win_ptr)
        SDL_DestroyWindow(this->win_ptr);
    SDL_Quit();
}

Graphique& Graphique::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(this->rend_ptr, x1, y1, x2, y2);
    return (*this);
}

Graphique& Graphique::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(this->rend_ptr, r, g, b, a);
    SDL_RenderClear(this->rend_ptr);
    return (*this);
}

Graphique& Graphique::present()
{
    SDL_RenderPresent(this->rend_ptr);
    return (*this);
}

Graphique& Graphique::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(this->rend_ptr, r, g, b, a);
    return (*this);
}
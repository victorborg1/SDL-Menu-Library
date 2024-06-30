#include "MenuItem.h"
#include <iostream>

MenuItem::MenuItem(SDL_Renderer *renderer, const std::string &fontFilePath, int fontSize, SDL_Color color, std::string label)
{
    TTF_Init();
    m_renderer = renderer;
    m_font = TTF_OpenFont(fontFilePath.c_str(), fontSize);
    m_label = label;
    m_textColor = color;
    m_textRect = {0, 0, 0, 0};
    m_borderRect = {0, 0, 0, 0};
    m_hover = false;
}

MenuItem::~MenuItem()
{
    TTF_CloseFont(m_font);
}

void MenuItem::render(int x, int y, int width, int height, SDL_Color menuBackground, SDL_Color hoverBackground, uint8_t opacity)
{
}

void MenuItem::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_MOUSEMOTION)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= m_borderRect.x && x <= m_borderRect.x + m_borderRect.w && y >= m_borderRect.y && y <= m_borderRect.y + m_borderRect.h)
        {
            m_hover = true;
        }
        else
        {
            m_hover = false;
        }
    }
}

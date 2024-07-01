#include "ButtonMenuItem.h"
#include <iostream>

ButtonMenuItem::ButtonMenuItem(SDL_Renderer *renderer, const std::string &fontFilePath, int fontSize, SDL_Color color, std::string label) : MenuItem(renderer, fontFilePath, fontSize, color, label)
{
    m_clicked = false;
    m_clickedTracker = true;
}

ButtonMenuItem::~ButtonMenuItem()
{
}

void ButtonMenuItem::render(int x, int y, int width, int height, SDL_Color menuBackground, SDL_Color hoverBackground, uint8_t opacity)
{
    m_hover ? SDL_SetRenderDrawColor(m_renderer, hoverBackground.r, hoverBackground.g, hoverBackground.b, opacity) : SDL_SetRenderDrawColor(m_renderer, menuBackground.r, menuBackground.g, menuBackground.b, opacity);
    m_borderRect = {x, y, width, height};

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(m_renderer, &m_borderRect);

    SDL_Surface *textSurface = TTF_RenderText_Blended(m_font, m_label.c_str(), m_textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    m_textRect = {x + (width / 2) - (textSurface->w / 2), y + (height / 2) - (textSurface->h / 2), textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &m_textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    if (m_clicked && m_clickedTracker)
    {
        drawTrackerRect(x, y);
    }
}

// Behövde göra föräldraklassens privata m_hover variabel till protected (alla privata variabler)
void ButtonMenuItem::handleEvent(SDL_Event &e)
{
    MenuItem::handleEvent(e);
    if (e.type == SDL_MOUSEBUTTONDOWN && m_hover)
    {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            m_clicked = !m_clicked;
            std::cout << m_clicked << '\n';
        }
    }
}

void ButtonMenuItem::setClickedStatus(bool status)
{
    m_clicked = status;
}

void ButtonMenuItem::setClickedTracker(bool status)
{
    m_clickedTracker = status;
}

bool ButtonMenuItem::isClicked()
{
    return m_clicked;
}

void ButtonMenuItem::drawTrackerRect(int x, int y)
{
    m_clickedTrackerRect = {x + 10, y + 10, 10, 10};
    SDL_SetRenderDrawColor(m_renderer, m_textColor.r, m_textColor.g, m_textColor.b, m_textColor.a);
    SDL_RenderDrawRect(m_renderer, &m_clickedTrackerRect);
}
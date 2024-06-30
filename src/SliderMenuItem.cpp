#include "SliderMenuItem.h"
#include <iostream>

SliderMenuItem::SliderMenuItem(SDL_Renderer *renderer, const std::string &fontFilePath, int fontSize, SDL_Color color, std::string label) : MenuItem(renderer, fontFilePath, fontSize, color, label), m_dragging(false), m_min(0), m_max(100), m_value(50)
{
    m_knobRect.w = 10;
    m_knobRect.h = 20;
}

SliderMenuItem::~SliderMenuItem()
{
}

void SliderMenuItem::render(int x, int y, int width, int height, SDL_Color menuBackground, SDL_Color hoverBackground, uint8_t opacity)
{
    SDL_SetRenderDrawColor(m_renderer, menuBackground.r, menuBackground.g, menuBackground.b, opacity);
    m_borderRect = {x, y, width, height};

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(m_renderer, &m_borderRect);

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(m_renderer, hoverBackground.r, hoverBackground.g, hoverBackground.b, hoverBackground.a);

    m_sliderRect = {x + width / 4, y + height / 2 - 2, width / 2, 4};
    SDL_RenderFillRect(m_renderer, &m_sliderRect);

    SDL_SetRenderDrawColor(m_renderer, m_textColor.r, m_textColor.g, m_textColor.b, m_textColor.a);
    int knobX = x + width / 4 + ((m_value - m_min) * (width / 2 - m_knobRect.w)) / (m_max - m_min);
    m_knobRect.x = knobX;
    m_knobRect.y = y + height / 2 - m_knobRect.h / 2;

    SDL_RenderDrawRect(m_renderer, &m_knobRect);
}

void SliderMenuItem::handleEvent(SDL_Event &e)
{
    MenuItem::handleEvent(e);

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX = e.button.x;
        int mouseY = e.button.y;
        if (mouseX >= m_knobRect.x && mouseX <= m_knobRect.x + m_knobRect.w &&
            mouseY >= m_knobRect.y && mouseY <= m_knobRect.y + m_knobRect.h)
        {
            m_dragging = true;
        }
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
        m_dragging = false;
    }
    else if (e.type == SDL_MOUSEMOTION)
    {
        if (m_dragging)
        {
            int mouseX = e.motion.x;
            updateSliderPosition(mouseX, m_sliderRect.y);
        }
    }
}

void SliderMenuItem::updateSliderPosition(int x, int y)
{
    int sliderStartX = m_sliderRect.x;
    int sliderEndX = m_sliderRect.x + m_sliderRect.w;
    if (x < sliderStartX)
        x = sliderStartX;
    if (x > sliderEndX)
        x = sliderEndX;

    m_value = m_min + (x - sliderStartX) * (m_max - m_min) / (sliderEndX - sliderStartX);
    std::cout << m_value << '\n';
}
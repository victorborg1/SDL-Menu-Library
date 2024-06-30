#ifndef __MENULIBRARY_INCLUDE_SLIDERMENUITEM_H_
#define __MENULIBRARY_INCLUDE_SLIDERMENUITEM_H_

#include "MenuItem.h"

class SliderMenuItem : public MenuItem
{
public:
    SliderMenuItem(SDL_Renderer *renderer, const std::string &fontFilePath, int fontSize, SDL_Color color, std::string label);
    ~SliderMenuItem();
    void render(int x, int y, int width, int height, SDL_Color menuBackground, SDL_Color hoverBackground, uint8_t opacity) override;
    void handleEvent(SDL_Event &e) override;

private:
    int m_min, m_max, m_value;
    SDL_Rect m_sliderRect;
    SDL_Rect m_knobRect;
    bool m_dragging;
    void updateSliderPosition(int x, int y);
};

#endif // __MENULIBRARY_INCLUDE_SLIDERMENUITEM_H_
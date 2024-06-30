#ifndef __MENULIBRARY_INCLUDE_MENUITEM_H_
#define __MENULIBRARY_INCLUDE_MENUITEM_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class MenuItem
{
public:
    MenuItem(SDL_Renderer *renderer, const std::string &fontFilePath, int fontSize, SDL_Color color, std::string label);
    virtual ~MenuItem();
    virtual void render(int x, int y, int width, int height, SDL_Color menuBackground, SDL_Color toggleBackground, uint8_t opacity);
    virtual void handleEvent(SDL_Event &e);

    virtual bool isClicked() { return false; }
    virtual void setClickedStatus(bool status) {}

    virtual int getSliderValue() { return 0; }

protected:
    int m_itemWidth, m_itemHeight;
    bool m_hover;
    std::string m_label;
    SDL_Rect m_textRect;
    SDL_Rect m_borderRect;
    TTF_Font *m_font;
    SDL_Color m_textColor;
    SDL_Renderer *m_renderer;
};

#endif // __MENULIBRARY_INCLUDE_MENUITEM_H_
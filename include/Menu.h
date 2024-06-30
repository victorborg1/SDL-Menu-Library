#ifndef __MENULIBRARY_INCLUDE_MENU_H_
#define __MENULIBRARY_INCLUDE_MENU_H_

#include <vector>
#include <SDL.h>
#include "MenuItem.h"

class Menu
{
public:
    enum class Type
    {
        RIGHT,
        LEFT,
        TOP,
        BOTTOM
    };

    Menu(SDL_Renderer *renderer, Type menuType, const int windowWidth, const int windowHeight, const int margin, SDL_Keycode toggleKey, SDL_Color windowBackground, SDL_Color menuBackground, SDL_Color hoverBackground, SDL_Color borderColor, uint8_t opacity, const bool visibleBorder);
    ~Menu();
    void addItem(MenuItem *item);
    void removeItem(MenuItem *item);
    void render();
    void handleEvent(SDL_Event &e);
    MenuItem &getMenuItem(int i);

private:
    Type m_type;
    int m_x, m_y;
    int m_windowWidth, m_windowHeight;
    int m_width, m_height;
    int m_numberOfItems;
    int m_margin;
    SDL_Keycode m_toggleKey;
    int m_toggleSpeed;
    bool m_visible;
    bool m_vertical;
    std::vector<MenuItem *> m_items;
    SDL_Rect m_menuContainer;
    SDL_Renderer *m_renderer;
    SDL_Color m_windowBackground;
    SDL_Color m_menuBackground;
    SDL_Color m_hoverBackground;
    SDL_Color m_borderColor;
    uint8_t m_opacity;
    bool m_visibleBorder;
    void renderMenuContainer();
    void renderMenuSeparators();
    void loadAnimation();
    void unloadAnimation();
    void animation(int &coordinate, int target, bool xAxis, bool positiveToggleSpeed);
    void handleToggleEvent(SDL_Event &e);
    void setLocation();
};

#endif // __MENULIBRARY_INCLUDE_MENU_H_
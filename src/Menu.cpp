#define SDL_MAIN_HANDLED

#include <SDL.h>
#include "ButtonMenuItem.h"
#include "SliderMenuItem.h"
#include "Menu.h"
#include <iostream>

Menu::Menu(SDL_Renderer *renderer, Type type, const int windowWidth, const int windowHeight, const int margin, SDL_Keycode toggleKey, SDL_Color windowBackground, SDL_Color menuBackground, SDL_Color hoverBackground, SDL_Color borderColor, uint8_t opacity, const bool visibleBorder)
{
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_type = type;
    m_renderer = renderer;
    m_numberOfItems = 0;
    m_visible = false;
    m_margin = margin;
    m_toggleKey = toggleKey;
    m_toggleSpeed = 15;
    setLocation();
    m_menuContainer = {m_x, m_y, m_width, m_height};
    m_windowBackground = windowBackground;
    m_menuBackground = menuBackground;
    m_hoverBackground = hoverBackground;
    m_borderColor = borderColor;
    m_opacity = opacity;
    m_visibleBorder = visibleBorder;
}

Menu::~Menu()
{
    for (MenuItem *item : m_items)
    {
        delete item;
    }
}

void Menu::addItem(MenuItem *item)
{
    m_items.push_back(item);
    m_numberOfItems++;
}

void Menu::removeItem(MenuItem *item)
{
}

void Menu::setLocation()
{
    switch (m_type)
    {
    case Type::LEFT:
        m_width = m_windowWidth / 12;
        m_height = m_windowHeight - (2 * m_margin);
        // m_x = m_margin
        m_x = -m_width;
        m_y = m_margin;
        m_vertical = true;
        break;

    case Type::RIGHT:
        m_width = m_windowWidth / 12;
        m_height = m_windowHeight - (2 * m_margin);
        // m_x = m_windowWidth - (m_width + m_margin);
        m_x = m_windowWidth;
        m_y = m_margin;
        m_vertical = true;
        break;

    case Type::TOP:
        m_width = m_windowWidth - (2 * m_margin);
        m_height = m_windowHeight / 20;
        m_x = m_margin;
        // m_y = m_margin;
        m_y = -m_height;
        m_vertical = false;
        break;

    case Type::BOTTOM:
        m_width = m_windowWidth - (2 * m_margin);
        m_height = m_windowHeight / 20;
        m_x = m_margin;
        // m_y = m_windowHeight - (m_height + m_margin);
        m_y = m_windowHeight;
        m_vertical = false;
        break;
    }
}

void Menu::render()
{

    if (m_numberOfItems > 0)
    {
        if (m_vertical)
        {
            int itemHeight = m_height / m_numberOfItems;
            int currentY = m_y;

            for (MenuItem *item : m_items)
            {
                item->render(m_x, currentY, m_width, itemHeight, m_menuBackground, m_hoverBackground, m_opacity);
                currentY += itemHeight;
            }
        }
        else
        {
            int itemWidth = m_width / m_numberOfItems;
            int currentX = m_x;

            for (MenuItem *item : m_items)
            {
                item->render(currentX, m_y, itemWidth, m_height, m_menuBackground, m_hoverBackground, m_opacity);
                currentX += itemWidth;
            }
        }
    }
    if (m_visibleBorder)
        renderMenuContainer();
}

void Menu::handleEvent(SDL_Event &e)
{
    for (MenuItem *item : m_items)
    {
        item->handleEvent(e);
    }

    handleToggleEvent(e);
}

void Menu::animation(int &coordinate, int target, bool xAxis, bool positiveToggleSpeed)
{
    int &menuCoord = xAxis ? m_menuContainer.x : m_menuContainer.y;

    SDL_Rect clearRect;
    clearRect = {m_menuContainer.x, m_menuContainer.y, m_menuContainer.w, m_menuContainer.h};

    if (positiveToggleSpeed)
    {
        while (coordinate < target)
        {
            coordinate += m_toggleSpeed;
            if (coordinate > target)
            {
                coordinate = target;
            }
            menuCoord = coordinate;

            std::cout << coordinate << " ";

            SDL_SetRenderDrawColor(m_renderer, m_windowBackground.r, m_windowBackground.g, m_windowBackground.b, m_windowBackground.a);
            SDL_RenderFillRect(m_renderer, &clearRect);
            render();
            SDL_RenderPresent(m_renderer);
        }
    }
    else
    {
        while (coordinate > target)
        {
            coordinate -= m_toggleSpeed;
            if (coordinate < target)
            {
                coordinate = target;
            }
            menuCoord = coordinate;

            std::cout << coordinate << " ";

            SDL_SetRenderDrawColor(m_renderer, m_windowBackground.r, m_windowBackground.g, m_windowBackground.b, m_windowBackground.a);
            SDL_RenderFillRect(m_renderer, &clearRect);
            render();
            SDL_RenderPresent(m_renderer);
        }
    }
}

void Menu::loadAnimation()
{
    switch (m_type)
    {
    case Type::LEFT:
        animation(m_x, m_margin, true, true);
        break;

    case Type::RIGHT:
        animation(m_x, m_windowWidth - (m_width + m_margin), true, false);
        break;

    case Type::TOP:
        animation(m_y, m_margin, false, true);
        break;

    case Type::BOTTOM:
        animation(m_y, m_windowHeight - (m_height + m_margin), false, false);
        break;
    }
}

void Menu::unloadAnimation()
{
    switch (m_type)
    {
    case Type::LEFT:
        animation(m_x, -m_width, true, false);
        break;

    case Type::RIGHT:
        animation(m_x, m_windowWidth, true, true);
        break;

    case Type::TOP:
        animation(m_y, -m_height, false, false);
        break;

    case Type::BOTTOM:
        animation(m_y, m_windowHeight, false, true);
        break;
    }
}

void Menu::renderMenuContainer()
{
    SDL_SetRenderDrawColor(m_renderer, m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a);
    SDL_RenderDrawRect(m_renderer, &m_menuContainer);
}

void Menu::handleToggleEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == m_toggleKey)
    {
        std::cout << '\n';
        m_visible = !m_visible;
        if (m_visible)
        {
            loadAnimation();
        }
        else
        {
            unloadAnimation();
        }
    }
}

MenuItem &Menu::getMenuItem(int i)
{
    return *m_items[i];
    // derefrencing, vi har en lista av pekare och vi måste då returnera värdet (det faktiska objektet) så att vi kan anväda dess funktioner och sånt
}

// ------------------------------------------------------------------------------------------------------- //

int main()
{

    const int WINDOW_WIDTH = 1600;
    const int WINDOW_HEIGHT = 950;
    const std::string FONTPATH = "src/../fonts/Roboto-Light.ttf";
    const int MARGIN = 10;
    const int FONTSIZE = 24;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    const SDL_Color textColor = {0, 0, 0, 255};

    SDL_Color bg = {200, 200, 200, 255};
    const SDL_Color hoverColor = {120, 120, 120, 255};
    const SDL_Color menuBg = {210, 210, 210, 255};

    const SDL_Color borderColor = {0, 0, 0, 255};
    const uint8_t opacity = 255;
    const bool visibleBorder = true;

    bool running = true;

    Menu menu1(renderer, Menu::Type::TOP, WINDOW_WIDTH, WINDOW_HEIGHT, MARGIN, SDLK_1, bg, menuBg, hoverColor, borderColor, opacity, visibleBorder);
    menu1.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Button"));
    menu1.addItem(new SliderMenuItem(renderer, FONTPATH, 0, textColor, "SliderValue"));

    Menu menu2(renderer, Menu::Type::BOTTOM, WINDOW_WIDTH, WINDOW_HEIGHT, MARGIN, SDLK_2, bg, menuBg, hoverColor, borderColor, opacity, visibleBorder);
    menu2.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Gurka"));
    menu2.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "About"));
    menu2.addItem(new SliderMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Gurka"));
    menu2.addItem(new SliderMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "About"));

    menu2.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "About"));

    menu2.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Gurka"));
    menu2.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "About"));

    Menu menu3(renderer, Menu::Type::RIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, MARGIN, SDLK_3, bg, menuBg, hoverColor, borderColor, opacity, visibleBorder);
    menu3.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Hem"));

    Menu menu4(renderer, Menu::Type::LEFT, WINDOW_WIDTH * 2, WINDOW_HEIGHT / 2, MARGIN, SDLK_4, bg, menuBg, hoverColor, borderColor, opacity, visibleBorder);
    menu4.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Hem"));
    menu4.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Hem"));
    menu4.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Hem"));
    menu4.addItem(new ButtonMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Hem"));
    menu4.addItem(new SliderMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Gurka"));
    menu4.addItem(new SliderMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "About"));
    menu4.addItem(new SliderMenuItem(renderer, FONTPATH, FONTSIZE, textColor, "Gurka"));

    // för att stänga av tracker, dvs att menuföremålet visar att den är iklickad:
    // menu4.getMenuItem(0).setClickedTracker(false);

    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            menu1.handleEvent(event);
            menu2.handleEvent(event);
            menu3.handleEvent(event);
            menu4.handleEvent(event);
        }

        SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
        SDL_RenderClear(renderer);
        menu1.render();
        menu2.render();
        menu3.render();
        menu4.render();
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

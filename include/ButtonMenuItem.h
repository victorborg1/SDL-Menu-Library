#ifndef __MENULIBRARY_INCLUDE_BUTTONMENUITEM_H_
#define __MENULIBRARY_INCLUDE_BUTTONMENUITEM_H_

#include "MenuItem.h"

class ButtonMenuItem : public MenuItem
{
public:
    ButtonMenuItem(SDL_Renderer *renderer, const std::string &fontFilePath, int fontSize, SDL_Color color, std::string label);
    ~ButtonMenuItem();
    void render(int x, int y, int width, int height, SDL_Color menuBackground, SDL_Color hoverBackground, uint8_t opacity) override;
    void handleEvent(SDL_Event &e) override;
    bool isClicked() override;
    void setClickedStatus(bool status) override;
    void setClickedTracker(bool status) override;

private:
    bool m_clicked;
    bool m_clickedTracker;
    SDL_Rect m_clickedTrackerRect;
    void drawTrackerRect(int x, int y);
};

#endif // __MENULIBRARY_INCLUDE_BUTTONMENUITEM_H_
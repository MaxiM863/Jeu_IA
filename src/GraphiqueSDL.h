#include<vector>
#include<math.h>

#include "SDL3/SDL.h"

#include "TreeNode.h"

class GraphiqueSDL{

public:

    static bool initialize(int width, int height) {   
        
        _width = width;
        _height = height;

        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow(
            "Prototype IA Maxim",
            50 * width,
            50 * height,
            SDL_WINDOW_OPENGL
        );

        if (window == NULL) {
            
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());

            return false;
        }

        renderer = SDL_CreateRenderer(window, NULL);

        if (renderer == NULL)
        {
            SDL_DestroyWindow(window);
            SDL_Quit();

            return false;
        }

        return true;
    }

    static bool afficherUnFrame(Position& clickedPos) 
    {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {

            switch(e.type){
                case SDL_EVENT_QUIT:
                    return false;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    clickedPos = Position((int)e.button.x / 50, (int)e.button.y / 50);           
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //**************************************************************

        drawBoard(renderer);

        //**************************************************************

        return true;
    }

    static void terminerFrame()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //**************************************************************

        drawBoard(renderer);

        //**************************************************************
        
        SDL_RenderPresent(renderer);
    }

    static void afficherFin(bool isBotWin)
    {
        if(isBotWin)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            drawCircle(_width/2*50, _height/2*50, 150, renderer);
            SDL_RenderPresent(renderer);

            SDL_Delay(3500);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            drawCircle(_width/2*50, _height/2*50, 150, renderer);
            SDL_RenderPresent(renderer);

            SDL_Delay(3500);
        }
    }

    static void putBotData(Position bot)
    {

        botPlayed.push_back(bot);
    }

    static void putPlayerData(Position player)
    {
        joueurPlayed.push_back(player);
    }

    private:

        static void drawCircle(int xx, int yy, int radius, SDL_Renderer* renderer) {
            
            for(int i = 0; i < 360; i ++) {
        
                int xc = xx;
                int yc = yy;
        
                float r = i/360.0f*2*3.14159f;                                 
                int x = xc + (int)(radius * cos(r));
                int y = yc + (int)(radius * sin(r));
                SDL_RenderPoint(renderer, (float)x, (float)y);
            }
        }

        static void drawBoard(SDL_Renderer *renderer)
        {            
            for(int i = 0;  i < _width; i++) {

                for(int j = 0; j < _height; j++) {

                    SDL_FRect rect;
                    rect.h = 50;
                    rect.w = 50;
                    rect.x = (float)(j * 50);
                    rect.y = (float)(i * 50);

                    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                    SDL_RenderRect(renderer, &rect);

                    bool testBot = false;

                    for(int k = 0; k < botPlayed.size(); k++)
                    {
                        if(botPlayed.at(k).xPos == i && botPlayed.at(k).yPos == j)
                        {
                            testBot = true;
                        }
                    }

                    if(testBot) {

                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        drawCircle(i*50+25, j*50+25, 15, renderer);
                    }
                    
                    bool testPly = false;

                    for(int k = 0; k < joueurPlayed.size(); k++)
                    {
                        if(joueurPlayed.at(k).xPos == i && joueurPlayed.at(k).yPos == j)
                        {
                            testPly = true;
                        }
                    }

                    if(testPly)
                    {

                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        drawCircle(i*50+25, j*50+25, 15, renderer);
                    }
                }
            }
        }

    private:

        static inline SDL_Window *window;
        static inline SDL_Renderer *renderer;

        static inline std::vector<Position> botPlayed;
        static inline std::vector<Position> joueurPlayed;

        static inline int _width;
        static inline int _height;
};
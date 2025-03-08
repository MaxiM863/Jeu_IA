#include<vector>

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

    static bool afficherUnFrame() 
    {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {

            switch(e.type){
                case SDL_EVENT_QUIT:
                    return false;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                                        
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //**************************************************************

        drawBoard(renderer);

        //**************************************************************
        
        SDL_RenderPresent(renderer);

        return true;
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
                int x = xc + radius * cos(r);
                int y = yc + radius * sin(r);
                SDL_RenderPoint(renderer, x, y);
            }
        }

        static void drawBoard(SDL_Renderer *renderer)
        {            
            for(int i = 0;  i < 6; i++) {

                for(int j = 0; j < 6; j++) {

                    SDL_FRect rect;
                    rect.h = 50;
                    rect.w = 50;
                    rect.x = j * 50;
                    rect.y = i * 50;

                    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                    SDL_RenderRect(renderer, &rect);

                    bool testBot = false;

                    for(int i = 0; i < botPlayed.size(); i++)
                    {
                        if(botPlayed.at(i).xPos == i && botPlayed.at(i).yPos == j)
                        {
                            testBot = true;
                        }
                    }

                    if(testBot) {

                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        drawCircle(i*50+25, j*50+25, 15, renderer);
                    }
                    
                    bool testPly = false;

                    for(int i = 0; i < joueurPlayed.size(); i++)
                    {
                        if(joueurPlayed.at(i).xPos == i && joueurPlayed.at(i).yPos == j)
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

        static std::vector<Position> botPlayed;
        static std::vector<Position> joueurPlayed;

        static int _width;
        static int _height;
};
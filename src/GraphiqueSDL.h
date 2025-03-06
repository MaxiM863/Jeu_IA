#include<vector>

#include "SDL3/SDL.h"

#include "TreeNode.h"

class GraphiqueSDL{

public:

    static bool initialize(int width, int height) {        

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

        static inline SDL_Window *window;
        static inline SDL_Renderer *renderer;

        static std::vector<Position> botPlayed;
        static std::vector<Position> joueurPlayed;
};
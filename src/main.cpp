#include"SDL3/SDL.h"

int main(){

    SDL_Window *window;                    // Declare a pointer
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);

    bool done = false;

    window = SDL_CreateWindow(
        "An SDL3 window",                  // window title
        300,                               // width, in pixels
        300,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }

    while (!done) {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {

            switch(e.type){
                case SDL_EVENT_QUIT:
                    done = true;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                                        
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}
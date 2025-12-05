#include <SDL2/SDL.h> // you must have your system's path to sdl2 in cmake for this line to work
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0){ // video/windowing subsystem (0 means success)
        /*
        **NOTES**
        SDL_Init(SDL_INIT_VIDEO) is a fn for asking the OS which video backend to use (in this case on Mac--Metal) & Sets up data structs for creating windows, tracking resolution, handling events etc.

        */
        std::cerr << "SDL Init Failed: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow( // ask OS for a screen
        "Josh's Engine Sandbox", // with the title
        SDL_WINDOWPOS_CENTERED, // where, but horizontally
        SDL_WINDOWPOS_CENTERED, // where, but vertically
        800, 600, // window sizing in px
        SDL_WINDOW_SHOWN // flags
    );
    if (!window) { // err handling for window obj
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) { // main loop
        while (SDL_PollEvent(&event)) { // 
            if (event.type == SDL_QUIT) { // (user clicked x)
                running = false;
            }
        }
        // rendering will go here.
        SDL_Delay(16); // ~60fps (16 ms -> 1/60)...every iteration of the parent loop = 1 frame
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "User exited the program.\n";
    return 0;

    
}
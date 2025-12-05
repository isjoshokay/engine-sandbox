#include <SDL2/SDL.h> // you must have your system's path to sdl2 in cmake for this line to work
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0){ // platform layer
        std::cerr << "SDL Init Failed: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow( // ask OS for screen
        "Josh's Engine Sandbox",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) { // main loop
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { // (user clicked x)
                running = false;
            }
        }
        // rendering will go here.
        SDL_Delay(16); // 60fps (16 ms -> )
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "User exited the program.\n";
    return 0;

    
}
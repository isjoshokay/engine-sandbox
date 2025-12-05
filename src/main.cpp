#include <SDL2/SDL.h> // you must have your system's path to sdl2 in makefile for this line to work
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
        SDL_WINDOW_SHOWN // bitwise flag
    );
    if (!window) { // err handling for window obj
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // Create a renderer (added 12/5/25)
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, // (window that was created)
        -1, // "index of the rendering driver???" 
        SDL_RENDERER_ACCELERATED // flag for hardware acceleration (if possible)
    );
    if (!renderer){ // rendering without a renderer is a harmful semi-alliterative phrase
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    } else {
        std::cout << "Renderering the renderation...";
    }

    bool running = true;
    SDL_Event event;

    while (running) { // main loop
        while (SDL_PollEvent(&event)) { // 
            if (event.type == SDL_QUIT) { // (user clicked x or force quit)
                running = false;
            }
        }
        // -- RENDERING STARTS HERE -- 
        // set color (RGBA)
        SDL_SetRenderDrawColor(renderer, 150, 30, 100, 255); 
        SDL_RenderClear(renderer); 

        // draw calls will go here

        SDL_RenderPresent(renderer); // swap buffers: actually shows the frame

        SDL_Delay(16); // ~60fps (16 ms -> 1/60)...every iteration of the parent loop = 1 frame
    }

    // CLEAN UP IN REVERSE ORDER OF CREATION
    SDL_DestroyRenderer(renderer); // this
    SDL_DestroyWindow(window); // depends on this
    SDL_Quit(); // which depends on this
    std::cout << "User exited the program.\n";
    return 0;

    
}
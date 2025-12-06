#include <SDL2/SDL.h> // you must have your system's path to sdl2 in makefile for this line to work
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0){ // video/windowing subsystem (0 means success)
        /*
        SDL_Init(SDL_INIT_VIDEO) is a fn for asking the OS which video backend to use (in this case on Mac--Metal)
        & Sets up data structs for creating windows, tracking resolution, handling events etc.
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
        -1, // tells SDL to use best fitting driver for system (Mac = Metal)
        SDL_RENDERER_ACCELERATED // bitmask flag for hardware acceleration- using the GPU backed APIs
        | SDL_RENDERER_PRESENTVSYNC // Work with the monitor/frame swap (vsync = vertical sync) helps to avoid "tearing" artifacts.
    );
    if (!renderer){ // rendering without a renderer is a harmful semi-alliterative phrase /joking-but-not
        /*
        If none of your drivers support acceleration, SDL_CreateRenderer() will fail.
        */
        std::cerr << "SDL_CreateRenderer failed: \n" << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    } else {
        std::cout << "Renderer successfully initialized.\n";
    }

    bool running = true;
    SDL_Event event;


    // render our first shape...a rectangle!
    float rectX = 100.0f; // top left corner
    float rectY = 100.0f;
    float rectW = 80.0f; // size
    float rectH = 60.0f;

    // velocity in pixels/sec
    float rectVX = 200.0f;
    float rectVY = 140.0f;

    const int windowWidth = 800;
    const int windowHeight = 600;
    // delta time
    Uint32 lastTicks = SDL_GetTicks();
    while (running) { // main loop
        while (SDL_PollEvent(&event)) { // 
            if (event.type == SDL_QUIT) { // (user clicked x or force quit)
                running = false;
                std::cout << "User exited the program.\n";
            }
        }
        // -- RENDERING STARTS HERE -- 
                // --- TIME STEP (delta time) ---
        Uint32 currentTicks = SDL_GetTicks();
        float dt = (currentTicks - lastTicks) / 1000.0f; // ms → seconds
        lastTicks = currentTicks;

        // --- UPDATE RECTANGLE POSITION ---
        rectX += rectVX * dt;
        rectY += rectVY * dt;

        // Bounce off edges
        if (rectX < 0.0f) {
            rectX = 0.0f;
            rectVX *= -1.0f;
        }
        if (rectX + rectW > windowWidth) {
            rectX = windowWidth - rectW;
            rectVX *= -1.0f;
        }

        if (rectY < 0.0f) {
            rectY = 0.0f;
            rectVY *= -1.0f;
        }
        if (rectY + rectH > windowHeight) {
            rectY = windowHeight - rectH;
            rectVY *= -1.0f;
        }
        // set color (RGBA)
        SDL_SetRenderDrawColor(renderer, 150, 30, 100, 255); 
        SDL_RenderClear(renderer); 

        // rectangle color (white)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect rect;
        rect.x = (int)rectX;
        rect.y = (int)rectY;
        rect.w = (int)rectW;
        rect.h = (int)rectH;

        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer); // swap buffers: actually shows the frame

        // SDL_Delay(16); // ~60fps (16 ms -> 1/60)...every iteration of the parent loop = 1 frame (vsync in renderer will naturally cap the frame rate)
    }

    // CLEAN UP IN REVERSE ORDER OF CREATION
    SDL_DestroyRenderer(renderer); // this
    SDL_DestroyWindow(window); // depends on this
    SDL_Quit(); // which depends on this
    
    return 0;

    
}
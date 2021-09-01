#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 1200;

/**
 * Background Model
 */
class Model {
    private:
        string file;
        SDL_Rect target;
        SDL_Texture* texture;

    public:
        Model(string file, int x, int y) : file(file) {
            target.x = x;
            target.y = y;
        }

        const char *getFile() {
            return file.c_str();
        }

        SDL_Rect *getTarget() {
            return &target;
        }

        int *getX() {
            return &target.x;
        }

        void moveRight() {
            target.x += 1;
        }

        void moveLeft() {
            target.x -= 1;
        }

        int *getY() {
            return &target.y;
        }

        void moveUp() {
            target.y -= 1;
        }

        void moveDown() {
            target.y += 1;
        }

        int *getW() {
            return &target.w;
        }

        int *getH() {
            return &target.h;
        }

        SDL_Texture* getTexture() {
            return texture;
        }

        void setTexture(SDL_Texture *texture) {
            this->texture = texture;
        }

        
};

/**
 * Controller for Foreground
 */
class FGController {
    private:
        const Uint8* state;
        const shared_ptr<Model> fg;
    public:
        FGController(shared_ptr<Model> fg) : fg(fg) {
            state = SDL_GetKeyboardState(nullptr); // estado do teclado
        }
        
        void move() {
            SDL_PumpEvents(); // atualiza estado do teclado
            if (state[SDL_SCANCODE_LEFT]) fg->moveLeft();
            if (state[SDL_SCANCODE_RIGHT]) fg->moveRight();
            if (state[SDL_SCANCODE_UP]) fg->moveUp();
            if (state[SDL_SCANCODE_DOWN]) fg->moveDown();
        }
};

/**
 * Renderer
 */
class View {
    private:
        shared_ptr<Model> bg;
        shared_ptr<Model> fg;
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        View(shared_ptr<Model> bg, shared_ptr<Model> fg) : bg(bg), fg(fg) {

            // Criando uma janela
            window = nullptr;
            window = SDL_CreateWindow("Demonstracao do SDL2",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);
            if (window==nullptr) { // Em caso de erro...
                std::cout << SDL_GetError();
                SDL_Quit();
            }

            // Inicializando o renderizador
            renderer = SDL_CreateRenderer(
                window, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer==nullptr) { // Em caso de erro...
                SDL_DestroyWindow(window);
                std::cout << SDL_GetError();
                SDL_Quit();
            }

            bg->setTexture(this->render(bg));
            fg->setTexture(this->render(fg));
        }

        ~View() {
            SDL_DestroyTexture(bg->getTexture());
            SDL_DestroyTexture(fg->getTexture());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

        SDL_Texture* render(shared_ptr<Model> model) {
            SDL_Texture *texture = IMG_LoadTexture(renderer, model->getFile());
            SDL_QueryTexture(texture, nullptr, nullptr, model->getW(), model->getH());
            return texture;
        }

        void draw() {
            // Desenhar a cena
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, bg->getTexture(), nullptr, nullptr);
            SDL_RenderCopy(renderer, fg->getTexture(), nullptr, fg->getTarget());
            SDL_RenderPresent(renderer);

            // Delay para diminuir o framerate
            SDL_Delay(10);
        }
};

int main() {
    // Inicializando o subsistema de video do SDL
    if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
        std::cout << SDL_GetError();
        return 1;
    }

    // MVC
    shared_ptr<Model> bg (new Model("./park.jpeg", 0, 0));
    shared_ptr<Model> fg (new Model("./capi.png", 0, 0));
    shared_ptr<FGController> fg_controller (new FGController(fg));
    shared_ptr<View> view (new View(bg, fg));

    // Error handling

    bool run = true;

    SDL_Event evento; // eventos discretos

    // Main loop
    while(run) {
        fg_controller->move();

        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                run = false;
            }
        }

        view->draw();
    }

    return 0;
}

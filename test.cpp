#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>



int main( int argc, char * args [] )
{
    SDL_Window * window = SDL_CreateWindow("Pong", 0, 0, 920, 480, SDL_WINDOW_OPENGL);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    TTF_Font * font = TTF_OpenFont("roboto.ttf", 48);

    SDL_Surface * textTitle = TTF_RenderText_Solid(font, "PONG GAME!", {255, 255, 255});
    SDL_Texture * textTexture = SDL_CreateTextureFromSurface(renderer, textTitle);

    SDL_Surface * textPressG = TTF_RenderText_Solid(font, "Press G to start..", {255, 255, 255});
    SDL_Texture * textTexture1 = SDL_CreateTextureFromSurface(renderer, textPressG);

    const char * score1 = NULL;
    int intScore1 = 0;
    score1 = (std::to_string(intScore1)).c_str();
    SDL_Surface * textScore1 = TTF_RenderText_Solid(font, score1, {255, 255, 255});
    SDL_Texture * textTexture2 = SDL_CreateTextureFromSurface(renderer, textScore1);




    SDL_Rect textRect = {400, 200, textTitle->w, textTitle->h};
    SDL_FreeSurface(textTitle);
    SDL_Rect textRect1 = {400, 300, textPressG->w, textPressG->h};
    SDL_FreeSurface(textPressG);
    SDL_Rect textRect2 = {100, 240, textScore1->w, textScore1->h};
    SDL_FreeSurface(textScore1);

    //TTF_CloseFont(font);
    
    SDL_Rect paddle1 = { 20, 20, 20, 100};
    SDL_Rect paddle2 = { 880, 20, 20, 100};
    SDL_Rect ball = { 220, 220, 20, 20};


    float v_x = 3.0f, v_y = 3.0f;
    float x = 460.0f, y = 240.0f;
    bool gameStart = false;

    while( true )
    {
        SDL_PumpEvents();

        const Uint8 * keystate = SDL_GetKeyboardState(nullptr);

        if( (keystate[SDL_SCANCODE_LCTRL] || keystate[SDL_SCANCODE_RCTRL] ) == 1
        && ( keystate[SDL_SCANCODE_Q] == 1 ) ) {
            TTF_Quit();
            TTF_CloseFont(font);
            return 0; //QUIT
        }

        if( paddle1.y >= 0)
            paddle1.y += ( keystate[SDL_SCANCODE_S] - keystate[SDL_SCANCODE_W] )* 3;
        else
            paddle1.y = 0;
        if( paddle1.y <= 380)
            paddle1.y += ( keystate[SDL_SCANCODE_S] - keystate[SDL_SCANCODE_W] )* 3;
        else
            paddle1.y = 380;

        if( paddle2.y >= 0)
            paddle2.y += ( keystate[SDL_SCANCODE_DOWN] - keystate[SDL_SCANCODE_UP] )* 3;
        else
            paddle2.y = 0;
        if( paddle2.y <= 380)
            paddle2.y += ( keystate[SDL_SCANCODE_DOWN] - keystate[SDL_SCANCODE_UP] )* 3;
        else
            paddle2.y = 380;

        if ( gameStart == true) {
            x += v_x;
            y += v_y;
        }
        
        ball.x = x;
        ball.y = y;

        if( x < 0 ) { // Kollision mit Bildschirmrand
            x = -x;
            v_x = 3.0f, v_y = 3.0f, x = 460.0f, y = 240.0f;
            intScore1++;
            score1 = (std::to_string(intScore1)).c_str();

            
            
        }
        else if( x > 900 ) {
            x = 1800 -x;
            v_x = 3.0f, v_y = 3.0f, x = 460.0f, y = 240.0f;
        }
        else if( y < 0 ) { 
            y = -y;
            v_y *= -1;
        }
        else if( y > 460 ) {
            y = 920 -y;
            v_y *= -1;
        }

        int diff_x_1 = abs(paddle1.x - ball.x);
        int diff_y_1 = (paddle1.y - ball.y);
        bool col_1 = diff_x_1 < 20 && diff_y_1 > -100 && diff_y_1 < 20;

        int diff_x_2 = abs(paddle2.x - ball.x);
        int diff_y_2 = (paddle2.y - ball.y);
        bool col_2 = diff_x_2 < 20 && diff_y_2 > -100 && diff_y_2 < 20;

        if( col_1 ) {
            if( x < 40 ) {
                x = 41;
            }
            v_x *= -1.1f;
            SDL_SetRenderDrawColor( renderer, 127, 127, 127, 255);
        }
        else if( col_2 ) {
            if( x > 880 ) {
                x = 879;  
            }
            v_x *= -1.1f;
            SDL_SetRenderDrawColor( renderer, 127, 127, 127, 255);
        }
        else        
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);
        if ( gameStart == false) {
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_RenderCopy(renderer, textTexture1, NULL, &textRect1);
            if ( keystate[SDL_SCANCODE_G] == 1 ) {
                gameStart = true;
                SDL_RenderClear(renderer);
            }
        }
        else {
            SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &paddle1);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &paddle2);
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &ball);
             
        }  
        SDL_RenderPresent(renderer); 
    }
}


#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 854
#define SCREEN_HEIGHT 480

int main( int argc, char* args[] )
{
  SDL_Window* window = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  
  SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" );

  window = SDL_CreateWindow(
			    "hello_sdl2",
			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN
			    );
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }
  
  SDL_Renderer *pRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC );
  if( !pRenderer )
  {
     SDL_DestroyWindow( window );
     fprintf( stderr, "Couldn't create renderer: %s\n", SDL_GetError() );
     return 1;
  }

  int texW = -1;
  int texH = -1;
  SDL_Surface *pPix = SDL_LoadBMP( "pic.bmp" );
  SDL_Texture *pTex = 0;
  if( pPix )
  {
     printf( "Texture size: %d, %d\n", pPix->w, pPix->h );
     texW = pPix->w;
     texH = pPix->h;
     pTex = SDL_CreateTextureFromSurface( pRenderer, pPix );
     SDL_FreeSurface( pPix );
  }
  
  int runrun = 1;
  float a = 0.0;
  while( runrun )
  {
     SDL_SetRenderDrawColor( pRenderer, 0xff, 0xff, 0xff, 0xff );
     SDL_RenderClear( pRenderer );

     SDL_Rect dRect;
     int w = texW * ( sin( a * 0.01 ) + 2.0 );
     int h = texH * ( sin( a * 0.01 ) + 2.0 );
     dRect.w = w;
     dRect.h = h;
     dRect.x = ( ( SCREEN_WIDTH - w ) / 2 ) + sin( a * 0.05 ) * 100.0;
     dRect.y = ( ( SCREEN_HEIGHT -  h ) / 2 ) + cos( a * 0.05 ) * 100.0;
     SDL_RenderCopyEx( pRenderer, pTex, 0, &dRect, a, 0, SDL_FLIP_NONE );
     a += 0.75;

     SDL_RenderPresent( pRenderer );

     SDL_Event event;
     while( SDL_PollEvent( &event ) )
     {
        if( event.type == SDL_KEYDOWN )
        {
           if( event.key.keysym.sym == SDLK_ESCAPE )
           {
              SDL_Quit();
              runrun = 0;
           }
        }
     }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}


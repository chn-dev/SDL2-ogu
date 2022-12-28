#include <SDL2/SDL.h>

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "modplay/modplay.h"

#define SCREEN_WIDTH 854
#define SCREEN_HEIGHT 480

#define TICK_INTERVAL    16

static Uint32 next_time;

Uint32 time_left()
{
   Uint32 now = SDL_GetTicks();
   if( next_time <= now )
      return 0;
   else
      return next_time - now;
}

void audio_callback( void *userdata, Uint8 *stream, int len )
{
   MODFILE *mod = (MODFILE *)userdata;

   mod->mixingbuf = (u16*)stream;
   mod->mixingbuflen = len;
   MODFILE_Player( mod );
}


typedef struct
{
   int A;
   int B;
   int X;
   int Y;
   int DPAD_LEFT;
   int DPAD_RIGHT;
   int DPAD_UP;
   int DPAD_DOWN;
   int L;
   int R;
} Buttons;

int main( int argc, char* args[] )
{
   Buttons curButtons;
   Buttons prevButtons;
   
   memset( &curButtons, 0, sizeof( Buttons ) );
   memset( &prevButtons, 0, sizeof( Buttons ) );

   MODFILE mod;

   SDL_Window* pWindow = NULL;

   if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO ) < 0 )
   {
      fprintf( stderr, "could not initialize sdl2: %s\n", SDL_GetError() );
      return( 1 );
   }

   // Open game controller
   printf( "Number of joysticks: %d\n", SDL_NumJoysticks() );
   SDL_GameControllerEventState( SDL_ENABLE );
   
   SDL_GameController *pGameController = 0;
   if( SDL_NumJoysticks() > 0 )
   {
      if( SDL_IsGameController( 0 ) )
      {
         pGameController = SDL_GameControllerOpen( 0 );
         if( !pGameController )
         {
            fprintf( stderr, "Couldn't open game controller\n" );
         }
      }
   }

   pWindow = SDL_CreateWindow(
         "hello_sdl2",
         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         SCREEN_WIDTH, SCREEN_HEIGHT,
         SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN
      );

   if( !pWindow )
   {
      fprintf( stderr, "could not create window: %s\n", SDL_GetError() );
      return( 1 );
   }
  
   SDL_Renderer *pRenderer = SDL_CreateRenderer( pWindow, -1, SDL_RENDERER_PRESENTVSYNC );
   if( !pRenderer )
   {
      SDL_DestroyWindow( pWindow );
      fprintf( stderr, "Couldn't create renderer: %s\n", SDL_GetError() );
      return( 1 );
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

   // Start audio
   MODFILE_Init( &mod );
   if( MODFILE_Load( "nearly_there.mod", &mod ) < 0 )
   {
      fprintf( stderr, "could not load MOD file\n" );
   }

   if( mod.set )
   {
      SDL_AudioSpec spec;
      SDL_AudioSpec obtained;

      spec.freq = 44100;
      spec.format = AUDIO_U16;
      spec.channels = 2;
      spec.samples = 4096;
      spec.callback = audio_callback;
      spec.userdata = &mod;

      if( SDL_OpenAudio( &spec, &obtained) < 0 )
      {
         fprintf( stderr, "Couldn't start audio: %s\n", SDL_GetError() );
         MODFILE_Free( &mod );
      } else
      {
         mod.musicvolume = 64;
         mod.sfxvolume = 64;
         MODFILE_Start( &mod );
         
         MODFILE_SetFormat( &mod, obtained.freq, obtained.channels,
                            obtained.format == AUDIO_S16 || obtained.format == AUDIO_U16 ? 16 : 8,
                            obtained.format == AUDIO_S16 || obtained.format == AUDIO_S8 );
                            
         SDL_PauseAudio( 0 );
      }
   }
  
   int runrun = 1;
   float zoom = 1.0;
   float angle = 0.0;
   int xPos = ( SCREEN_WIDTH - texW ) / 2;
   int yPos = ( SCREEN_HEIGHT - texH ) / 2;
   next_time = SDL_GetTicks() + TICK_INTERVAL;

   while( runrun )
   {
      prevButtons = curButtons;

      SDL_Event event;
      while( SDL_PollEvent( &event ) )
      {
         if( event.type == SDL_QUIT )
         {
            runrun = 0;
         } else
         if( event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP )
         {
            if( event.cbutton.which == SDL_JoystickInstanceID( SDL_GameControllerGetJoystick( pGameController ) ) )
            {
               if( event.cbutton.button == SDL_CONTROLLER_BUTTON_A )
               {
                  curButtons.A = event.cbutton.state == SDL_PRESSED;
               } else
               if( event.cbutton.button == SDL_CONTROLLER_BUTTON_B )
               {
                  curButtons.B = event.cbutton.state == SDL_PRESSED;
               } else
               if( event.cbutton.button == SDL_CONTROLLER_BUTTON_X )
               {
                  curButtons.X = event.cbutton.state == SDL_PRESSED;
               } else
               if( event.cbutton.button == SDL_CONTROLLER_BUTTON_Y )
               {
                  curButtons.Y = event.cbutton.state == SDL_PRESSED;
               } else
               if( event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER )
               {
                  curButtons.L = event.cbutton.state == SDL_PRESSED;
               } else
               if( event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER )
               {
                  curButtons.R = event.cbutton.state == SDL_PRESSED;
               } else
               if( event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP )
               {
                  curButtons.DPAD_UP = event.cbutton.state == SDL_PRESSED;
               } else
               if( event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN )
               {
                  curButtons.DPAD_DOWN = event.cbutton.state == SDL_PRESSED;
               } else
               if( event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT )
               {
                  curButtons.DPAD_LEFT = event.cbutton.state == SDL_PRESSED;
               } else
               if( event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT )
               {
                  curButtons.DPAD_RIGHT = event.cbutton.state == SDL_PRESSED;
               }
            }
         }
      }

      if( curButtons.A )
      {
         zoom -= 0.01;
      }

      if( curButtons.B )
      {
         zoom += 0.01;
      }
         
      if( curButtons.L )
      {
         angle -= 0.5;
      }
         
      if( curButtons.R )
      {
         angle += 0.5;
      }
         
      if( curButtons.DPAD_UP )
      {
         yPos -= 1;
      }
         
      if( curButtons.DPAD_DOWN )
      {
         yPos += 1;
      }
         
      if( curButtons.DPAD_LEFT )
      {
         xPos -= 1;
      }
         
      if( curButtons.DPAD_RIGHT )
      {
         xPos += 1;
      }
         
      if( !curButtons.Y && prevButtons.Y )
      {
         runrun = 0;
      }

      SDL_SetRenderDrawColor( pRenderer, 0xff, 0xff, 0xff, 0xff );
      SDL_RenderClear( pRenderer );

      SDL_Rect dRect;
      dRect.w = texW * zoom;
      dRect.h = texH * zoom;
      dRect.x = xPos;
      dRect.y = yPos;
      SDL_RenderCopyEx( pRenderer, pTex, 0, &dRect, angle, 0, SDL_FLIP_NONE );

      SDL_RenderPresent( pRenderer );

      SDL_Delay(time_left());
      next_time += TICK_INTERVAL;
   }
   
   // Stop audio
   if( mod.set )
   {
      SDL_PauseAudio( 1 );
      MODFILE_Stop( &mod );
      SDL_CloseAudio();
      MODFILE_Free( &mod );
   }

   // Release game controller
   if( pGameController )
   {
      SDL_GameControllerClose( pGameController );
   }

   SDL_DestroyWindow( pWindow);
   
   SDL_Quit();
  
  return( 0 );
}


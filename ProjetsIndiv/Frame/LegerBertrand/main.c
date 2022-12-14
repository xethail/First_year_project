#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer,
             SDL_Texture *panier,
             SDL_Texture *ciel,
	     SDL_Texture *ballon)
{
  char msg_formated[255];
  int l;

  if (!ok)
    { // Affichage de ce qui ne va pas
      strncpy(msg_formated, msg, 250);
      l = strlen(msg_formated);
      strcpy(msg_formated + l, " : %s\n");

      SDL_Log(msg_formated, SDL_GetError());
    }

  if (renderer != NULL)
    {
      SDL_DestroyRenderer(renderer);
      renderer = NULL;
    }
  if (window != NULL)
    {
      SDL_DestroyWindow(window);
      window = NULL;
    }

  if (panier != NULL)
    {
      SDL_DestroyTexture(panier);
      panier = NULL;
    }

  if (ciel != NULL)
    {
      SDL_DestroyTexture(ciel);
      ciel = NULL;
    }
  if (ballon != NULL)
    {
      SDL_DestroyTexture(ballon);
      ballon = NULL;
    }


  SDL_Quit();

  if (!ok)
    { // On quitte si cela ne va pas
      exit(EXIT_FAILURE);
    }
}





void AffichageObjet(SDL_Renderer *renderer, SDL_Texture *objet, SDL_Rect pos)
{
  SDL_Rect image = {0};
  SDL_QueryTexture(objet, NULL, NULL, &image.w, &image.h);
  SDL_RenderCopy(renderer, objet, &image, &pos);
  
}



void Animation(SDL_Window *window,
	       SDL_Renderer *renderer,
	       SDL_Texture *panier,
	       SDL_Texture *ciel,
	       SDL_Texture *ballon)
{

 
  /* fond */
  SDL_Rect
    source = {0},            // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
    destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
    posPanier = {0};
    

  SDL_GetWindowSize(
		    window, &window_dimensions.w,
		    &window_dimensions.h); // Récupération des dimensions de la fenêtre

  SDL_QueryTexture(ciel, NULL, NULL,
		   &source.w,
		   &source.h); // Récupération des dimensions de l'image

  float zoom = 1.5;                // Facteur de zoom entre l'image source et l'image affichée pour fond
  destination.w = source.w * zoom; // On applique le zoom sur la largeur
  destination.h = source.h * zoom; // On applique le zoom sur la hauteur
  destination.x = -source.w / 2;   // au depart a droite

  /* position Panier */

  posPanier.h = 400;
  posPanier.w = 400;
  posPanier.x = 60*window_dimensions.w/100;
  posPanier.y = window_dimensions.h - posPanier.h + 100; /*+100 car la hauteur du png fais plus
							   que la hauteur du panier en soit*/

 
  /* ballon */

  //découpage du sprite et on les met tous dans un tableau de SDL_Rect pour pouvoir les utilsez dans l'animation

  //int a, b, c ;

  
  SDL_Rect
    planche = {0},    //rectangle de toute la table de sprite
    posBallon = {0};        //rectangle à chaque itération du sprite
  
  SDL_QueryTexture(ballon, NULL, NULL, &planche.w, &planche.h);
  
  int offsetX = planche.w / 4;
  int offsetY = planche.h / 3; //3 lignes et 4 colonnes

  SDL_Rect etats[12];
  
  int indice = 0;
  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 4; j++)
        {
	  etats[indice].w = offsetX;
	  etats[indice].h = offsetY;
	  etats[indice].x = j * offsetX;
	  etats[indice].y = i * offsetY;
	  indice++;
        }
    }

  //position et dimension du ballon
  /*posBallon.y = window_dimensions.h -25;
    posBallon.x = 0;
    posBallon.h = 100;
    posBallon.w = 100;*/

  posBallon.x = 0;
  posBallon.y = window_dimensions.h/2 -25;
  posBallon.h = 100;
  posBallon.w = 100;
  // boucle évènement SDL
  
  SDL_bool program_on = SDL_TRUE;
  SDL_Event event;

  while (program_on)
    {

      while (SDL_PollEvent(&event))
        {
	  switch (event.type)
            {
            case SDL_QUIT:
	      program_on = SDL_FALSE;
	      break;

            default:
	      break;
            }
        }

      
      /*animation*/


      // c = window_dimensions.h -25 ;
      
      int m = 0;
      for(m  = 0 ; m < 12 ; m ++){

       
	SDL_RenderClear(renderer);                                // Effacer l'image précédente
	
	SDL_RenderCopy(renderer, ciel, &source, &destination);    // Préparation de l'affichage

	posBallon.x = posBallon.x + (60*window_dimensions.w/100)/50 ;

	/*
	 *paramètres de la parabole
	 */
	
	/*b = ((window_dimensions.h/2)-window_dimensions.h +25 -
	  800*(36/100)*window_dimensions.w*window_dimensions.w - 800*156*window_dimensions.w - 800*16900 +
	  8*(36/100)*window_dimensions.h*window_dimensions.w*window_dimensions.w
	  +8*156*window_dimensions.h*window_dimensions.w + 8*16900*window_dimensions.h -
	  100*(36/100)*window_dimensions.w*window_dimensions.w -100*156*window_dimensions.w
	  -100*169000)/(-4*((6/10) * (6/10))*window_dimensions.w)/2 - 312 -
	  (4*19000)/(window_dimensions.w*2)+(6/10)*window_dimensions.w +130;
	
	  a = 4 * (100 - (b * window_dimensions.w / 2 ) - window_dimensions.h
	  +25)/(window_dimensions.w * window_dimensions.w);*/
       
    
	/*équation de la parabole*/
	
	/*posBallon.y = -(posBallon.x * posBallon.x) * a + posBallon.x * b + c; */
	
	
	if (posBallon.x < (60*window_dimensions.w/100) + 130 ){
	
	  SDL_RenderCopy(renderer, ballon, &etats[m], &posBallon);        //ballon
	  
	}else {

	  program_on = SDL_FALSE;
	}

	AffichageObjet(renderer, panier, posPanier);              // Affichage du panier
	
	SDL_RenderPresent(renderer);                              // Affichage de la nouvelle image

	SDL_Delay(50);

	
      }
    }
}



int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  SDL_Window *window = NULL;
  SDL_DisplayMode screen;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *panier = NULL;
  SDL_Texture *ciel = NULL;
  SDL_Texture *ballon = NULL;


  /*Allocation sdl*/
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    end_sdl(0, "ERROR SDL INIT", window, renderer, panier, ciel, ballon);

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n",
	 screen.w, screen.h);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("3 POINTS !!!!!!! .... Ah non en fait...",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
			    screen.h * 0.66,
			    SDL_WINDOW_OPENGL);
  if (window == NULL)
    end_sdl(0, "ERROR WINDOW CREATION", window, renderer, panier, ciel, ballon);

  /* Création du renderer */

  renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
    end_sdl(0, "ERROR RENDERER CREATION", window, renderer, panier, ciel, ballon);

  /*Creation image panier*/

  panier = IMG_LoadTexture(renderer, "./img/panier.png");
  if (panier == NULL)
    end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, panier, ciel, ballon);

  /*Creation image ciel*/

  ciel = IMG_LoadTexture(renderer, "./img/ciel.png");
  if (ciel == NULL)
    end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, panier, ciel, ballon);

  /*Creation image ballon*/

  ballon = IMG_LoadTexture(renderer, "./img/ballon.png");
  if (ballon == NULL)
    end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, panier, ciel, ballon);
  
  /*Affichage*/

  Animation(window, renderer, panier, ciel, ballon);

  end_sdl(1, "Normal ending", window, renderer, panier, ciel, ballon);
  return EXIT_SUCCESS;
}

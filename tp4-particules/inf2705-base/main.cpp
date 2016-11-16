// Prénoms, noms et matricule des membres de l'équipe:
// - Vincent Audet (1637998)
// - Alexis Cabana-Loriaux (1688398)

#include <iostream>
#include <stdlib.h>
#include <map>
#include <GL/glew.h>
#include <GL/glut.h>
#include "varglob.h"

struct Particule
{
   GLfloat position[3];          // en unités
   GLfloat vitesse[3];           // en unités/seconde
   GLint tempsDeVieRestant;     // en secondes
   GLubyte couleur[4];           // couleur actuelle de la particule
   bool    estSelectionnee;      // la particule est actuellement sélectionnée
   // (vous pouvez ajouter d'autres éléments)
};
const unsigned int MAXNPARTICULES = 10000;
Particule particules[MAXNPARTICULES]; // tableau de particules
GLubyte couleursOriginalesParticules[MAXNPARTICULES][4]; // tableau pour ravoir les couleurs originales des particules 

unsigned int nparticules = 30;     // nombre de particules utilisées (actuellement affichées)

float gravite = 0.15; // gravité utilisée dans le calcul de la position de la particule

const GLubyte COULMIN =  50; // valeur minimale d'une composante de couleur lorsque la particule (re)naît
const GLubyte COULMAX = 250; // valeur maximale d'une composante de couleur lorsque la particule (re)naît
const GLuint VIE_MAX_SECONDES = 5;
const GLuint VIE_MIN_SECONDES = 0;

const GLfloat GROSSEUR_POINTS = 5.0;

const float positionPuits[3] = { 0, 0.5, 0 }; // position du puits de particules

bool modeSelection = false; // on est en mode sélection
int dernierX=0, dernierY=0;

bool transparenceSelonAge = false; // l'âge de la particule est utilisée pour la rendre transparente

// afficher la boîte
const GLfloat coo[] = { -1, 0,  1,   1, 0,  1,   1, 0, -1,  -1, 0, -1,
                        1, 2,  1,   1, 2, -1,   1, 0, -1,   1, 0,  1,
                       -1, 2,  1,  -1, 2, -1,  -1, 0, -1,  -1, 0,  1,
                        1, 2, -1,  -1, 2, -1,  -1, 0, -1,   1, 0, -1 };
const GLubyte couleur[] = { 255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255,
                           255, 255,   0,  255, 255,   0,  255, 255,   0,  255, 255,   0,
                           255,   0, 255,  255,   0, 255,  255,   0, 255,  255,   0, 255,
                           0, 255, 255,    0, 255, 255,    0, 255, 255,    0, 255, 255 };

// Valeur aléatoire entre 0.0 et 1.0
float myrandom()
{
   return (float) rand() / (float) RAND_MAX;
}

//Cette fonction effectue une reflexion du vecteur vitesse de la particule par rapport à un vecteur
//unitaire passé en paramètre. On change le vecteur vitesse de la particule
void effectuerReflexion(Particule& p, const float x, const float y, const float z)
{
	float dotprod = p.vitesse[0]*x + p.vitesse[1]*y + p.vitesse[2]*z;
	p.vitesse[0] -= 2*dotprod*x;
	p.vitesse[1] -= 2*dotprod*y;
	p.vitesse[2] -= 2*dotprod*z;
}

//Le code n'est pas 'propre', mais c'est un proof of concept
void changerDirectionParticule(Particule& p)
{
	if(p.position[1] >= 2) // on est sorti de la boite
		return;
	if(p.position[1] <= 0) //Tester pour le plan horizontal (en Y)
		effectuerReflexion(p,0,1.0,0);
	if(p.position[0] <= -1) //tester pour le plan vertical en x= -1
		effectuerReflexion(p,1.0,0,0);
	if(p.position[0] >= 1) //tester pour le plan vertical en x= 1
		effectuerReflexion(p,-1.0,0,0);
	if(p.position[2] <= -1) //tester pour le plan vertical en z= -1
		effectuerReflexion(p,0,0,1.0);
	if(p.position[2] >= 1) //tester pour le plan vertical en z= 1
		effectuerReflexion(p,0,0,-1.0);
}

void avancerParticules( const int deltaT )
{
   for (unsigned int i = 0 ; i < nparticules ; i++ )
   {
   	  particules[i].tempsDeVieRestant -= deltaT;
   	  if(particules[i].tempsDeVieRestant < 0)
   	  {
	   	  //Réinitialiser la position
	      particules[i].position[0] = positionPuits[0];
	      particules[i].position[1] = positionPuits[1];
	      particules[i].position[2] = positionPuits[2];
	      //réinitaliser le temps de vie
	      particules[i].tempsDeVieRestant = (GLint) ((VIE_MIN_SECONDES + (VIE_MAX_SECONDES - VIE_MIN_SECONDES)*myrandom()) * 1000);
   	  }

      particules[i].position[0] += particules[i].vitesse[0];
      particules[i].position[1] += particules[i].vitesse[1];
      particules[i].position[2] += particules[i].vitesse[2];

      //la gravité agit sur toutes les particules. gravité*temps = vitesse à retirer de la vitesse initiale 
      particules[i].vitesse[1] -= gravite*(deltaT/1000.0f);

      changerDirectionParticule(particules[i]);
   }
}


int deltaTemps=0;
static void animer( int tempsPrec )
{
   // obtenir le temps depuis le début du programme, en millisecondes
   int tempsCour = glutGet( GLUT_ELAPSED_TIME );
   if ( tempsPrec == 0 ) tempsPrec = tempsCour;

   // temps d'attente en secondes avant le prochain affichage
   const int FPS = 60;  // en "images/seconde"
   const int delai = 1000/FPS;  // en "millisecondes/image" (= 1000 millisecondes/seconde  /  images/seconde)
   if ( enmouvement ) glutTimerFunc( delai, animer, tempsCour );

   deltaTemps = tempsCour - tempsPrec;

   // déplacer les particules
   avancerParticules( deltaTemps );

   // indiquer qu'il faut afficher à nouveau
   glutPostRedisplay();
}

void initialisation()
{
   enmouvement = true;

   // donner la position de la caméra
   theta = 0.0;
   phi = 1.0;
   dist = 5.0;

   // donner la couleur de fond
   glClearColor( 0.0, 0.0, 0.0, 1.0 );

   // activer les etats openGL
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_BLEND );
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // Initialisation des particules
   for ( unsigned int i = 0 ; i < MAXNPARTICULES ; i++ )
   {
      particules[i].position[0] = positionPuits[0];
      particules[i].position[1] = positionPuits[1];
      particules[i].position[2] = positionPuits[2];
      particules[i].vitesse[0] = (myrandom() - 0.5f) / 32 ; // le nb 32 est arbitraire, on verra bien les particules bouger
      particules[i].vitesse[1] = (myrandom() - 0.5f) / 32 ; 
      particules[i].vitesse[2] = (myrandom() - 0.5f) / 32 ;      
      particules[i].couleur[0] = couleursOriginalesParticules[i][0] = (GLubyte) COULMIN + (COULMAX - COULMIN)*myrandom();
      particules[i].couleur[1] = couleursOriginalesParticules[i][1] = (GLubyte) COULMIN + (COULMAX - COULMIN)*myrandom();
      particules[i].couleur[2] = couleursOriginalesParticules[i][2] = (GLubyte) COULMIN + (COULMAX - COULMIN)*myrandom(); 
      particules[i].couleur[3] = couleursOriginalesParticules[i][3] = (GLubyte) 255;

      particules[i].tempsDeVieRestant = (GLint)((VIE_MIN_SECONDES + (VIE_MAX_SECONDES - VIE_MIN_SECONDES)*myrandom()) * 1000); //milliseconds
      particules[i].estSelectionnee = false;


   }

   glewInit();
}

void afficherScene()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluPerspective( 45.0, (GLdouble) g_largeur / (GLdouble) g_hauteur, 0.1, 10.0 );

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();
   gluLookAt( dist*sin(phi)*sin(theta), dist*cos(phi), dist*sin(phi)*cos(theta), 0, 1, 0, 0, 2, 0 );

   glEnableClientState( GL_VERTEX_ARRAY );
   glEnableClientState( GL_COLOR_ARRAY );

   //glEnable(GL_MULTISAMPLE_ARB);
   glEnable( GL_POINT_SMOOTH );
   glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
   glPointSize(GROSSEUR_POINTS);

   //dessiner les plans
   glVertexPointer( 3, GL_FLOAT, 0, coo );
   glColorPointer( 3, GL_UNSIGNED_BYTE, 0, couleur );
   glDrawArrays( GL_QUADS, 0, 16 );
   
   //dessiner les particules
   glVertexPointer(3, GL_FLOAT, sizeof(Particule), particules);
   glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(Particule), particules[0].couleur);
   glDrawArrays( GL_POINTS, 0, nparticules );
   
   //glDisable(GL_MULTISAMPLE_ARB);
   glDisable( GL_POINT_SMOOTH ); 

   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_COLOR_ARRAY );
   glutSwapBuffers();
}

void redimensionnement( GLsizei w, GLsizei h )
{
   g_largeur = w;
   g_hauteur = h;
   glViewport( 0, 0, w, h );
   glutPostRedisplay();
}

void clavier( unsigned char touche, int x, int y )
{
   switch ( touche )
   {
   case '\e': // escape
      glutDestroyWindow( g_feneID );
      exit( 0 );
      break;
   case ' ':
      enmouvement = !enmouvement;
      if ( enmouvement ) animer( 0 );
      glutPostRedisplay();
      break;
   case '[':
      nparticules /= 1.2;
      if ( nparticules < 5 ) nparticules = 5;
      std::cout << " nparticules=" << nparticules << std::endl;
      glutPostRedisplay();
      break;
   case ']':
      nparticules *= 1.2;
      if ( nparticules > MAXNPARTICULES ) nparticules = MAXNPARTICULES;
      std::cout << " nparticules=" << nparticules << std::endl;
      glutPostRedisplay();
      break;
   case 'a':
      gravite += 0.05;
      std::cout << " gravite=" << gravite << std::endl;
      glutPostRedisplay();
      break;
   case 'd':
      gravite -= 0.05;
      if ( gravite < 0.0 ) gravite = 0.0;
      std::cout << " gravite=" << gravite << std::endl;
      glutPostRedisplay();
      break;
   case 'p':
      for ( unsigned int i = 0 ; i < nparticules ; i++ )
      {
         if ( particules[i].estSelectionnee )
         {
            particules[i].tempsDeVieRestant = 0;
            particules[i].position[0] = positionPuits[0];
            particules[i].position[1] = positionPuits[1];
            particules[i].position[2] = positionPuits[2];
            particules[i].couleur[0] = couleursOriginalesParticules[i][0] ;
	        particules[i].couleur[1] = couleursOriginalesParticules[i][1] ;
	        particules[i].couleur[2] = couleursOriginalesParticules[i][2] ; 
         }
      }
      break;
   case 't':
      transparenceSelonAge = !transparenceSelonAge;
      glutPostRedisplay();
      break;
   }
}

void clavierSpecial( int touche, int x, int y )
{
}

/*void convertWindowToAxisCoord(const int winx, const int winy, GLdouble& axisX, GLdouble& axisY)
{
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);
	int window_width = glutGet(GLUT_WINDOW_WIDTH);

	axisX = winx / (double) window_width * (AXIS_X_MAX - AXIS_X_MIN) + AXIS_X_MIN;
	axisY = (1 - winy / (double) window_height) * (AXIS_Y_MAX - AXIS_Y_MIN) + AXIS_Y_MIN;
}*/

//Prend en paramètre les coordonnées de la souris et selectionne la particule
void toggleSelectionParticules(const GLint x, const GLint y)
{
	GLubyte coulPixel[3];
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);
	glReadPixels( x, window_height - y - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, coulPixel); // get la couleur du pixel

	if(0 == coulPixel[0] && 
		0 == coulPixel[1] &&
		0 == coulPixel[2] ) // si le pixel est noir, il faudra vérifier si c'est une particule déjà selectionnée avec sa position
	{
		/*GLfloat winx,winy,winz;//coordonées du clic
		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLdouble posX, posY, posZ;
		
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		winx = (float)x;
		winy = (float)viewport[3] - y;
		glReadPixels(x, window_height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);
		
		std::cout << "--------------------" <<std::endl;
		std::cout << "Clic ---> " << winx << " : " << winy << " : " << winz << std::endl;

		gluUnProject( winx, winy, winz, modelview, projection, viewport, &posX, &posY, &posZ); //get la position 3d de l'objet sur lequel on a cliquer

		GLdouble sourisx,sourisy;


		for(unsigned int i = 0; i < nparticules; i++)
		{
			if(abs(particules[i].position[0] - posX) < 0.01f && 
			   abs(particules[i].position[1] - posY) < 0.01f &&
			   abs(particules[i].position[2] - posZ) < 0.01f)
			{
				particules[i].estSelectionnee = false;
				particules[i].couleur[0] = couleursOriginalesParticules[i][0]; //remettre à la couleur d'origine
				particules[i].couleur[1] = couleursOriginalesParticules[i][1];
				particules[i].couleur[2] = couleursOriginalesParticules[i][2];

				break; //on considère que chaque particule est unique donc on break quand on l'a trouvé
			}	
			std::cout << particules[i].position[0] << " : " << particules[i].position[0] << " : " << particules[i].position[0] << std::endl;
		}*/
	}
	else
	{
		//on doit scanner toutes les particules à cause de la selection par couleur
		for(unsigned int i = 0; i < nparticules; i++)
		{
			if(particules[i].couleur[0] == coulPixel[0] && 
			   particules[i].couleur[1] == coulPixel[1] &&
			   particules[i].couleur[2] == coulPixel[2])
			{
				particules[i].estSelectionnee = true;
				particules[i].couleur[0] = 0; //mettre à noir lorsque selectionné
				particules[i].couleur[1] = 0;
				particules[i].couleur[2] = 0;

				break; //on considère que chaque particule est unique donc on break quand on l'a trouvé
			}				
		}
	}

	glutPostRedisplay();
}

void sourisClic( int button, int state, int x, int y )
{
   if ( state == GLUT_DOWN )
   {
      dernierX = x;
      dernierY = y;
      if(button == GLUT_RIGHT_BUTTON && !enmouvement)
      {
      	toggleSelectionParticules((GLint)x,(GLint)y);
      }
   }
}

void sourisMouvement( int x, int y )
{
   theta += (dernierX-x) / 100.0;
   phi += (dernierY-y) / 50.0;
   dernierX = x;
   dernierY = y;

   if ( phi >= M_PI )
      phi = M_PI - 0.001;
   else if ( phi <= 0 )
      phi = 0.001;

   glutPostRedisplay();
}

int main( int argc, char *argv[] )
{
   // initialisation de GLUT
   glutInit( &argc, argv );
   // paramétrage de l'affichage
   glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
   // taille de la fenetre
   glutInitWindowSize( g_largeur, g_hauteur );
   // création de la fenêtre
   g_feneID = glutCreateWindow( "INF2705" );

   // référencement de la fonction de rappel pour l'affichage
   glutDisplayFunc( afficherScene );
   // référencement de la fonction de rappel pour le redimensionnement
   glutReshapeFunc( redimensionnement );
   // référencement de la fonction de gestion des touches
   glutKeyboardFunc( clavier );
   // référencement de la fonction de gestion des touches spéciales
   glutSpecialFunc( clavierSpecial );
   // référencement de la fonction de rappel pour le mouvement de la souris
   glutMotionFunc( sourisMouvement );
   // référencement de la fonction de rappel pour le clic de la souris
   glutMouseFunc( sourisClic );

   initialisation();
   if ( enmouvement ) animer( 0 );

   // boucle principale de gestion des evenements
   glutMainLoop();

   // le programme n'arrivera jamais jusqu'ici
   return EXIT_SUCCESS;
}

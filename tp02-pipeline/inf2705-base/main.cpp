// Prénoms, noms et matricule des membres de l'équipe:
// - Alexis Cabana-Loriaux (1688398)
// - Vincent Audet (1637998)

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "varglob.h"
#include "float3.h"
#include "teapot_data.h"

#define AXE_X 0
#define AXE_Y 1
#define AXE_Z 2
#define PI 3.1415392

// partie 1:
double thetaBras = 0.0;   // angle de rotation du bras
double phiBras = 0.0;     // angle de rotation du bras
double angleTheiere = 0.0;

float positionCamera[3] = {0, 15, 5};
float directionVueCamera[3] = {0, 0, 0};
float vecteurNormalCamera[3] = {0, 0, 1};
float positionBras[3] = {0.0,0.0,0.0};

// partie 2:
GLdouble MAXPHI = M_PI - 0.001, MAXTHETA = M_PI - 0.001;
GLdouble MINPHI = 0.001, MINTHETA = 0.001;

GLuint g_VBOsommets = 0;
GLuint g_VBOconnec = 0;
double originalDist;
bool modeLookAt = true;


void creerVBO()
{
   // créer le VBO pour les sommets
   //generer le VBO (sommet)
   glGenBuffers(1, &g_VBOsommets);

   //lier l'objet tampon pour l'utiliser
   glBindBuffer(GL_ARRAY_BUFFER, g_VBOsommets);

   //Charger le tableau de sommets sur le serveur
   glBufferData(GL_ARRAY_BUFFER, sizeof(gTeapotSommets), gTeapotSommets, GL_STATIC_DRAW);

   //glBindBuffer(GL_ARRAY_BUFFER, 0);
   //
   // créer le VBO la connectivité
   //genere le IBO
   glGenBuffers(1, &g_VBOconnec);

   //lier l'objet tampon pour l'utiliser
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_VBOconnec);

   //charger le tableau de connectivite sur le serveur
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gTeapotConnec), gTeapotConnec, GL_STATIC_DRAW);
   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void initialisation()
{
   theta = 0.;
   phi = PI / 3 ;
   originalDist = sqrt(positionCamera[AXE_X]*positionCamera[AXE_X] + 
   				positionCamera[AXE_Y]*positionCamera[AXE_Y] + 
   				positionCamera[AXE_Z]*positionCamera[AXE_Z]); //distance à l'origine
   dist = originalDist;

   // donner la couleur de fond
   glClearColor( 0.0, 0.0, 0.0, 1.0 );

   // activer les etats openGL
   glEnable( GL_DEPTH_TEST );
   glMatrixMode(GL_MODELVIEW);

   glewInit();

   creerVBO();
}

// (partie 1) Vous devez vous servir de ces fonctions pour tracer les quadriques.
void afficherCylindre( )
{
   // affiche un cylindre de rayon 1 et de hauteur 1
   static GLUquadric* q = 0;
   if ( !q ) q = gluNewQuadric();
   const GLint slices = 16, stack = 2;
   glColor3f( 0, 0, 1 );
   gluCylinder( q, 1.0, 1.0, 1.0, slices, stack );
}
void afficherSphere( )
{
   // affiche une sphere de rayon 1
   static GLUquadric* q = 0;
   if ( !q ) q = gluNewQuadric();
   const GLint slices = 16, stack = 32;
   glColor3f( 1, 0, 0 );
   gluSphere( q, 1.0, slices, stack );
}

// (partie 2) Vous modifierez cette fonction pour utiliser les VBOs
void afficherTheiere()
{
   glColor3f( 0.0, 1.0, 0.0 );

   // glut offre une fonction pour tracer une théière et vous pouvez utiliser cette fonction pour la première partie
   //glutSolidTeapot( 1.0 );

   //activer et specifier un pointeur 0 vers les sommets
   glBindBuffer(GL_ARRAY_BUFFER,g_VBOsommets);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,g_VBOconnec);
   
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   //tracer la primitive
   glDrawElements(GL_TRIANGLES, sizeof(gTeapotConnec)/sizeof(GLuint),GL_UNSIGNED_INT,0);
   //desactiver l'utilisation des tableaux de sommets
   glDisableClientState(GL_VERTEX_ARRAY);

   glBindBuffer(GL_ARRAY_BUFFER,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void afficherBras()
{
   const GLfloat cylhauteur = 2.0;
   const GLfloat sphererayon = 0.25;
	
   if(!modeLookAt)
   {	
   	glRotatef(theta, 0.f, 0.f, 1.f);
		glTranslatef(positionBras[AXE_X], positionBras[AXE_Y], positionBras[AXE_Z]);
	}

   // toutes les modifications ici ...
   glPushMatrix();
   glScalef(sphererayon, sphererayon, cylhauteur);
   // ajouter une ou des transformations afin de tracer un cylindre de rayon "sphererayon" et de hauteur "cylhauteur"
   afficherCylindre();
   glPopMatrix();

   // se déplacer un peu
   glTranslatef( 0.0, 0.0, cylhauteur+sphererayon/2);
   glPushMatrix();
   glScalef(sphererayon, sphererayon ,sphererayon);
   // ajouter une ou des transformations afin de tracer une sphère de rayon "sphererayon"
   afficherSphere();
   glPopMatrix();

   //2ieme cylindre du bras
   glRotatef( 90, 0.0, 1.0, 0.0 );
   glRotatef(phiBras, 1.0, 0.0, 0.0);
   glTranslatef(0.0, 0.0, sphererayon/2);
   glPushMatrix();
   glScalef(sphererayon, sphererayon, cylhauteur);
   afficherCylindre();
   glPopMatrix();

   //afficher 2ieme boule
   glTranslatef( 0.0, 0.0, cylhauteur+sphererayon/2);
   glPushMatrix();
   glScalef(sphererayon, sphererayon ,sphererayon);
   afficherSphere();
   glPopMatrix();

   //afficher 3ieme bras
   glTranslatef(0.0, 0.0, sphererayon/2);
   glRotatef(thetaBras, 1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef(sphererayon, sphererayon, cylhauteur);
   afficherCylindre();
   glPopMatrix();

   //afficher la 3ieme sphere
   glTranslatef( 0.0, 0.0, cylhauteur+sphererayon/2);
   glPushMatrix();
   glScalef(sphererayon, sphererayon ,sphererayon);
   afficherSphere();
   glPopMatrix();

   //afficher la théière
   glRotatef(-90, 0.0, 1.0, 0.0);
   glRotatef(90, 1.0, 0.0, 0.0);
   glRotatef(angleTheiere, 0.0, 0.0, 1.0);
   glTranslatef(1.0, -0.5, 0.0);
   glPushMatrix();
   glScalef(0.25,0.25,0.25);   
   afficherTheiere();
   glPopMatrix();
}

void definirCamera()
{
   if ( modeLookAt )
   	gluLookAt( 	positionCamera[AXE_X],		positionCamera[AXE_Y],		positionCamera[AXE_Z],
   					directionVueCamera[AXE_X],	directionVueCamera[AXE_Y],	directionVueCamera[AXE_Z],
   					vecteurNormalCamera[AXE_X],vecteurNormalCamera[AXE_Y],vecteurNormalCamera[AXE_Z]
   					);
   else
   	gluLookAt( 0, 0, 0, positionBras[AXE_X], positionBras[AXE_Y], positionBras[AXE_Z],  0, 0, 1 ); //test
}

void afficherScene()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluPerspective( 45.0, (GLdouble) g_largeur / (GLdouble) g_hauteur, 0.1, 300.0 );

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   definirCamera();

   glColor3f( 1., .5, .5 );
   glBegin( GL_QUADS );
   glVertex3f( -4.0,  4.0, 0.0 );
   glVertex3f(  4.0,  4.0, 0.0 );
   glVertex3f(  4.0, -4.0, 0.0 );
   glVertex3f( -4.0, -4.0, 0.0 );
   glEnd();

   afficherBras();

   glutSwapBuffers();
}

void redimensionnement( GLsizei w, GLsizei h )
{
   g_largeur = w;
   g_hauteur = h;
   glViewport( 0, 0, w, h );
   glutPostRedisplay();
}

void reinitCamera()
{
	positionCamera[AXE_X] = 0;	
	positionCamera[AXE_Y] = 15; 
	positionCamera[AXE_Z] = 5 ;
   directionVueCamera[AXE_X] = 0;	
   directionVueCamera[AXE_Y] = 0;
   directionVueCamera[AXE_Z] = 0;
   vecteurNormalCamera[AXE_X] = 0;
   vecteurNormalCamera[AXE_Y] = 0;
   vecteurNormalCamera[AXE_Z] = 1;
   positionBras[AXE_X] = 0.0;
   positionBras[AXE_Y] = 0.0;
   positionBras[AXE_Z] = 0.0;
   dist = originalDist;
   phi = PI/3;
	theta = PI/2;
   modeLookAt = true;
}

void initLookAtByTranslateAndRot()
{
   dist = originalDist;
	positionBras[AXE_X] = 0.0;
   positionBras[AXE_Y] = 10.0;
   positionBras[AXE_Z] = 0.0;

	positionCamera[AXE_X] = 0;	
	positionCamera[AXE_Y] = 0; 
	positionCamera[AXE_Z] = 0;
   directionVueCamera[AXE_X] = positionBras[AXE_X];	
   directionVueCamera[AXE_Y] = positionBras[AXE_Y];
   directionVueCamera[AXE_Z] = positionBras[AXE_Z];
   vecteurNormalCamera[AXE_X] = 0;
   vecteurNormalCamera[AXE_Y] = 0;
   vecteurNormalCamera[AXE_Z] = 1;
   phi = PI/3;
	theta = PI/2;
   modeLookAt = false;
}

void updateViewingDistance()
{
   if(!modeLookAt)
   {	
      positionBras[AXE_X] = dist * sin(phi) * cos(theta);
		positionBras[AXE_Y] = dist * sin(phi) * sin(theta);
		positionBras[AXE_Z] = dist * cos(phi);
   }
   else
   {
		positionCamera[AXE_X] = dist * sin(phi) * cos(theta);
		positionCamera[AXE_Y] = dist * sin(phi) * sin(theta);
		positionCamera[AXE_Z] = dist * cos(phi);

   }
}

void clavier( unsigned char touche, int x, int y )
{
   switch ( touche )
   {
   case '\e': // escape
      glutDestroyWindow( g_feneID );
      exit( 0 );
      break;
   case '_'://nous avons décidé de prendre les boutons qui sont les plus faciles d'accès (sans tenir shift)
   case '-':
     dist += 0.3;
     updateViewingDistance();
     break;
   case '+':
   case '=':
      if ( dist > 4.0 )
      {
        dist -= 0.3;
        updateViewingDistance();
      }

      break;
   case 'r':
   	reinitCamera();
      break;
   case 'l':
      modeLookAt = !modeLookAt;
      initLookAtByTranslateAndRot();
      std::cout << " modeLookAt=" << modeLookAt << std::endl;
      break;
   case 'g':
      {
         static bool modePlein = true;
         modePlein = !modePlein;
         if(modePlein)
         	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
         else
         	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      }
      break;
   case '[':
   	if( angleTheiere >= -45)
      	angleTheiere -= 1.0;
      break;
   case ']':
		if( angleTheiere <= 45)
     		angleTheiere += 1.0;
      break;
   case 'q':
      angleTheiere -= 1.0;
      break;
   case 'w':
      angleTheiere += 1.0;
      break;

   }
   glutPostRedisplay();
}

void clavierSpecial( int touche, int x, int y )
{
   switch ( touche )
   {
   case GLUT_KEY_LEFT:
      phiBras -= 2.0;
      break;
   case GLUT_KEY_RIGHT:
      phiBras += 2.0;
      break;
   case GLUT_KEY_DOWN:
      if( thetaBras >= -90)
         thetaBras -= 2.0;
      break;
   case GLUT_KEY_UP:
      if(thetaBras <= 0)
         thetaBras += 2.0;
      break;
   }
   glutPostRedisplay();
}

int dernierX, dernierY;
bool boutoncliquer = false;
void sourisClic( int button, int state, int x, int y )
{
   // button est un parmi { GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON }
   // state  est un parmi { GLUT_DOWN, GLUT_UP }
   // Pour référence et quelques exemples, voir http://www.lighthouse3d.com/opengl/glut/index.php?9
   if(button == GLUT_LEFT_BUTTON)
   {
	   if ( state == GLUT_DOWN )
	   	boutoncliquer = true;
	   else
	   	boutoncliquer = false;
	}

   dernierX = x;
   dernierY = y;
}

void sourisMouvement( int x, int y )
{	
	if(boutoncliquer)
	{
		if (modeLookAt) //on calcul angles à rotater, puis on applique les changements
		{
			theta -= (x - dernierX) * 0.01f; //on soustrait car la rotation se fait contraire au mouv. de la souris
			phi   -= (y - dernierY) * 0.01f;
			if(phi < PI / 6.0)
				phi = PI / 6.0;
			else if (phi > 2 * PI / 3.0)
				phi = 2 * PI / 3.0;

			positionCamera[AXE_X] = dist * sin(phi) * cos(theta);
			positionCamera[AXE_Y] = dist * sin(phi) * sin(theta);
			positionCamera[AXE_Z] = dist * cos(phi);
		}
		else
		{
			theta -= (x - dernierX) * 0.01f; //on soustrait car la rotation se fait contraire au mouv. de la souris
			phi   += (y - dernierY) * 0.01f;

			if(phi > 5 * PI / 6.0)
				phi = 5 * PI / 6.0;
			else if (phi < PI / 3.0)
				phi = PI / 3.0;

			positionBras[AXE_X] = dist * sin(phi) * cos(theta);
   		positionBras[AXE_Y] = dist * sin(phi) * sin(theta);
   		positionBras[AXE_Z] = dist * cos(phi);

		}
	}

   dernierX = x;
   dernierY = y;

	definirCamera();
   glutPostRedisplay();
}

int main( int argc, char *argv[] )
{
   // initialisation de GLUT
   glutInit( &argc, argv );
   // paramétrage de l'affichage
   glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
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

   // boucle principale de gestion des evenements
   glutMainLoop();

   // le programme n'arrivera jamais jusqu'ici
   return EXIT_SUCCESS;
}

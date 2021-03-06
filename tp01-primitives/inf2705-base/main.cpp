// Prénoms, noms et matricule des membres de l'équipe:
// - Prénom1 NOM1 (matricule1)
// - Prénom2 NOM2 (matricule2)

#include <iostream>
#include <GL/glut.h>
#include "varglob.h"
#include "float3.h"

#if 1
// pour un W
float p1[3] = { -4.0,  2.0,  0.0 };
float p2[3] = { -3.0, -3.0,  0.0 };
float p3[3] = { -1.0, -3.0,  0.0 };
float p4[3] = {  0.0,  0.0,  0.0 };
float p5[3] = {  1.0, -3.0,  0.0 };
float p6[3] = {  3.0, -3.0,  0.0 };
float p7[3] = {  4.0,  2.0,  0.0 };
#else
// pour une flèche (Voir apprentissage supplémentaire)
float p1[3] = { -3.0,  1.0,  0.0 };
float p2[3] = { -3.0, -1.0,  0.0 };
float p3[3] = {  0.0, -1.0,  0.0 };
float p4[3] = { -0.5, -2.5,  0.0 };
float p5[3] = {  3.0,  0.0,  0.0 };
float p6[3] = { -0.5,  2.5,  0.0 };
float p7[3] = {  0.0,  1.0,  0.0 };
#endif

void initialisation()
{
   // donner la couleur de fond
   glClearColor( 0.0, 0.0, 0.0, 1.0 );

   // définir le pipeline graphique
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   // la taille de la fenêtre
   glOrtho( -12, 12, -8, 8, -10, 10 );
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   // activer le mélange de couleur pour bien voir les possibles plis à l'affichage
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void afficherScene()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glLoadIdentity();

   // utiliser du rouge
   glColor3f( 1, 0, 0 );
   // utiliser du rouge, mais avec un alpha de 0.8 plutôt que 1.0 pour bien voir les possibles plis à l'affichage
   glColor4f( 1, 0, 0, 0.8 );
	glLoadIdentity();

   // la fenêtre varie en X de -12 à 12 et en Y de -8 à 8
	
	glTranslatef(-8.0, 4.0, 0.0); //#1
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p4);	
	glVertex3fv(p7);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(p4);
	glVertex3fv(p1);	
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glVertex3fv(p5);	
	glVertex3fv(p6);
	glVertex3fv(p7);
	glEnd();
	
	glColor3f( 1, 1, 0 );
	glTranslatef(8.0, 0.0, 0.0); //#2
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p4);	
	glVertex3fv(p7);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(p4);
	glVertex3fv(p1);	
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glVertex3fv(p5);	
	glVertex3fv(p6);
	glVertex3fv(p7);
	glEnd();
	
	glColor3f( 1, 0, 1 );
	glTranslatef(8.0, 0.0, 0.0); //#3
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p4);	
	glVertex3fv(p7);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(p4);
	glVertex3fv(p1);	
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glVertex3fv(p5);	
	glVertex3fv(p6);
	glVertex3fv(p7);
	glEnd();


	glColor3f( 0, 1, 1 );
	glTranslatef(0.0, -8.0, 0.0); //#4
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p4);	
	glVertex3fv(p7);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(p4);
	glVertex3fv(p1);	
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glVertex3fv(p5);	
	glVertex3fv(p6);
	glVertex3fv(p7);
	glEnd();

	glColor3f( 1, 1, 1 );
	glTranslatef(-8.0, 0.0, 0.0); //#5
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p4);	
	glVertex3fv(p7);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(p4);
	glVertex3fv(p1);	
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glVertex3fv(p5);	
	glVertex3fv(p6);
	glVertex3fv(p7);
	glEnd();

	glTranslatef(-8.0, 0.0, 0.0); //#6
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p4);	
	glVertex3fv(p7);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(p4);
	glVertex3fv(p1);	
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glVertex3fv(p5);	
	glVertex3fv(p6);
	glVertex3fv(p7);
	glEnd();

	glTranslatef(-4.0, 4.0, 0.0);

	glColor3f( 1, 1, 1 );


	glBegin(GL_LINES);
	glVertex3f(-12.0,0.0,0.0);
	glVertex3f(12.0,0.0,0.0);
	glVertex3f(8.0,8.0,0.0);
	glVertex3f(8.0,-8.0,0.0);
	glVertex3f(16.0,8.0,0.0);
	glVertex3f(16.0,-8.0,0.0);
	glEnd();

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
   case 'g':
		
      glutPostRedisplay(); // indiquer que la fenêtre a besoin d'être réafficher
      break;
   }
}

void clavierSpecial( int touche, int x, int y )
{
}

void sourisClic( int button, int state, int x, int y )
{
}

void sourisMouvement( int x, int y )
{
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

   // boucle principale de gestion des événements
   glutMainLoop();

   // le programme n'arrivera jamais jusqu'ici
   return EXIT_SUCCESS;
}

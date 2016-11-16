// les étudiants peuvent utiliser l'exemple du cours pour démarrer:
//    http://www.cours.polymtl.ca/inf2705/nuanceurs/exempleSimple/

#define M_PI_2  (1.57079632679489661923)  // PI/2

void main( void )
{
   // transformation standard du sommet (ModelView et Projection)
   gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
   //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

   // calculer de la position du sommet dans l'espace de l'oeil afin que la carte fasse le découpage demandée par glClipPlane()
   gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;
   // (à partir de la version 1.30, c'est plutôt gl_ClipDistance[] qu'il faut utiliser)
   // vec4 vsPos = gl_ModelViewMatrix * gl_Vertex;
   // gl_ClipDistance[0] = dot( u_plane0, vsPos );
   // gl_ClipDistance[1] = dot( u_plane1, vsPos );
}

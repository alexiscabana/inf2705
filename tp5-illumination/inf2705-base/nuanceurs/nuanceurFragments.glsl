// les étudiants peuvent utiliser l'exemple du cours pour démarrer:
//    http://www.cours.polymtl.ca/inf2705/nuanceurs/exempleIllumination/phong.glsl

// Les paramètres de la source de lumière sont définis ainsi:
// struct gl_LightSourceParameters
// {
//    vec4 ambient;
//    vec4 diffuse;
//    vec4 specular;
//    vec4 position;
//    vec4 halfVector;
//    vec3 spotDirection;
//    float spotExponent;
//    float spotCutoff;          // ( [0.0,90.0], 180.0 )
//    float spotCosCutoff;       // == cos(spotCutoff) ( [1.0,0.0], -1.0 )
//    float constantAttenuation;
//    float linearAttenuation;
//    float quadraticAttenuation;
// };
// uniform gl_LightSourceParameters gl_LightSource[gl_MaxLights];
// bool gl_FrontFacing  // on est en train de tracer la face avant?

void main( void )
{
   gl_FragColor = vec4( 0.5, 0.5, 0.5, 1.0 ); // gris!
}

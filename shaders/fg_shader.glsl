// Vertex Shader
#version 120

#define M_PI 3.1415926535897932384626433832795

varying vec4 pos_sommet; 
varying vec3 nml_sommet;
uniform mat4 view_matrix;
uniform vec3 light_world_position;

/* Parametres geometrique
mat4 gl_ModelViewMatrix : la matrice modelview entre le repère objet et le repère caméra 
mat3 gl_NormalMatrix : la matrice "normal" (c'est l'équivalent de la modelview matrix à utiliser pour les normales)
mat4 view_matrix : la matrice View entre le repère du monde et le repère caméra
vec4 pos_sommet : position du sommet (dans son repère propre)
vec3 nml_sommet : normal à la surface au sommet (dans son repère propre)
*/
/* Propriétés de lumière
vec4 gl_LightSource[0].diffuse : puissance de la source pour la réflexion diffuse
vec4 gl_LightSource[0].specular : puissance de la source pour la réflexion speculaire
vec3 light_world_position : position de la source de lumière (dans le repère du monde)
*/
/* Propriétés de l'objet
vec4 gl_FrontMaterial.diffuse : coefficient de reflexion diffus.
float gl_FrontMaterial.shininess : coefficient de brillance.
*/

// Exemple de transformation d'un vec3 b en vec4 a
// vec4 a = vec4(b,1.0);
// vec4 a = vec4(b,0.0);
// Exemple de transformation d'un vec4 b en vec3 a
// vec3 a = b.xyz;

// Produit scalaire : dot
// Exemple :
// vec3 a = vec3(1.,0.,1.);
// vec3 b = vec3(1.,1.,0.);
// float resultat = dot(a,b);

// Normaliser un vecteur : normalize
// Exemple :
// vec3 a = vec3(1.,0.,1.);
// vec3 a_norm = normalize(a);

// Norme d'un vecteur : length
// Exemple :
// vec3 a = vec3(1.,0.,1.);
// float l = length(a);

// Puissance : pow
// Exemple : res = a^b
// float a,b;
// float res = pow(a,b);

void main() {
	gl_FragColor = vec4(1.0,0.0,0.0,1.0);
	
	// Faire les exercices (derniere page enonce)
	// Ajout du Modele d'éclairage
}


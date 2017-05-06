/*#include <stdio.h>
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h> 

int main(int argc, char **argv)
{
	printf("Hello World");
	return(0);
}*/

#include "GL/glew.h"
#define GLFW_DLL
#include "GLFW/glfw3.h"
#include <stdio.h>

int main () 
{
  // start GL context and O/S window using the GLFW helper library
  if (!glfwInit ()) 
  {
    fprintf (stderr, "ERROR: could not start GLFW3\n");
    return 1;
  } 

  GLFWwindow* window = glfwCreateWindow (640, 480, "Hello Triangle", NULL, NULL);

  if (!window) 
  {
    fprintf (stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent (window);

  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit ();

  // get version info
  const GLubyte* renderer = glGetString (GL_RENDERER);
  const GLubyte* version = glGetString (GL_VERSION);
  printf ("Renderer: %s\n", renderer);
  printf ("OpenGL version supported %s\n", version);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable (GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

  /* OTHER STUFF GOES HERE NEXT */

  // ARRAY FOR TRIANGLE POINTS
  GLfloat points1[] = {
   -0.5f,  0.5f,  0.0f,
   0.0f, 0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
}; 

  GLfloat points2[] = {
   0.0f,  0.5f,  0.0f,
   0.0f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
}; 

// VERTEX BUFFER STUFF
GLuint vbo1 = 0;
glGenBuffers (1, &vbo1);
glBindBuffer (GL_ARRAY_BUFFER, vbo1);
glBufferData (GL_ARRAY_BUFFER, sizeof (points1), points1, GL_STATIC_DRAW); 

GLuint vbo2 = 0;
glGenBuffers (1, &vbo2);
glBindBuffer (GL_ARRAY_BUFFER, vbo2);
glBufferData (GL_ARRAY_BUFFER, sizeof (points2), points2, GL_STATIC_DRAW); 

// VERTEX ATTRIBUTE OBJECT STUFF
GLuint vao1 = 0;
glGenVertexArrays (1, &vao1);
glBindVertexArray (vao1);
glEnableVertexAttribArray (0);
glBindBuffer (GL_ARRAY_BUFFER, vbo1);
glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL); 

GLuint vao2 = 0;
glGenVertexArrays (1, &vao2);
glBindVertexArray (vao2);
glEnableVertexAttribArray (0);
glBindBuffer (GL_ARRAY_BUFFER, vbo2);
glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL); 

// VERTEX SHADER
const char* vertex_shader =
"#version 410\n"
"in vec3 vp;"
"void main () {"
"  gl_Position = vec4 (vp.x, vp.y + 0.0, vp.z, 1.0);"
"}"; 

//FRAGMENT SHADER
const char* fragment_shader =
	"#version 410\n"
	"out vec4 frag_colour;"
	"void main () {"
	"  frag_colour = vec4 (0.1, 1.0, 0.9, 1.0);"
	"}"; 

// LOADING INTO GL SHADER
GLuint vs = glCreateShader (GL_VERTEX_SHADER);
glShaderSource (vs, 1, &vertex_shader, NULL);
glCompileShader (vs);
GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
glShaderSource (fs, 1, &fragment_shader, NULL);
glCompileShader (fs);

// GPU SHADER PROGRAMME
GLuint shader_programme = glCreateProgram ();
glAttachShader (shader_programme, fs);
glAttachShader (shader_programme, vs);
glLinkProgram (shader_programme); 

// DRAWING TRIANGLE
while (!glfwWindowShouldClose (window)) 
{
  // wipe the drawing surface clear
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram (shader_programme);
  glBindVertexArray (vao1);

  // draw points 0-3 from the currently bound VAO with current in-use shader
  glDrawArrays (GL_TRIANGLES, 0, 3);

  glBindVertexArray (vao2);

  // draw points 0-3 from the currently bound VAO with current in-use shader
  glDrawArrays (GL_TRIANGLES, 0, 3);

  // update other events like input handling 
  glfwPollEvents ();

  // put the stuff we've been drawing onto the display
  glfwSwapBuffers (window);
} 


  // close GL context and any other GLFW resources
  glfwTerminate();

  return 0;
} 
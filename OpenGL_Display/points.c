#include "GLFW/glfw3.h"
#include "stdlib.h"
#include "stdio.h"

const int WINDOWS_WIDTH = 640;
const int WINDOWS_HEIGHT = 480;

typedef struct
{ //datatype de vertice, con posicion y color del vertice.
    GLfloat x, y, z;
    GLfloat r, g, b, a;
} Vertex;

void drawPoint(Vertex v1, GLfloat size);
void drawPointsDEMO(int width, int height);

//drawPoint dibuja un punto pasandole el vertice y su tamaño
void drawPoint(Vertex v1, GLfloat size)
{
    glPointSize(size);                 //settea el tamaño de cada punto, en pixeles.
    glBegin(GL_POINTS);                //abrir una lista de vertices para una primitiva del tipo GL_POINTS
    glColor4f(v1.r, v1.g, v1.b, v1.a); //settear color
    glVertex3f(v1.x, v1.y, v1.z);      //y posicion de vertices usando el elemento pasado en atributos
    glEnd();                           //cerrar la lista de vertices
}

//demo que dibuja varios puntos, uno tras otro, de diferentes tamaños
void drawPointsDEMO(int width, int height)
{
    GLfloat size = 5.0f;
    for (GLfloat x = 0.0f; x <= 1.0f; x += 0.2f, size += 5)
    {
        Vertex v1 = {x, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        drawPoint(v1, size);
    }
}

int main(void)
{

    //crear ventana y darle el contexto
    GLFWwindow *window;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(WINDOWS_WIDTH, WINDOWS_HEIGHT, "Demo Puntos", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    //habilitar anti-alising y smoothing

    /*glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

    //rendering loop
    while (!glfwWindowShouldClose(window))
    {
        //mantener el ratio del viewport igual al tamaño de la ventana cuando resize window
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float)width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT); //borrar el color buffer en cada iteracion para updatear el nuevo contenido

        //set camera matrix for orthographic projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //Orthographic Projection
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawPointsDEMO(width, height); //llamamos al demo

        glfwSwapBuffers(window); //intercambiar el front y back buffer de la ventana
        glfwPollEvents();        //procesar el events queue, como los inputs, para evitar bloqueos
    }

    glfwDestroyWindow(window); //destruir window y se cierra
    glfwTerminate();           //terminar GLFW para liberar recursos
    exit(EXIT_SUCCESS);
}
#include "GLFW/glfw3.h"
#include "stdlib.h"
#include "stdio.h"

int main(void)
{
  GLFWwindow *window;       //crear un objeto del tipo GLFWwindow donde alamceno el id de la ventana
  
  if (!glfwInit())          //inicializar GLFW antes de usarlo
    exit(EXIT_FAILURE);
  
  //creo una ventana nueva, asigno tamaño, titulo, si es full screen y si comparte recursos
  
  window = glfwCreateWindow(640, 480, "Rotating triangle!", NULL, NULL);    
  
  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwMakeContextCurrent(window);   //asignar el contexto de opgl a la ventana creada
  /*si opengl es una maquina virtual, esta requiere almacenar su estado en cada momento en alguna parte. 
  El contexto asignado a esta ventana almacena el estado de opengl para trabajar sobre la misma especificamente*/

  while (!glfwWindowShouldClose(window))  //creo un loop de acciones que se ejecutan mientras la ventana no se cierre
  {
    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
    glBegin(GL_TRIANGLES);

    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window); //al salir del loop destruir ventana
  glfwTerminate(); //terminar glfw para liberar recursos
  exit(EXIT_SUCCESS);
}

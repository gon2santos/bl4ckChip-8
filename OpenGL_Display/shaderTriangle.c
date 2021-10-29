#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "stdlib.h"
#include "stdio.h"

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

int main(void)
{
    //=========================================================================================
    /////////////////////////// crear ventana y darle el contexto /////////////////////////////
    //=========================================================================================

    GLFWwindow *window;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "Shader Triangle", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("\nFailed to initialize GLAD");
        return -1;
    }

    //=========================================================================================
    /////////////////////////// compilar y linkear shaders ////////////////////////////////////
    //=========================================================================================

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);            //crear vertex shader y gurdar su id
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //meter el codigo del shader en el objeto shader creado
    glCompileShader(vertexShader);                              //compilar el shader

    //ERROR CHECK DE COMPILACION DEL SHADER
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //ERROR CHECK DE COMPILACION DEL FR SHADER
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();             //crear un shader program obj para unir los shaders compilados
    glAttachShader(shaderProgram, vertexShader);   //agregar el vertexshader al program obj
    glAttachShader(shaderProgram, fragmentShader); //agregar el fragment shader al program object
    glLinkProgram(shaderProgram);                  //unir/link ambos shaders para que la salida de uno sea la intrada del otro

    //ERROR CHECK EN EL LINKEADO DE LOS SHADERS
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //==================================================================================================
    ///////////// settear datos de los vertices, buffers y atributos de los vertices ///////////////////
    //==================================================================================================

    float vertices[] = {//los veritices del triangulo
                        -0.5f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f,
                        0.0f, 0.5f, 0.0f};

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);                                                     //crear un buffer de vertices y almacenar su id en VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                        //bind el buffer apuntado por VBO al buffer de vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copiar los vertices en buffer de vertices

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VBO
    glBindVertexArray(0); //unbind VAO

    //==================================================================================================
    ///////////////////////////////// render loop //////////////////////////////////////////////////////
    //==================================================================================================

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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

        //renderear aca
        glUseProgram(shaderProgram); //usar el shader program object
        glBindVertexArray(VAO); //bind VAO, no es necesario si solo tenemos uno
        glDrawArrays(GL_TRIANGLES, 0, 3);//
        
        //swap buffers y poll events
        glfwSwapBuffers(window); //intercambiar el front y back buffer de la ventana
        glfwPollEvents();        //procesar el events queue, como los inputs, para evitar bloqueos
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window); //destruir window y se cierra
    glfwTerminate();           //terminar GLFW para liberar recursos
    exit(EXIT_SUCCESS);
}
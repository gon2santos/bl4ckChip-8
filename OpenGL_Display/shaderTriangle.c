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

const char *fragmentShaderSourceORG = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

const char *fragmentShaderSourceYLW = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.9f, 0.0f, 1.0f);\n"
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

    //compilar vertex shader
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

    //compilar fragment shader orange
    unsigned int fragmentShaderORG;
    fragmentShaderORG = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderORG, 1, &fragmentShaderSourceORG, NULL);
    glCompileShader(fragmentShaderORG);

    //ERROR CHECK DE COMPILACION DEL FR SHADER
    glGetShaderiv(fragmentShaderORG, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderORG, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    //compilar fragment shader yellow
    unsigned int fragmentShaderYLW;
    fragmentShaderYLW = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYLW, 1, &fragmentShaderSourceYLW, NULL);
    glCompileShader(fragmentShaderYLW);

    //ERROR CHECK DE COMPILACION DEL FR SHADER
    glGetShaderiv(fragmentShaderYLW, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderYLW, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    //crear shader program
    unsigned int shaderProgramORG;
    shaderProgramORG = glCreateProgram();             //crear un shader program obj para unir los shaders compilados
    glAttachShader(shaderProgramORG, vertexShader);   //agregar el vertexshader al program obj
    glAttachShader(shaderProgramORG, fragmentShaderORG); //agregar el fragment shader al program object
    glLinkProgram(shaderProgramORG);                  //unir/link ambos shaders para que la salida de uno sea la intrada del otro

    //ERROR CHECK EN EL LINKEADO DE LOS SHADERS
    glGetProgramiv(shaderProgramORG, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramORG, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    //crear shader program
    unsigned int shaderProgramYLW;
    shaderProgramYLW = glCreateProgram();             //crear un shader program obj para unir los shaders compilados
    glAttachShader(shaderProgramYLW, vertexShader);   //agregar el vertexshader al program obj
    glAttachShader(shaderProgramYLW, fragmentShaderYLW); //agregar el fragment shader al program object
    glLinkProgram(shaderProgramYLW);                  //unir/link ambos shaders para que la salida de uno sea la intrada del otro

    //ERROR CHECK EN EL LINKEADO DE LOS SHADERS
    glGetProgramiv(shaderProgramYLW, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramYLW, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderORG);
    glDeleteShader(fragmentShaderYLW);

    //==================================================================================================
    ///////////// settear datos de los vertices, buffers y atributos de los vertices ///////////////////
    //==================================================================================================

    /*float vertices[] = {//los veritices del triangulo
                        -0.5f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f,
                        0.0f, 0.5f, 0.0f};*/

    float vertices0[] = {
                        -1.0f, -0.0f, 0.0f,
                        0.0f, -0.0f, 0.0f,
                        -0.5f, 0.5f, 0.0f
                        };
    
    float vertices1[] = {
                        0.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,
                        0.5f, 0.5f, 0.0f
                        };



    unsigned int VBO[2];
    unsigned int VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);                                                     //crear un buffer de vertices y almacenar su id en VBO
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);                                        //bind el buffer apuntado por VBO al buffer de vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices0), vertices0, GL_STATIC_DRAW); //copiar los vertices en buffer de vertices

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VBO
    glBindVertexArray(0); //unbind VAO

    //configurar 2ndo VAO y VBO

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);                                        //bind el buffer apuntado por VBO al buffer de vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW); //copiar los vertices en buffer de vertices

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

        //==================================================================================================
        ///////////////////////////////// renderear desde aca //////////////////////////////////////////////
        //==================================================================================================

        glUseProgram(shaderProgramORG); //usar el shader program object
        glBindVertexArray(VAO[0]); //bind VAO, no es necesario si solo tenemos uno
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(shaderProgramYLW); 
        glBindVertexArray(VAO[1]); //bind VAO, no es necesario si solo tenemos uno
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        //swap buffers y poll events
        glfwSwapBuffers(window); //intercambiar el front y back buffer de la ventana
        glfwPollEvents();        //procesar el events queue, como los inputs, para evitar bloqueos
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(shaderProgramORG);
    glDeleteProgram(shaderProgramYLW);
    glfwDestroyWindow(window); //destruir window y se cierra
    glfwTerminate();           //terminar GLFW para liberar recursos
    exit(EXIT_SUCCESS);
}
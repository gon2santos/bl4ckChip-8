#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "stdlib.h"
#include "stdio.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//=========================================================================================
/////////////////////////// codigo de shaders /////////////////////////////////////////////
//=========================================================================================


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


int main()
{
    //=========================================================================================
    /////////////////////////// crear ventana y darle el contexto /////////////////////////////
    //=========================================================================================

    GLFWwindow *window;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "Shaded rectangle", NULL, NULL);

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

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

        glUseProgram(shaderProgramORG);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, &VAO);
    glDeleteBuffers(2, &VBO);
    glDeleteProgram(shaderProgramORG);
    glDeleteProgram(shaderProgramYLW);
    glfwDestroyWindow(window); //destruir window y se cierra
    glfwTerminate();           //terminar GLFW para liberar recursos
    exit(EXIT_SUCCESS);
}
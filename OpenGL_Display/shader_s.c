
#include "shader_s.h"

#define VERTEX_SHADER_CODE_SIZE 200
#define FRAGMENT_SHADER_CODE_SIZE 200

//este es el shader program que quiero agregar al programa ppal
//uso: int *shaderProgram = makeShaderProgram("rutaVertexShader", "rutaFragmentShader");

unsigned int makeShaderProgram(const char *vertexPath, const char *fragmentPath)
{
    /* VERTEX SH FILE READING */
FILE* shaderFile = fopen(vertexPath, "r");
int fileSize = 0;
char* vertex_shader = NULL;

//Getting File Size
fseek( shaderFile, 0, SEEK_END );
fileSize = ftell( shaderFile );
rewind( shaderFile );

//Reading From File
vertex_shader = (char*)malloc( sizeof( char) * (fileSize+1) );
fread( vertex_shader, sizeof( char ), fileSize, shaderFile );
vertex_shader[fileSize] = '\0';
fclose( shaderFile );

    /* FRAGMENT SH FILE READING */
shaderFile = fopen(fragmentPath, "r");
fileSize = 0;
char* fragment_shader = NULL;

//Getting File Size
fseek( shaderFile, 0, SEEK_END );
fileSize = ftell( shaderFile );
rewind( shaderFile );

//Reading From File
fragment_shader = (char*)malloc( sizeof( char) * (fileSize+1) );
fread( fragment_shader, sizeof( char ), fileSize, shaderFile );
fragment_shader[fileSize] = '\0';
fclose( shaderFile );

/*const char* vertex_shader = "#version 330 core\n"
			     "layout (location = 0) in vec3 aPos;\n"
			     "void main()\n"
			     "{\n"
			     "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			     "}\0"*/

/*const char* fragment_shader = "#version 330\n"
                              "out vec4 FragColor;\n"
                              "void main () {\n"
                              "  FragColor = vec4(1.0f, 0.9f, 0.0f, 1.0f);\n"
                              "}\0";*/


    //compilar vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);            //crear vertex shader y gurdar su id
    glShaderSource(vertexShader, 1, (const char **)&vertex_shader, NULL);  //meter el codigo del shader en el objeto shader creado
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

    //compilar fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const char **)&fragment_shader, NULL);
    glCompileShader(fragmentShader);

    //ERROR CHECK DE COMPILACION DEL FR SHADER
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    //crear shader program
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
    
    return (shaderProgram); //si no funciona esto devolver el address del shaderprogram, sino hay que usar malloc :(
}





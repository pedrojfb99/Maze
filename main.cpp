// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// GLM header file
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// shaders header file
#include "common/shader.hpp"

// Vertex array object (VAO)
GLuint VertexArrayID;

// Vertex buffer object (VBO)
GLuint vertexbuffer;
GLuint plan;

// color buffer object (CBO)
GLuint colorbuffer;
GLuint plan_colorbuffer;

// GLSL program from the shaders
GLuint programID;

// Matrix id of the MVP
GLuint MatrixID;
glm::mat4 MVP_cube;
glm::mat4 MVP_plan;

glm::mat4 plan_Model = glm::mat4(1.0f);
glm::mat4 cube_Model = glm::mat4(1.0f);

glm::mat4 Projection = glm::mat4(1.0f);
glm::mat4 View = glm::mat4(1.0f);

GLint WindowWidth = 1024;
GLint WindowHeight = 768;

float x = 0.0, z = 0.0, delta = 0.5, angulo = 0.0;

//--------------------------------------------------------------------------------
void transferDataToGPUMemory(void)
{
    // VAO
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

    static const GLfloat plan_data[] = {
        0.0f, 0.0f,  0.0f,
        0.0f, 0.0f, 20.0f,
       20.0f, 0.0f, 20.0f,
       20.0f, 0.0f, 20.0f,
        0.0f, 0.0f,  0.0f, 
       20.0f, 0.0f,  0.0f
    };

    static const GLfloat plan_color[] = {
        0.8f, 0.8f, 0.8f,
        0.6f, 0.6f, 0.6f,
        0.4f, 0.4f, 0.4f,
        0.4f, 0.4f, 0.4f,
        0.8f, 0.8f, 0.8f,
        0.4f, 0.4f, 0.4f
    };


    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
         0.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 2.0f,
         0.0f, 2.0f, 2.0f,
         2.0f, 2.0f, 0.0f,
         0.0f, 0.0f, 0.0f,
         0.0f, 2.0f, 0.0f,
         2.0f, 0.0f, 2.0f,
         0.0f, 0.0f, 0.0f,
         2.0f, 0.0f, 0.0f,
         2.0f, 2.0f, 0.0f,
         2.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 0.0f,
         0.0f, 2.0f, 2.0f,
         0.0f, 2.0f, 0.0f,
         2.0f, 0.0f, 2.0f,
         0.0f, 0.0f, 2.0f,
         0.0f, 0.0f, 0.0f,
         0.0f, 2.0f, 2.0f,
         0.0f, 0.0f, 2.0f,
         2.0f, 0.0f, 2.0f,
         2.0f, 2.0f, 2.0f,
         2.0f, 0.0f, 0.0f,
         2.0f, 2.0f, 2.0f,
         2.0f, 0.0f, 0.0f,
         2.0f, 2.0f, 2.0f,
         2.0f, 0.0f, 2.0f,
         2.0f, 2.0f, 2.0f,
         2.0f, 2.0f, 0.0f,
         0.0f, 2.0f, 0.0f,
         2.0f, 2.0f, 2.0f,
         0.0f, 2.0f, 0.0f,
         0.0f, 2.0f, 2.0f,
         2.0f, 2.0f, 2.0f,
         0.0f, 2.0f, 2.0f,
         2.0f, 0.0f, 2.0f
    };
    
    // One color for each vertex. They were generated randomly.
    static const GLfloat g_color_buffer_data[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    // Move vertex data to video memory; specifically to VBO called vertexbuffer
    glGenBuffers(1, &plan);
    glBindBuffer(GL_ARRAY_BUFFER, plan);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plan_data), plan_data, GL_STATIC_DRAW);
    
    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &plan_colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, plan_colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plan_color), plan_color, GL_STATIC_DRAW);
    
    // Move vertex data to video memory; specifically to VBO called vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    
}

//--------------------------------------------------------------------------------
void cleanupDataFromGPU()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteBuffers(1, &plan);
    glDeleteBuffers(1, &plan_colorbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
}

//--------------------------------------------------------------------------------
void setMVP(void)
{
    // Get a handle for our "MVP" uniform
    MatrixID = glGetUniformLocation(programID, "MVP");
    
    // Projection matrix : 45∞ Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    View       = glm::lookAt(
                                       glm::vec3(10,15,-20), // Camera is at (4,3,-3), in World Space
                                       glm::vec3(10,0,10), // and looks at the origin
                                       glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                       );

}

//--------------------------------------------------------------------------------
void draw ()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Use our shader
    glUseProgram(programID);
    
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform 
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP_cube[0][0]);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    
    //glEnable(GL_PROGRAM_POINT_SIZE);
    //glPointSize(10);
    // Draw the cube
    glDrawArrays(GL_TRIANGLES, 0, 12*3); //

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP_plan[0][0]);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, plan);
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, plan_colorbuffer);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    
    //glEnable(GL_PROGRAM_POINT_SIZE);
    //glPointSize(10);
    // Draw the cube
    glDrawArrays(GL_TRIANGLES, 0, 6); //

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);


}
//--------------------------------------------------------------------------------



int main( void )
{
    // Initialise GLFW
    glfwInit();
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window
    window = glfwCreateWindow( WindowWidth, WindowHeight, "A cube with 12 triangles", NULL, NULL);
    
    // Create window context
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    glewInit();
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    // transfer my data (vertices, colors, and shaders) to GPU side
    transferDataToGPUMemory();
    
    // set the model-view-projection matrix
    setMVP();
    
    // render scene for each frame
    do{

        if(glfwGetKey(window, GLFW_KEY_X)){
            if(x + 0.5 <= 18.0)
                x = x + 0.25;
        }

        if(glfwGetKey(window, GLFW_KEY_Z)){
            if(z + 0.5 <= 18.0)
                z = z + 0.25;

        }

        if(glfwGetKey(window, GLFW_KEY_Y)){
            angulo += delta;
            angulo = (angulo/360-1)*360;
            
        }




        // Model matrix : an identity matrix (model will be at the origin)
        
        cube_Model = glm::rotate(glm::mat4(1.0),glm::radians(angulo),glm::vec3(0,1,0));
        cube_Model      = glm::translate(glm::mat4(1.0), glm::vec3(x, 0.0f, z));
        // Our ModelViewProjection : multiplication of our 3 matrices
        MVP_cube                  = Projection * View * cube_Model;

        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 plan_Model      = glm::mat4(1.0f);
        // Our ModelViewProjection : multiplication of our 3 matrices
        MVP_plan                  = Projection * View * plan_Model;



        // draw cube
        draw();
        // Swap buffers
        glfwSwapBuffers(window);
        // looking for events
        glfwPollEvents();
        
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VAO, VBOs, and shaders from GPU
    cleanupDataFromGPU();
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}


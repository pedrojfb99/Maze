#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  5.0f;
const float SENSITIVITY =  1.0f;
const float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    glm::vec3 aux_Position;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    int EvaluateCoordinates(float x, float y){

        // Paredes Exteriores
        if(x < -19.8 ){
            return -1;
        }
        if(x > 19.8 ){
            return -1;
        }
        if(y < -19.5) {
            return -1;
        }
        if(y > 19.5){
            return -1;
        }

        // Blocos
        if( ((x < -14.75) && y > 11.75)){
            return -1;
        }

        if( (x > -12.2 && x  < -6.8 ) && (y > 11.75)){
            return -1;
        }

        if (( x > -4.2 && x < 13.2) && ( y < 18.2 && y > 11.8)){
            return -1;
        }


        if (( x > 2.8 && x < 7.2) && ( y < 9.2 && y > 4.8)){
            return -1;
        }   

        if (( x > 8.8 && x < 13.2) && ( y < 9.2  && y > 4.8)){
            return -1;
        }


        if (( x > -0.2 && x < 13.2) && ( y < -10.8 && y > -18.2)){
            return -1;
        }


        if (( x > 7.8 && x < 13.2) && ( y < -2.8 && y > -18.2 )){
            return -1;
        }


        if (( x > -4.2 && x < 4.2) && ( y < -2.8 && y > -7.2 )){
            return -1;
        }


        if (( x > -9.2 && x < -3.8) && ( y < -15.8 && y > -18.2 )){
            return -1;
        }


        if (( x > -8.2 && x < -5.8) && ( y < -0.8 && y > -7.2 )){
            return -1;
        }


        if (( x > -13.2 && x < -3.8) && ( y < 5.2 && y >0.8 )){
            return -1;
        }

        //Paredes Interiores

        if (( x > -17.2 && x < 0.2) && ( y < 9.2  &&  y > 8.8)){
            return -1;
        }

        if (( x > -0.2 && x <0.2) && ( y < 9.2  &&  y > 2.8)){
            return -1;
        }

        if (( x > -0.2 && x < 13.2) && ( y < 3.2  &&  y > 2.8)){
            return -1;
        }

        if (( x > 12.8 && x < 13.2) && ( y < 3.2  &&  y > 0.8)){
            return -1;
        }

        if (( x > 12.8 && x < 16.2) && ( y < 1.2  &&  y > 0.8)){
            return -1;
        }

        if (( x > 8.8 && x < 16.2) && ( y < 5.2  &&  y > 4.8)){
            return -1;
        }

        if (( x > 15.8 && x < 16.2) && ( y < 18.2  &&  y > -14.2)){
            return -1;
        }

        if (( x > 17.8 && x < 18.2) && ( y < 18.2  &&  y > -14.2)){
            return -1;
        }

        if (( x > 15.8 && x < 18.2) && ( y <  -13.8 &&  y > -14.2)){
            return -1;
        }

        if (( x > 13.8 && x < 14.2) && ( y < -15.8  &&  y > -18.2)){
            return -1;
        }

        if (( x > -0.2 && x < 19.8) && ( y < -17.8  &&  y > -18.2)){
            return -1;
        }

        if (( x > -4.2 && x < -3.8) && ( y < 9.2  &&  y > -13.2)){
            return -1;
        }

        if (( x > -6.2 && x < -3.8) && ( y < -12.8  &&  y > -13.2)){
            return -1;
        }

        if (( x > -6.2 && x < -5.8) && ( y < -6.8 &&  y > -13.2)){
            return -1;
        }

        if (( x > -10.2 && x < -5.8) && ( y < -6.8  &&  y > -7.2)){
            return -1;
        }

        if (( x > -15.2 && x < -11.8) && ( y < -6.8  &&  y > -7.2)){
            return -1;
        }

        if (( x > -15.2 && x < -14.8) && ( y < 7.2 &&  y > -7.2)){
            return -1;
        }

        if (( x > 15.4 && x < -14.8) && ( y < 7.2 &&  y > -7.2)){
            return -1;
        }

        if (( x > -15.2 && x < -3.8) && ( y < 7.2  &&  y > 6.8)){
            return -1;
        }

        if (( x > -17.2 && x < -16.8) && ( y < 9.2  &&  y > -19.8)){
            return -1;
        }

        if (( x > -17.2 && x < -14.8) && ( y < -17.8  &&  y > -18.2)){
            return -1;
        }

        if (( x > -15.2 && x < -14.8) && ( y < -9.8  &&  y > -18.2)){
            return -1;
        }

        if (( x > -15.2 && x < -8.8) && ( y < -9.8  &&  y > -10.2)){
            return -1;
        }

        if (( x > -12.2 && x < -11.8) && ( y < -9.8  &&  y > -18.2)){
            return -1;
        }

        if (( x > -9.2 && x < -8.8) && ( y < -9.8  &&  y > -18.2)){
            return -1;
        }

        if (( x > 15.8 && x < 16.2) && ( y < -15.8  &&  y > -18.2)){
            return -1;
        }

        // buracos
        if((pow((x + 0.791),2.0) + (pow((y - 0.1471),2.0))) <= (pow(1,2))){
            return -2;
        }

        if((pow((x - 5.627),2.0) + (pow((y + 0.9405),2.0))) <= (pow(1.4,2))){
            return -2;
        }

        if((pow((x + 4.519),2.0) + (pow((y + 13.92),2.0))) <= (pow(1,2))){
            return -2;
        }

        if((pow((x + 5.0),2.0) + (pow((y),2.0))) <= (pow(1.4,2))){
            return -2;
        }

        if((pow((x - 5.312),2.0) + (pow((y - 8.12),2.0))) <= (pow(1.4,2))){
            return 0;
        }

        if((pow((x + 16.81),2.0) + (pow((y + 11.89),2.0))) <= (pow(1,2))){
            return -2;
        }

        if((pow((x + 18.77),2.0) + (pow((y + 13.45),2.0))) <= (pow(1.4,2))){
            return -2;
        }

        if((pow((x + 17.96),2.0) + (pow((y + 15.16),2.0))) <= (pow(1.2,2))){
            return -2;
        }

        return true;
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {   
        aux_Position = Position;
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD){
            Position += Front * velocity;
            if(EvaluateCoordinates(Position.x, Position.z) == -1)
                Position = aux_Position;
            else if(EvaluateCoordinates(Position.x, Position.z) == -2){
                Position.x = -13.5;
                Position.y = 0.5f;
                Position.z = 16.0f;
            }
        }
        if (direction == BACKWARD){
            Position -= Front * velocity;
            if(EvaluateCoordinates(Position.x, Position.z) == -1)
                Position = aux_Position;
            else if(EvaluateCoordinates(Position.x, Position.z) == -2){
                Position.x = -13.5;
                Position.y = 0.5f;
                Position.z = 16.0f;
            }
        }
        if (direction == LEFT){
            Position -= Right * velocity;
            if(EvaluateCoordinates(Position.x, Position.z) == -1)
                Position = aux_Position;
            else if(EvaluateCoordinates(Position.x, Position.z) == -2){
                Position.x = -13.5;
                Position.y = 0.5f;
                Position.z = 16.0f;
            }
        }
        if (direction == RIGHT){
            Position += Right * velocity;
            if(EvaluateCoordinates(Position.x, Position.z) == -1)
                Position = aux_Position;
            else if(EvaluateCoordinates(Position.x, Position.z) == -2){
                Position.x = -13.5;
                Position.y = 0.5f;
                Position.z = 16.0f;
            }
        }
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = 0;
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif



#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
constexpr float YAW = 0.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 5.0f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 0.0f;


class Camera
{
public:
    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);


    inline glm::mat4 GetViewMatrix(){ return view; }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    void updateCameraVectors();


    glm::vec3 pos;
private:
    // camera Attributes
    glm::vec3 Front;
    glm::vec3 Right;
    glm::vec3 up;
    glm::mat4 view;
    // euler Angles
    float yaw;
    float pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
};

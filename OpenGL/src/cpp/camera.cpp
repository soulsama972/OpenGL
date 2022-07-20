#include "camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch):
    Front(glm::vec3(0.0f, 0.0f, 0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY),yaw(yaw),pitch(pitch), up(up),pos(position)
{
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch):
Front(glm::vec3(0.0f, 0.0f, 0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
{
    pos = glm::vec3(posX, posY, posZ);
    up = glm::vec3(upX, upY, upZ);
    yaw = yaw;
    pitch = pitch;
    updateCameraVectors();
}


void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        pos += Front * velocity;
    if (direction == BACKWARD)
        pos -= Front * velocity;
    if (direction == LEFT)
        pos -= Right * velocity;
    if (direction == RIGHT)
        pos += Right * velocity;

    updateCameraVectors();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        if (yaw > 360.0f)
            yaw = 0;
        if (yaw < 0)
            yaw = 360 - yaw;
    }
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{

    Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    Front.y = sin(glm::radians(pitch));
    Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    Front = glm::normalize(Front);
    Right = glm::normalize(glm::cross(Front, up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.

    view = glm::lookAtRH(pos, pos + Front, glm::normalize(glm::cross(Right, Front)));
}
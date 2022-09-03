#include "camera.h"

constexpr auto radians = 0.01745329251994329576923690768489;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch):
    front(glm::vec3(0.0f, 0.0f, 0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY),yaw(yaw),pitch(pitch), up(up),pos(position)
{
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch):
front(glm::vec3(0.0f, 0.0f, 0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
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
        pos += front * velocity;
    if (direction == BACKWARD)
        pos -= front * velocity;
    if (direction == LEFT)
        pos -= right * velocity;
    if (direction == RIGHT)
        pos += right * velocity;

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
    front.x = cos(radians *yaw) * cos(radians * pitch);
    front.y = sin(radians * pitch);
    front.z = sin(radians * yaw) * cos(radians *pitch);

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, up)); 

    view = glm::lookAtRH(pos, pos + front, glm::normalize(glm::cross(right, front)));
}
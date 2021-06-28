#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as
// abstraction to stay away from window-system specific input methods
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// An abstract camera class that processes input and calculates the
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Default camera values
    constexpr static float YAW         = -90.0f;
    constexpr static float PITCH       =  0.0f;
    constexpr static float SPEED       =  2.5f;
    constexpr static float SENSITIVITY =  0.1f;
    constexpr static float ZOOM        =  45.0f;

    // camera Attributes
    glm::vec3 mPosition;
    glm::vec3 mFront; // Camera facing direction.
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;

    // euler Angles
    float mYaw;
    float mPitch;

    // camera options
    float mMovementSpeed;
    float mMouseSensitivity;
    float mZoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)
            , glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)
            , float yaw = YAW, float pitch = PITCH)
            : mFront(glm::vec3(0.0f, 0.0f, -1.0f))
            , mMovementSpeed(SPEED)
            , mMouseSensitivity(SENSITIVITY)
            , mZoom(ZOOM) {
        mPosition = position;
        mWorldUp = up;
        mYaw = yaw;
        mPitch = pitch;
        updateCameraVectors();
    }

    // constructor with scalar values
    Camera(float posX, float posY, float posZ
            , float upX, float upY, float upZ
            , float yaw, float pitch)
            : mFront(glm::vec3(0.0f, 0.0f, -1.0f))
            , mMovementSpeed(SPEED)
            , mMouseSensitivity(SENSITIVITY)
            , mZoom(ZOOM) {
        mPosition = glm::vec3(posX, posY, posZ);
        mWorldUp = glm::vec3(upX, upY, upZ);
        mYaw = yaw;
        mPitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles
    // and the LookAt Matrix
    glm::mat4 getViewMatrix() {
        return glm::lookAt(mPosition, mPosition + mFront, mUp);
    }

    // return FOV
    float getFOV() { return mZoom; }

    // processes input received from any keyboard-like input system.
    // Accepts input parameter in the form of camera defined ENUM
    // (to abstract it from windowing systems)
    void processKeyboard(CameraMovement direction, float deltaTime) {
        float velocity = mMovementSpeed * deltaTime;
        if (direction == FORWARD)
            mPosition += mFront * velocity;
        if (direction == BACKWARD)
            mPosition -= mFront * velocity;
        if (direction == LEFT)
            mPosition -= mRight * velocity;
        if (direction == RIGHT)
            mPosition += mRight * velocity;
    }

    // Processes input received from a mouse input system.
    // Expects the offset value in both the x and y direction.
    void processMouseMovement(float xOffset, float yOffset
            , GLboolean constrainPitch = true) {
        xOffset *= mMouseSensitivity;
        yOffset *= mMouseSensitivity;

        mYaw   += xOffset;
        mPitch += yOffset;

        // make sure that when pitch is out of bounds,
        // screen doesn't get flipped
        if (constrainPitch)
        {
            if (mPitch > 89.0f)
                mPitch = 89.0f;
            if (mPitch < -89.0f)
                mPitch = -89.0f;
        }

        // update mFront, mRight and mUp Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event.
    // Only requires input on the vertical wheel-axis
    void processMouseScroll(float yOffset) {
        mZoom -= (float)yOffset;
        if (mZoom < 1.0f)
            mZoom = 1.0f;
        if (mZoom > 45.0f)
            mZoom = 45.0f;
    }

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors() {
        // Calculate the new mFront vector
        glm::vec3 front;
        front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        front.y = sin(glm::radians(mPitch));
        front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        mFront = glm::normalize(front);

        // Also re-calculate the mRight and mUp vector.
        // Normalize the vectors, because their length gets closer to 0
        // the more you look up or down which results in slower movement.
        mRight = glm::normalize(glm::cross(mFront, mWorldUp));
        mUp    = glm::normalize(glm::cross(mRight, mFront));
    }
};
#endif
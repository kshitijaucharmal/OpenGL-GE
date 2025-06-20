#pragma once

#include <glm/glm.hpp>

struct PointLight {
    glm::vec3 position;
    float constant;

    glm::vec3 ambient;
    float linear;

    glm::vec3 diffuse;
    float quadratic;

    glm::vec3 specular;
    float pad = 0.0f; // Optional

    // Constructor for convenience
    PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec,
               float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f)
    : position(pos), ambient(amb), diffuse(diff), specular(spec),
    constant(constant), linear(linear), quadratic(quadratic) {}
};

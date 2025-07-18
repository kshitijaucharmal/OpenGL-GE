#include "SimObjectSystem.hpp"

#include <utility>

#include "Components/Rendering/Material.hpp"

#include "glm/gtc/quaternion.hpp"

namespace SimObject {

    // Create entity with default values
    entt::entity Create(entt::registry& registry, std::string name){
        const auto entity = registry.create();

        // Add a transform
        registry.emplace<Transform>(entity, Transform{
            .name = std::move(name)
        });

        return entity;
    }

    glm::mat4 ComposeTransform(const Transform &t) {
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, t.position);
        model *= glm::mat4_cast(t.rotation);
        model = glm::scale(model, t.scale);
        return model;
    }

}

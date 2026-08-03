#pragma once

#include "Transform.h"
#include "Model.h"
#include <string>

namespace nu {
    class Scene;

    struct ActorDesc {
        std::string name;
        std::string tag;
        Transform transform;
        Vector2 vel;
        float damping{ 0.0f };
        float lifespan{ 0 };
        Model model;
    };

    class Actor {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) : m_name{ actorDesc.name }, m_tag{ actorDesc.tag }, m_transform { actorDesc.transform }, m_damping{actorDesc.damping}, m_velocity{actorDesc.vel}, m_lifespan{actorDesc.lifespan}, m_model{actorDesc.model} {}


        Actor(const Transform& transform) : m_transform{ transform } {}
        Actor(const Transform& transform, const Model& model) : m_transform{ transform }, m_model{ model } { }

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;

        virtual void OnCollision(Actor* other) {};

        const Transform& GetTeansform() const { return m_transform; }
        void SetPosition(const Vector2 position) { m_transform.pos = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.scale = scale; }

        const Vector2 GetVelocity() const { return m_velocity; }
        void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
        void AddVelocity(const Vector2& velocity) { m_velocity += velocity; }

        const std::string& GetName() { return m_name;  }
        const std::string& GetTag() { return m_tag;  }

        Scene* GetScene() { return m_scene; }

        float GetRadius() const;

        float GetDestroyed() const { return m_destroyed; }

        void SetDestroyed(bool destroy) { m_destroyed = destroy; }

        friend Scene;

    protected:
        std::string m_name;
        std::string m_tag;

        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
        float m_damping{ 0.0f };
        float m_lifespan{ 0.0f };
        bool m_destroyed{ false };

        Model m_model;
        Scene* m_scene{ nullptr };
    };
}
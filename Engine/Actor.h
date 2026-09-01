#pragma once

#include "Transform.h"
#include "Model.h"
#include "Resource.h"
#include "Object.h"
#include "Components/Component.h"
#include "json.h"
#include <string>
#include <memory>

namespace nu {
    class Scene;
    class Texture;

    struct ActorDesc {
        std::string name;
        std::string tag;
        Transform transform;
        Vector2 vel;
        float damping{ 0.0f };
        float lifespan{ 0 };
        res_t<Model> model;
        res_t<Texture> texture;
    };

    class Actor : public Object {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) : 
            m_tag{ actorDesc.tag }, 
            m_transform{ actorDesc.transform }, 
            m_velocity{ actorDesc.vel }, 
            m_damping{ actorDesc.damping }, 
            m_lifespan{ actorDesc.lifespan }
        { }

        Actor(const Actor& other);

        CLASS_PROTOTYPE(Actor)

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;
        virtual void Read(const json::value_t& value) override;

        virtual void OnCollision(Actor* other) {};

        const Transform& GetTransform() const { return m_transform; }
        void SetTransform(const Transform& transform) { m_transform = transform; }

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

        float GetRotation() const { return m_transform.rotation; }

        void SetDestroyed(bool destroy) { m_destroyed = destroy; }

        void AddComponent(std::unique_ptr<Component> component);

        template<std::derived_from<Component> T>
        T* GetComponent();

        friend Scene;

    protected:
        std::string m_tag;

        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
        float m_damping{ 0.0f };
        float m_lifespan{ 0.0f };
        bool m_destroyed{ false };

        std::vector<std::unique_ptr<Component>> m_components;

        Scene* m_scene{ nullptr };
    };

    template<std::derived_from<Component> T>
    inline T* Actor::GetComponent() {
        for (auto &component : m_components) {
            auto result = dynamic_cast<T*>(component.get());
            if (result) {
                return result;
            }
        }

        return nullptr;
    }
}
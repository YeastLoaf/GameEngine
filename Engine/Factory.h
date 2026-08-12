#pragma once

#include "Object.h"
#include "Singleton.h"

#include <memory>
#include <map>

namespace nu {
    class ICreater {
    public:
        virtual ~ICreater() = default;
        virtual std::unique_ptr<Object> Create() = 0;
    };

    template <typename T>
        requires std::derived_from<T, Object>
    class Creater : public ICreater {
    public:
        std::unique_ptr<Object> Create() override {
            return std::make_unique<T>();
        }
    };

    class Factory : public Singleton<Factory> {
    public:
        template <typename T>
            requires std::derived_from<T, Object>
        void Register(const std::string& name);

        template <typename T = class Object>
            requires std::derived_from<T, Object>
        std::unique_ptr<T> Create(const std::string& name);

    private:
        std::map<std::string, std::unique_ptr<ICreater>> m_registry;

    };

    template <typename T>
        requires std::derived_from<T, Object>
    inline void Factory::Register(const std::string& name) {
        std::string lowerName = ToLower(name);

        if (m_registry.contains(lowerName)) {
            std::cerr << "Object alreay registered: " << name << std::endl;
            return;
        }

        m_registry[lowerName] = std::make_unique<Creater<T>>();
    }

    template <typename T>
        requires std::derived_from<T, Object>
    inline std::unique_ptr<T> Factory::Create(const std::string& name) {
        std::string lowerName = ToLower(name);

        if (!m_registry.contains(lowerName)) {
            std::cerr << "Object not registered: " << name << std::endl;
            return std::unique_ptr<T>();
        }

        auto iter = m_registry.find(lowerName);

        // auto creater = m_registry[lowerName];
        // create unique pointer to object
        auto object = iter->second->Create();

        // check if object is derived from T
        T* derived = dynamic_cast<T*>(object.get());
        if (derived) {
            // release unique pointer ownership
            object.release();

            // create unique pointer with derived pointer
            return std::unique_ptr<T>(derived);
        }
        else {
            std::cerr << "Object not derived from type: " << name << std::endl;
        }

        return std::unique_ptr<T>();
    }
}
#pragma once
#include "Resource.h"
#include "Core/singleton.h"

#include <map>
#include <string>
#include <iostream>

namespace nu {
	class ResourceManager : public Singleton<ResourceManager> {
	public:

		template<typename T, typename ... Args>
		res_t<T> Get(const std::string&, Args&& ... args);

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};
	template<typename T, typename ...Args>
	inline res_t<T> ResourceManager::Get(const std::string& name, Args && ...args) {
		auto iter = m_resources.find(name);
		// check if resources exists
		if (iter != m_resources.end()) {
			auto base = iter->second;
			auto resource = std::dynamic_pointer_cast<T>(base);

			if (resource == nullptr) {
				std::cerr << "Resource type mismatch: " << name << std::endl;
				return res_t<T>();
			}

			return resource;
		}

		// resource doesn't exist, create and load
		res_t<T> resource = std::make_shared<T>();
		if (!resource->Load(name, std::forward<Args>(args)...)) {
			std::cerr << "Could not load resource: " << name << std::endl;
			return res_t<T>();
		}

		// store resource in map
		m_resources[name] = resource;

		return resource;
	}

	inline ResourceManager& Resources() { return ResourceManager::Instance(); }

	//ResourceManager resmanager;
}
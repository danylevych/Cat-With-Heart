#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>

//////////////////////////////////////////////////////
// \brief
//   Represents the holders for the resources of 
//   the appication.
// 
//////////////////////////////////////////////////////
template<typename Key, typename Value>
class ResourceHolder
{
private:
	std::map<Key, std::unique_ptr<Value>> resources;

public:
	ResourceHolder() = default;
	~ResourceHolder() = default;

public:
	void Load(const Key& key, const std::string& path)
	{
		std::unique_ptr<Value> resource { new Value() };
		if (!resource->loadFromFile(path))
		{
			throw std::runtime_error("Error loading resources: " + path);
		}

		resources[key] = std::move(resource);
	}
	
	std::unique_ptr<Value>& Get(const Key& key)
	{
		return resources[key];
	}

	const std::unique_ptr<Value>& Get(const Key& key) const
	{
		return resources[key];
	}
};

//////////////////////////////////////////////////////
// \brief
//   Partical typization for vector of resources.
// 
//////////////////////////////////////////////////////
template<typename Key, typename Type>
class ResourceHolder<Key, std::vector<Type>>
{
private:
	std::map<Key, std::vector<std::unique_ptr<Type>>> resources;

public:
	ResourceHolder() = default;
	~ResourceHolder() = default;

public:
	void Load(const Key& key, const std::string& path)
	{
		std::unique_ptr<Type> resource{ new Type() };

		if (!resource->loadFromFile(path))
		{
			throw std::runtime_error("Error loading resources: " + path);
		}

		resources[key].push_back(std::move(resource));
	}

	std::vector<std::unique_ptr<Type>>& Get(const Key& key)
	{
		return resources[key];
	}

	const std::vector<std::unique_ptr<Type>>& Get(const Key& key) const
	{
		return resources[key];
	}
};
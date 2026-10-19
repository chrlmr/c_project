#pragma once
#include <vector>
#include <unordered_map>

template<typename T, typename Param>
using Filter = bool(*)(const T&, Param);

template<typename T, typename Param>
std::vector<int> FindByFilter(
    const std::unordered_map<int, T>& objects,
    Filter<T, Param> filter,
    Param param)
{
    std::vector<int> result;

    for (const auto& item : objects) {
        if (filter(item.second, param))
            result.push_back(item.first);
    }

    return result;
}
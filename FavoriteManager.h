#pragma once
#include <vector>
#include <string>

class FavoriteManager
{
private:
    std::vector<std::string> fav;

public:
    void add(std::string city);
    void show();
};

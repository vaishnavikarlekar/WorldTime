#include "FavoriteManager.h"
#include <iostream>
using namespace std;

void FavoriteManager::add(string city)
{
    fav.push_back(city);
    cout << "  Added to favorites.\n";
}

void FavoriteManager::show()
{
    if (fav.empty()) { cout << "  No favorites saved.\n"; return; }
    cout << "\n--- Favorites ---\n";
    for (int i = 0; i < (int)fav.size(); i++)
        cout << "  " << i + 1 << "  " << fav[i] << "\n";
}

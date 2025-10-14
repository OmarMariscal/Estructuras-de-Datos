#include "list.hpp"
#include "recipe.hpp"


#include "iostream"
#include "fstream"

#include "../lib/nlohmann/json.hpp"


int main(){
    List<Recipe> recipeBook;
    std::ifstream file("prueba.json");
     
    nlohmann::json js;
    file >> js;

    if(!js.empty())
        recipeBook.fromJson(js.at("data"));

    getchar();
    return 0;
}

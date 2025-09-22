#include "recipebook.hpp"


void RecipeBook::setModify(){
    if(this->modify)
        this->modify = false;
    else
        this->modify = true;
}

void RecipeBook::updateTotalRecipes(){
    this->totalRecipes = this->recipes.getLastPosition() + 1;
}

bool RecipeBook::isValidRecipe(const Recipe& recipe){
    if( this->recipes.findDataL(recipe) != -1)
        return false;
    return true;
}

RecipeBook::RecipeBook() : recipes(*new List<Recipe>), recipeBookName("default"), filePath("default"), modify(false), totalRecipes(0) {}

RecipeBook::RecipeBook(const RecipeBook& other): recipes(other.recipes), recipeBookName(other.recipeBookName), filePath(other.filePath), modify(other.modify), totalRecipes(other.totalRecipes) {}

RecipeBook::RecipeBook(const List<Recipe>& r, const std::string& rBN, const std::string& fP, const bool& m, const int& tR) : recipes(r), recipeBookName(rBN), filePath(fP), modify(m) ,totalRecipes(tR) {}

List<Recipe> RecipeBook::getRecipes() const{
    return this->recipes;
}

std::string RecipeBook::getRecipeBookName() const{
    return this->recipeBookName;
}

std::string RecipeBook::getFilePath() const{
    return this->filePath;
}

bool RecipeBook::getModify() const{
    return this->modify;
}

int RecipeBook::getTotalRecipes() const{
    return this->totalRecipes;
}

void RecipeBook::setRecipes(const List<Recipe>& recipes){
    this->recipes = recipes;
}

void RecipeBook::setRecipeBookName(const std::string& recipeBookName){
    if(recipeBookName.empty())
        throw InputExceptions::EmptyString("Nombre del libro no puede estar vacio.");
    this->recipeBookName = recipeBookName;
}

void RecipeBook::setFilePath(const std::string& filePath){
    if(filePath.empty())
        throw InputExceptions::EmptyString("El filePath no puede estar vacio");
    this->filePath = filePath;
}

void RecipeBook::addRecipe(const Recipe& recipe){
    if(!this->isValidRecipe(recipe))
        throw RecipeBookExceptions::IdNotAvalible();
    this->recipes.insertSortedData(recipe);    
}

void RecipeBook::deleteRecipe(const Recipe& recipe){
    if(this->recipes.findDataL(recipe) == -1)
        throw RecipeBookExceptions::RecipeNotFound();
    this->recipes.deleteData(this->recipes.findDataL(recipe));
}



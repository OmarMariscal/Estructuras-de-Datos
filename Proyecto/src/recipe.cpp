#include "recipe.hpp"


Recipe::Recipe() : id(-1), recipeName("default"), category(DESAYUNO), preparationTime(-1), procedureList(*new List<std::string>), ingredientList(*new List<Ingredient>), creationDate(Date()) {}

Recipe::Recipe(const Recipe& other) : id(other.id), recipeName(other.recipeName), category(other.category), preparationTime(other.preparationTime), procedureList(other.procedureList), ingredientList(other.ingredientList), creationDate(other.creationDate) {}

Recipe::Recipe(const int& i, const std::string& rN, const Category& c, const int& pT, const List<std::string>& pL, const List<Ingredient>& iL, const Date& cD) : id(i), recipeName(rN), category(c), preparationTime(pT), procedureList(pL), ingredientList(iL), creationDate(cD) {}

int Recipe::getId() const{
    return this->id;
}

std::string Recipe::getRecipeName() const{
    return this->recipeName;
}

Category Recipe::getCategory() const{
    return this->category;
}

int Recipe::getPreparationTime() const{
    return this->preparationTime;
}

List<std::string> Recipe::getProcedureList() const{
    return this->procedureList;
}

List<Ingredient> Recipe::getIngredientList() const{
    return this->ingredientList;
}

std::string Recipe::toString() const{
    
}

void Recipe::setId(const int& id){
    if(id < 0)
        throw InputExceptions::NumberNotPositive("Id debe ser positivo");
    this->id = id;
}

void Recipe::setRecipeName(const std::string& recipeName){
    if(recipeName.empty())
        throw InputExceptions::EmptyString("El nombre de la receta no puede estar vacio.");
    this->recipeName = recipeName;
}

void Recipe::setCategory(const Category& category){
    this->category = category;
}

void Recipe::setPreparationTime(const int& preparationTime){
    if(preparationTime < 0)
        throw InputExceptions::NumberNotPositive("El tiempo de preparacion debe ser positivo.");
    this->preparationTime = preparationTime;
}

void Recipe::setProcedureList(const List<std::string>& procedureList){
    this->procedureList = procedureList;
}

void Recipe::setIngredientList(const List<Ingredient>& ingredientList){
    this->ingredientList = ingredientList;
}

void Recipe::addIngredient(const Ingredient& ingredient){
    if(this->ingredientList.findDataL(ingredient) != -1)
        throw RecipeExceptions::RepeatedIngredient();
    this->ingredientList.insertSortedData(ingredient);
}

void Recipe::deleteIngredient(const Ingredient& ingredient){
    if(this->ingredientList.findDataL(ingredient) == -1)
        throw RecipeExceptions::NonExistenIngredient();
    this->ingredientList.deleteData(this->ingredientList.findDataL(ingredient));
}

void Recipe::clearIngredients(){
    this->ingredientList.deleteAll();
}

Ingredient* Recipe::searchIngredient(const Ingredient& ingredient){
    if(this->ingredientList.findDataL(ingredient) == -1)
        return nullptr;
    return this->ingredientList.retrieve(this->ingredientList.findDataL(ingredient));
}

void Recipe::addStepToProcedure(const std::string& step){
    if(step.empty())
        throw InputExceptions::EmptyString("Procedimiento no puede estar vacio.");
    this->procedureList.insertSortedData(step);
}

void Recipe::deleteStepFromProcedure(const int& index){
    if(!this->procedureList.isValidPosition(index - 1))
        throw DataContainersExceptions::InvalidPosition("No existe el paso " + std::to_string(index+1));
    this->procedureList.deleteData(index-1);
}

void Recipe::clearProcedure(){
    this->procedureList.deleteAll();
}

bool Recipe::operator == (const Recipe& other){
    return this->id == other.id;
}

bool Recipe::operator < (const Recipe& other){
    return this->id < other.id;
}

bool Recipe::operator > (const Recipe& other){
    return this->id > other.id;
}

bool Recipe::operator <= (const Recipe& other){
    return this->id <= other.id;
}

bool Recipe::operator >= (const Recipe& other){
    return this->id >= other.id;
}

int Recipe::compareTo(const Recipe& other){
    return this->id - other.id;
}

int Recipe::compare(const Recipe& recipeA, const Recipe& recipeB){
    return recipeA.id - recipeB.id;
}

int Recipe::compareByName(const Recipe& other){
    return this->recipeName.compare(other.recipeName);
}

int Recipe::compareByCategory(const Recipe& other){
    return this->category - other.category;
}

int Recipe::compareByPreparationTime(const Recipe& other){
    return this->preparationTime - other.preparationTime;
}

int Recipe::compareByCreationDate(const Recipe& other){
    return this->creationDate.compareTo(other.creationDate);
}

Recipe& Recipe::operator = (const Recipe& other){
    this->id = other.id;
    this->recipeName = other.recipeName;
    this->category = other.category;
    this->preparationTime = other.preparationTime;
    this->procedureList = other.procedureList;
    this->ingredientList = other.ingredientList;
    this->creationDate = other.creationDate;

    return *this;
}

std::istream& operator >> (std::istream&, Ingredient&){
    //PENDIENTE: CREAR .JSON
}

std::ostream& operator << (std::ostream&, const Ingredient&){
    //PENDIENTE: CREAR .JSON
}

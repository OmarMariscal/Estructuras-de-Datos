#include "recipe.hpp"

Recipe::Recipe() : id(-1), recipeName("default"), category(DESAYUNO), preparationTime(-1),  creationDate(Date()) {}

Recipe::Recipe(const Recipe& other) : id(other.id), recipeName(other.recipeName), author(other.author), category(other.category), preparationTime(other.preparationTime), procedureList(other.procedureList), ingredientList(other.ingredientList), creationDate(other.creationDate) {}

Recipe::Recipe(const int& i, const std::string& rN, const Name& n, const Category& c, const int& pT, const SimpleLinkedList<StringWrapper>& pL, const SimpleLinkedList<Ingredient>& iL, const Date& cD) : id(i), recipeName(rN), author(n), category(c), preparationTime(pT), procedureList(pL), ingredientList(iL), creationDate(cD) {}

int Recipe::getId() const{
    return this->id;
}

std::string Recipe::getRecipeName() const{
    return this->recipeName;
}

Name Recipe::getAuthor() const{
    return this->author;
}

Category Recipe::getCategory() const{
    return this->category;
}

int Recipe::getPreparationTime() const{
    return this->preparationTime;
}

SimpleLinkedList<StringWrapper>& Recipe::getProcedureList(){
    return this->procedureList;
}

SimpleLinkedList<Ingredient>& Recipe::getIngredientList(){
    return this->ingredientList;
}

Date Recipe::getCreationDate() const{
    return this->creationDate;
}

std::string Recipe::toString(const std::string& format) const{
    std::ostringstream oss;
    
    if(format == "full"){
    oss << "\033[36mID de la Receta: \033[37m   " << this->id << std::endl;
    oss << "\033[36mFecha de Creación \033[37m: " << this->creationDate.toString() << std::endl;
    oss << "\033[36mNombre de la Receta \033[37m:   " << this->recipeName << std::endl;
    oss << "\033[36mAutor \033[37m:   " << this->author.toString() << std::endl;
    oss << "\033[36mCategoría \033[37m:   "; 
    switch(this->category){
        case DESAYUNO: oss << "Desayuno"; break;
        case COMIDA : oss << "Comida"; break;
        case CENA : oss << "Cena"; break;
        case NAVIDEÑO : oss << "Navideño"; break;
    }
    oss << std::endl;

    oss << "\033[36mTiempo \033[37m:    " << this->preparationTime << " minutos." << std::endl;
    oss << std::setfill('-');
    oss << std::setw(53) << "" << std::endl;
    oss << std::setfill(' ');
    oss << "🥑 \033[33mIngredientes \033[37m: " << std::endl;
    oss << this->ingredientList.toString();
    oss << std::setfill('-');
    oss << std::setw(53) << "" << std::endl;
    oss << std::setfill(' ');
    oss << "🧾 \033[35mProcedimiento \033[37m: " << std::endl;
    oss << this->procedureList.toString();
    }
    else if(format == "table") {
        // Truncar strings largos para que quepan en columnas
        std::string truncName = recipeName.length() > 22 ? 
                               recipeName.substr(0, 19) + "..." : recipeName;
        
        std::string truncAuthor = author.toString().length() > 18 ? 
                                 author.toString().substr(0, 15) + "..." : 
                                 author.toString();
        
        // Formato compacto con columnas alineadas
        oss << std::left
            << std::setw(5) << id << " | "
            << std::setw(22) << truncName << " | "
            << std::setw(12) << category << " | "
            << std::setw(18) << truncAuthor << " | "
            << std::right << std::setw(4) << preparationTime << " min | "
            << std::left << std::setw(6) << ingredientList.getTotalElements() << " ing.";
    }

    return oss.str();
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

void Recipe::setAuthor(const Name& author){
    this->author = author;
}

void Recipe::setCategory(const Category& category){
    this->category = category;
}

void Recipe::setPreparationTime(const int& preparationTime){
    if(preparationTime < 0)
        throw InputExceptions::NumberNotPositive("El tiempo de preparacion debe ser positivo.");
    this->preparationTime = preparationTime;
}

void Recipe::setProcedureList(const SimpleLinkedList<StringWrapper>& procedureList){
    this->procedureList = procedureList;
}

void Recipe::setIngredientList(const SimpleLinkedList<Ingredient>& ingredientList){
    this->ingredientList = ingredientList;
}

void Recipe::setCreationDate(const Date& date){
    this->creationDate = date;
}

void Recipe::addIngredient(const Ingredient& ingredient){
    if(this->ingredientList.findData(ingredient) != nullptr)
        throw RecipeExceptions::RepeatedIngredient();
    this->ingredientList.insertSortedData(ingredient);
}

void Recipe::deleteIngredient(const Ingredient& ingredient){
    if(this->ingredientList.findData(ingredient) == nullptr)
        throw RecipeExceptions::NonExistenIngredient();
    this->ingredientList.deleteData(this->ingredientList.findData(ingredient));
}

void Recipe::clearIngredients(){
    this->ingredientList.deleteAll();
}

Ingredient* Recipe::searchIngredient(const Ingredient& ingredient){
    if(this->ingredientList.findData(ingredient) == nullptr)
        return nullptr;
    return &this->ingredientList.retrieve(this->ingredientList.findData(ingredient));
}

void Recipe::addStepToProcedure(const std::string& step){
    if(step.empty())
        throw InputExceptions::EmptyString("Procedimiento no puede estar vacio.");
    this->procedureList.insertSortedData(step);
}

void Recipe::deleteStepFromProcedure(const int& index){
    if(index < 0 || index > this->procedureList.getTotalElements())
        throw DataContainersExceptions::InvalidPosition("No existe el paso " + std::to_string(index+1));
    this->procedureList.deleteData(this->procedureList.getNodeAt(index));
}

void Recipe::clearProcedure(){
    this->procedureList.deleteAll();
}

bool Recipe::operator == (const Recipe& other) const{
    return this->id == other.id;
}

bool Recipe::operator < (const Recipe& other) const{
    return this->id < other.id;
}

bool Recipe::operator > (const Recipe& other) const{
    return this->id > other.id;
}

bool Recipe::operator <= (const Recipe& other) const{
    return this->id <= other.id;
}

bool Recipe::operator >= (const Recipe& other) const{
    return this->id >= other.id;
}

int Recipe::compareTo(const Recipe& other){
    return this->id - other.id;
}

int Recipe::compare(const Recipe& recipeA, const Recipe& recipeB){
    return recipeA.id - recipeB.id;
}

int Recipe::compareByName(const Recipe& recipeA, const Recipe& recipeB){
    return recipeA.recipeName.compare(recipeB.recipeName);
}

int Recipe::compareByAuthor(const Recipe& recipeA, const Recipe& recipeB){
    return recipeA.author.compareTo(recipeB.author);
}

int Recipe::compareByCategory(const Recipe& recipeA, const Recipe& recipeB){
    return recipeA.category - recipeB.category;
}

int Recipe::compareByPreparationTime(const Recipe& recipeA, const Recipe& recipeB){
    return recipeA.preparationTime - recipeB.preparationTime;
}

int Recipe::compareByCreationDate(const Recipe& recipeA, const Recipe& recipeB){
    return recipeA.creationDate.compareTo(recipeB.creationDate);
}

nlohmann::json Recipe::toJson() const {
    nlohmann::json js{
        {"id", this->id},
        {"recipe name", this->recipeName},
        {"author", this->author.toJson()},
        {"category", this->category},
        {"preparation time", this->preparationTime},
        {"procedure list", this->procedureList.toJson()},
        {"ingredient list", this->ingredientList.toJson()},
        {"creation date", this->creationDate.toJson()},
    };
    return js;
}

void Recipe::fromJson(const nlohmann::json& js) {
    this->id = js.at("id").get<int>();
    this->recipeName = js.at("recipe name").get<std::string>();
    this->author.fromJson(js.at("author"));
    this->category = js.at("category").get<Category>();
    this->preparationTime = js.at("preparation time").get<int>();
    this->procedureList.fromJson(js.at("procedure list").at("data"));
    this->ingredientList.fromJson(js.at("ingredient list").at("data"));
    this->creationDate.fromJson(js.at("creation date"));
}

Recipe& Recipe::operator = (const Recipe& other){
    this->id = other.id;
    this->recipeName = other.recipeName;
    this->author = other.author;
    this->category = other.category;
    this->preparationTime = other.preparationTime;
    this->procedureList = other.procedureList;
    this->ingredientList = other.ingredientList;
    this->creationDate = other.creationDate;

    return *this;
}

#include "sortingbenchmark.hpp"

SortingBenchmark::SortingBenchmark() : originalList(), workingList(), results() {
    this->generateRandomData();
}

SortingBenchmark::SortingBenchmark(const List<Integer, ListConfigure::ARRAYSIZE>& o, const List<Integer, ListConfigure::ARRAYSIZE>& w, const List<BenchMarkResult, ListConfigure::NumberAlgorithms>& r) : originalList(o), workingList(w), results(r) {}
SortingBenchmark::SortingBenchmark(const SortingBenchmark& other) : originalList(other.originalList), workingList(other.workingList), results(other.results) {}

void SortingBenchmark::generateRandomData(const int& minimunData, const int& maximunData){
    this->originalList.deleteAll();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minimunData, maximunData);
    for(int i = 0; i < ListConfigure::ARRAYSIZE; i++)
        this->originalList.insertElement(Integer(dist(gen)), this->originalList.getLastPosition()+1);
    
    resetWorkingList();
}

void SortingBenchmark::resetWorkingList(){
    this->workingList = this->originalList;
}

void SortingBenchmark::clearResults(){
    this->results.deleteAll();
}

List<Integer, ListConfigure::ARRAYSIZE>& SortingBenchmark::getOriginalList(){
    return this->originalList;
}

List<Integer, ListConfigure::ARRAYSIZE>& SortingBenchmark::getWorkingList(){
    return this->workingList;
}

List <BenchMarkResult, ListConfigure::NumberAlgorithms>& SortingBenchmark::getResults(){
    return this->results;
}

void SortingBenchmark::runAllBenchmarks(){
    this->clearResults();
    this->runSingleBenchmark("BubbleSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {list.sortDataBubble(); });
    this->runSingleBenchmark("InsertSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {list.sortDataInsert(); });
    this->runSingleBenchmark("SelectSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {list.sortDataSelect(); });
    this->runSingleBenchmark("ShellSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {list.sortDataShell(); });
    this->runSingleBenchmark("MergeSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {list.sortDataMerge(); });
    this->runSingleBenchmark("QuickSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {list.sortDataQuick(); });
}

std::string SortingBenchmark::getResultsTable() const{
    std::ostringstream oss;
    int nameBorder(30), durationBorder(20), widthBorder(nameBorder + durationBorder*2);
    std::string tittle = "COMPARACION DE ALGORITMOS";

    //Cabecera
    oss << std::setfill('=') << std::setw(widthBorder) << "" << std::endl;
    oss << std::setfill(' ');
    oss << "|" << std::setw(((widthBorder - tittle.size()) / 2) + 2) << "" << tittle << std::setw((widthBorder - tittle.size()) / 2 - 2) << "|" << std::endl; 
    oss << std::setfill('=') << std::setw(widthBorder) << "" << std::endl;
    oss << std::setfill(' ');

    oss << "|Algoritmo" << std::setw(nameBorder - 10) << "" << "|Duracion en ms" << std::setw(durationBorder-15) << "" << "|Duracion en S" << std::setw(durationBorder-15) << "" << "|" <<std::endl;  
    oss << std::setfill('-') << std::setw(widthBorder) << "" << std::endl;
    oss << std::setfill(' ');

    oss << this->results.toString();

    oss << std::setfill('=') << std::setw(widthBorder) << "" << std::endl;
    oss << std::setfill(' ');

    return oss.str();
}

std::string SortingBenchmark::getSingleTable(const BenchMarkResult& benchmark){
    std::ostringstream oss;
    int widthBorder = 70;
    std::string tittle = "Resultados del BenchMark";
    oss << std::setfill('=') << std::setw(widthBorder) << "" << std::endl;
    oss << std::setfill(' ');
    oss << "|" << std::setw(((widthBorder - tittle.size()) / 2) + 2) << "" << tittle << std::setw((widthBorder - tittle.size()) / 2 - 2) << "|" << std::endl; 
    oss << std::setfill('=') << std::setw(widthBorder) << "" << std::endl;
    oss << std::setfill(' ');

    oss << "| Elementos totales del arreglo: " << ListConfigure::ARRAYSIZE << std::setw(widthBorder - 32 - std::to_string(ListConfigure::ARRAYSIZE).size()) << "|" <<std::endl;
    oss << std::setfill('-') << std::setw(widthBorder) << "" << std::endl;
    oss << std::setfill(' ');
    oss << "Algoritmo Usado: " << benchmark.getAlgorithName() << std::endl;
    oss << "Tiempo total de Ordenamiento en ms: " << benchmark.getDuration().count() << std::endl;
    oss << "Tiempo total de Ordenamiento en s: " << benchmark.getDuration().count() / 1000 << std::endl;
    oss << std::setfill('-') << std::setw(widthBorder) << "" << std::endl;
    oss << std::setfill(' ');

    return oss.str();
}

SortingBenchmark& SortingBenchmark::operator = (const SortingBenchmark& other){
    this->originalList = other.originalList;
    this->workingList = other.workingList;
    this->results = other.results;

    return *this;
}
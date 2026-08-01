// GeneticAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <stdio.h>
#include "Mutation.h"
#include "Crossover.h"

//parametry geneticsalgorithms i swapmutation - tam beda bledy tam sprawdz, teraz sparametryzuj prawdopodobienstwo krzyzowania

int totalDistance
(
    const std::vector<std::vector<int>>& adjacencyMatrix, 
    int path[], 
    int n
);

int** generateRandomPaths
(
    int totalDestinations, 
    int numberOfPaths
);

int** chooseSurvivors
(
    const std::vector<std::vector<int>>& adjacencyMatrix, 
    int** oldGeneration, 
    int numberOfPaths, 
    int numberOfCities
);

int* orderCrossover
(
    int* parentA, 
    int* parentB, 
    int parentLength
);

int** createNewGenerationOrderCrossover
(
    int** survivors, 
    int survivorsAmount, 
    int newGenerationSize, 
    int chromosomeLength, 
    double crossoverProbability
);

int** swapMutation
(
    int** generation, 
    int generationLength, 
    int chromosomeLength,
    double mutationProbability
);

std::vector<std::vector<int>> readAdjacencyMatrix
(
    std::string filename
);

int** inversionMutation
(
    int** generation, 
    int generationLength, 
    int chromosomeLength, 
    double mutationProbability
);

int** scrambleMutation
(
    int** generation, 
    int generationLength, 
    int chromosomeLength, 
    double mutationProbability
);

int* PMX
(
    int* parentA, 
    int* parentB, 
    int length
);

int* CX
(
    int* parentA, 
    int* parentB, 
    int length
);

int geneticsAlgorithm
(
    std::vector<std::vector<int>> adjacencyMatrix, 
    int populationSize,
    int survivorCount,
    int generations,
    double mutationProbability, 
    double crossoverProbability, 
    CrossoverType crossover,
    MutationType mutation
);


int** createNewGenerationPMX
(
    int** survivors, 
    int survivorsAmount, 
    int newGenerationSize, 
    int chromosomeLength, 
    double crossoverProbability
);

int** createNewGenerationCX
(
    int** survivors, 
    int survivorsAmount, 
    int newGenerationSize, 
    int chromosomeLength, 
    double crossoverProbability
);

bool writeResultsToFile
(
    std::string fileName, 
    std::string columnNameOne, 
    std::string columnNameTwo, 
    std::string columnNameThree,
    std::string columnNameFour

);

int main()
{
    int populationSize = 100;
    int survivorCount = 50;
    int generations = 5000;

    //OX dla 3 roznych macierzy i roznych wielkosci populacji-------------------------------
    auto begin = std::chrono::high_resolution_clock::now();
    auto adjacencyMatrix = readAdjacencyMatrix("ftv47.xml");
    auto res = geneticsAlgorithm(adjacencyMatrix, 
        populationSize,
        survivorCount,
        generations, 
        0.15,
        0.85, 
        CrossoverType::OX, 
        MutationType::SWAP);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", "czas", "liczba miast", "best cost", "Rozmiar populacji");
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "47", std::to_string(res), "100");

    populationSize = 200;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv47.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::OX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "47", std::to_string(res), "200");

    populationSize = 300;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv47.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::OX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "47", std::to_string(res), "300");

    //auto adjacencyMatrix = readAdjacencyMatrix("ftv44.xml");

    //int counter1 = 0;
    //int counter2 = 0;

    //for (int i = 0; i < adjacencyMatrix.size(); i++)
    //{
    //    for (int j = 0; j < adjacencyMatrix[i].size(); j++)
    //    {
    //        std::cout << adjacencyMatrix[i][j] << " ";
    //        counter2 ++;
    //    }

    //    std::cout << "\n";
    //    counter1 ++;

    //}

    //std::cout << "counter1: " << counter1 << " " << "counter2: " << counter2;

    populationSize = 100; 

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv170.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::OX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "170", std::to_string(res), "100");

    populationSize = 200;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv170.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::OX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "170", std::to_string(res), "200");


    populationSize = 300;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv170.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::OX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "170", std::to_string(res), "300");

    populationSize = 100;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("rbg403.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::OX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "403", std::to_string(res), "100");


    populationSize = 200;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("rbg403.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::OX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "403", std::to_string(res), "200");

    populationSize = 300;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("rbg403.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::OX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "403", std::to_string(res), "300");


    //PMX dla 3 roznych macierzy i 3 roznych wielkosci populacji-------------------------------

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv47.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::PMX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "47", std::to_string(res), "100");

    populationSize = 200;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv47.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::PMX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "47", std::to_string(res), "200");

    populationSize = 300;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv47.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::PMX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "47", std::to_string(res), "300");


    populationSize = 100;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv170.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::PMX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "170", std::to_string(res), "100");

    populationSize = 200;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv170.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::PMX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "170", std::to_string(res), "200");


    populationSize = 300;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv170.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::PMX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "170", std::to_string(res), "300");

    populationSize = 100;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("rbg403.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::PMX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "403", std::to_string(res), "100");


    populationSize = 200;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("rbg403.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::PMX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "403", std::to_string(res), "200");

    populationSize = 300;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("rbg403.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::PMX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "403", std::to_string(res), "300");


    //CX dla 3 roznych macierzy i 3 roznych wielkosci populacji-------------------------------

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv47.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::CX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "47", std::to_string(res), "100");

    populationSize = 200;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv47.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::CX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "47", std::to_string(res), "200");

    populationSize = 300;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv47.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::CX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "47", std::to_string(res), "300");


    populationSize = 100;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv170.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::CX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "170", std::to_string(res), "100");

    populationSize = 200;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv170.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::CX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "170", std::to_string(res), "200");


    populationSize = 300;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("ftv170.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::CX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "170", std::to_string(res), "300");

    populationSize = 100;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("rbg403.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::CX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "403", std::to_string(res), "100");


    populationSize = 200;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("rbg403.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::CX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "403", std::to_string(res), "200");

    populationSize = 300;

    begin = std::chrono::high_resolution_clock::now();
    adjacencyMatrix = readAdjacencyMatrix("rbg403.xml");
    res = geneticsAlgorithm(adjacencyMatrix,
        populationSize,
        survivorCount,
        generations,
        0.15,
        0.85,
        CrossoverType::CX,
        MutationType::SWAP);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    writeResultsToFile("data.csv", std::to_string(elapsed.count()), "403", std::to_string(res), "300");

    return 0;
}
 


int geneticsAlgorithm(std::vector<std::vector<int>> adjacencyMatrix, 
    int populationSize,
    int survivorCount,
    int generations, 
    double mutationProbability,
    double crossoverProbability, 
    CrossoverType crossover, 
    MutationType mutation)
{

    int cities = adjacencyMatrix.size();

    std::cout << "Miast: "
        << cities
        << "\n";

    std::srand(std::time(nullptr));

    int** paths = generateRandomPaths(cities, populationSize);
    int globalBest = std::numeric_limits<int>::max();

    for (int i = 0; i < generations; i++)
    {
        int best = totalDistance(adjacencyMatrix, paths[0], cities);

        for (int j = 1; j < populationSize; j++)
        {
            best = std::min(
                best,
                totalDistance(adjacencyMatrix, paths[j], cities)
            );
        }

        if (best < globalBest)
        {
            globalBest = best;
        }

        std::cout << "Generacja "
            << i
            << " najlepszy koszt = "
            << best
            << "\n";

        int** survivors = chooseSurvivors(adjacencyMatrix, paths, populationSize, cities);

        int** newGeneration = nullptr;

        switch (crossover)
        {
        case CrossoverType::OX:
            newGeneration =
                createNewGenerationOrderCrossover(
                    survivors, survivorCount, populationSize, cities,
                    crossoverProbability);
            break;

        case CrossoverType::PMX:
            newGeneration =
                createNewGenerationPMX(
                    survivors, survivorCount, populationSize, cities,
                    crossoverProbability);
            break;

        case CrossoverType::CX:
            newGeneration =
                createNewGenerationCX(
                    survivors, survivorCount, populationSize, cities,
                    crossoverProbability);
            break;
        }

        int** mutatedPaths = nullptr;

        switch (mutation)
        {
        case MutationType::SWAP:
            mutatedPaths =
                swapMutation(
                    newGeneration, populationSize, cities,
                    mutationProbability);
            break;

        case MutationType::INVERSION:
            mutatedPaths =
                inversionMutation(
                    newGeneration, populationSize, cities,
                    mutationProbability);
            break;

        case MutationType::SCRAMBLE:
            mutatedPaths =
                scrambleMutation(
                    newGeneration, populationSize, cities,
                    mutationProbability);
            break;
        }

        for (int i = 0; i < populationSize; i++)
        {
            delete[] paths[i];
        }
        delete[] paths;


        paths = mutatedPaths;


        for (int i = 0; i < survivorCount; i++)
        {
            delete[] survivors[i];
        }
        delete[] survivors;


        for (int i = 0;i < populationSize;i++)
        {
            delete[] newGeneration[i];
        }
        delete[] newGeneration;
    }

    for (int i = 0; i < populationSize; i++)
    {
        delete[] paths[i];
    }
    delete[] paths;

    std::cout << "Best cost = "
        << globalBest
        << "\n";

    return  globalBest;

}



void saveDataToFile(std::vector<std::vector<std::string>> data)
{
    std::ofstream file("data.csv");

    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i != row.size() - 1) file << ",";
        }
        file << "\n";
    }

    file.close();
    std::cout << "CSV file created successfully." << std::endl;

}

//
//std::vector<std::vector<int>> readAdjacencyMatrix(std::string filename)
//{
//    std::ifstream file(filename);
//    if (!file.is_open())
//    {
//        std::cout << "File can't be open!\n";
//        return {};
//    }
//
//    std::vector<std::vector<int>> adjacencyMatrix;
//    std::vector<int> row;
//
//    std::string line;
//
//    while (std::getline(file, line))
//    {
//        size_t pos = line.find("cost=\"");
//
//        if (pos != std::string::npos)
//        {
//            pos += 6;
//
//            size_t end = line.find("\"", pos);
//
//            double cost = std::stod(line.substr(pos, end - pos));
//
//            row.push_back((int)cost);
//        }
//
//        if (line.find("</vertex>") != std::string::npos)
//        {
//            adjacencyMatrix.push_back(row);
//            row.clear();
//        }
//    }
//
//    return adjacencyMatrix;
//}

std::vector<std::vector<int>> readAdjacencyMatrix(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "File can't be open!\n";
        return {};
    }

    std::vector<std::vector<int>> rows;
    std::vector<int> row;
    std::string line;

    while (std::getline(file, line))
    {
        size_t pos = line.find("cost=\"");

        if (pos != std::string::npos)
        {
            pos += 6;
            size_t end = line.find("\"", pos);

            double cost = std::stod(line.substr(pos, end - pos));
            row.push_back((int)cost);
        }

        if (line.find("</vertex>") != std::string::npos)
        {
            rows.push_back(row);
            row.clear();
        }
    }

    int n = rows.size();

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        int k = 0;

        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
            }
            else
            {
                matrix[i][j] = rows[i][k++];
            }
        }
    }

    return matrix;
}

int totalDistance(const std::vector<std::vector<int>>& adjacencyMatrix, int path[], int n) {
    
    int sum = 0;

    for (int i = 0; i < n-1; i++)
    {

        sum += adjacencyMatrix[path[i]][path[i + 1]];
    }

    sum += adjacencyMatrix[path[n - 1]][path[0]];

    return sum;
}

int** generateRandomPaths(int totalDestinations, int numberOfPaths) {
    //POTEM PAMIETAJ O delete[] path; ZEBY NIE BYLO WYCIEKU PAMIECI
    // for (int i = 0; i < numberOfPaths; i++)
    //{
    //    delete[] paths[i];
    //}
    //delete[] paths;

    
    int* initialPath = new int[totalDestinations];
    int** paths = new int*[numberOfPaths];
   

    //czy tu nie powinno być po = i+1? ogarnij te graniczne warunki
    for (int i = 1; i < totalDestinations; i++)
    {
        initialPath[i] = i;
    }

    
    std::random_device rd;
    std::mt19937 generator(rd());

    initialPath[0] = 0;

    for (int i = 0; i < numberOfPaths; i++)
    {

        paths[i] = new int[totalDestinations];
        std::shuffle(initialPath+1, initialPath + totalDestinations, generator);
        for (int j = 0; j < totalDestinations; j++)
        {
            paths[i][j] = initialPath[j];
        } 
    }


    delete[] initialPath;

    return paths;
}

int** chooseSurvivors(const std::vector<std::vector<int>>& adjacencyMatrix, int** oldGeneration, int numberOfPaths, int numberOfCities) {

    if (numberOfPaths % 2 != 0)
    {
        numberOfPaths--;
    }

    int midway = numberOfPaths / 2;

    int** survivors = new int* [midway];



    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(oldGeneration, oldGeneration + numberOfPaths, generator);

    

    for (int i = 0; i < midway; i++)
    {
        survivors[i] = new int[numberOfCities];

        if (totalDistance(adjacencyMatrix, oldGeneration[i], numberOfCities) < totalDistance(adjacencyMatrix, oldGeneration[i + midway], numberOfCities))
        {
            for (int j = 0; j < numberOfCities; j++)
            {
                survivors[i][j] = oldGeneration[i][j];
            }
        }
        else
        {
            for (int j = 0; j < numberOfCities; j++)
            {
                survivors[i][j] = oldGeneration[i + midway][j];
            }
        }
    }


    return survivors;
}

//PRZETESTUJ


int** createNewGenerationOrderCrossover(int** survivors, int survivorsAmount, int newGenerationSize, int chromosomeLength, double crossoverProbability)
{
    int** newGeneration = new int* [newGenerationSize];

    for (int i = 0; i < newGenerationSize; i++)
    {
        int parentA = std::rand() % survivorsAmount;
        int parentB;

        do
        {
            parentB = std::rand() % survivorsAmount;
        } while (parentA == parentB);
        
        if ((double)std::rand() / RAND_MAX < crossoverProbability)
        {
            newGeneration[i] = orderCrossover(
                survivors[parentA],
                survivors[parentB],
                chromosomeLength);
        }
        else
        {
            // bez krzyżowania - kopiujemy rodzica
            newGeneration[i] = new int[chromosomeLength];

            for (int j = 0; j < chromosomeLength; j++)
            {
                newGeneration[i][j] = survivors[parentA][j];
            }
        }

    }

    return newGeneration;
}

int** createNewGenerationCX(int** survivors, int survivorsAmount, int newGenerationSize, int chromosomeLength, double crossoverProbability)
{
    int** newGeneration = new int* [newGenerationSize];

    for (int i = 0; i < newGenerationSize; i++)
    {
        int parentA = std::rand() % survivorsAmount;
        int parentB;

        do
        {
            parentB = std::rand() % survivorsAmount;
        } while (parentA == parentB);

        if ((double)std::rand() / RAND_MAX < crossoverProbability)
        {
            newGeneration[i] = CX(
                survivors[parentA],
                survivors[parentB],
                chromosomeLength);
        }
        else
        {
            // bez krzyżowania - kopiujemy rodzica
            newGeneration[i] = new int[chromosomeLength];

            for (int j = 0; j < chromosomeLength; j++)
            {
                newGeneration[i][j] = survivors[parentA][j];
            }
        }

    }

    return newGeneration;
}

int** createNewGenerationPMX(int** survivors, int survivorsAmount, int newGenerationSize, int chromosomeLength, double crossoverProbability)
{
    int** newGeneration = new int* [newGenerationSize];

    for (int i = 0; i < newGenerationSize; i++)
    {
        int parentA = std::rand() % survivorsAmount;
        int parentB;

        do
        {
            parentB = std::rand() % survivorsAmount;
        } while (parentA == parentB);

        newGeneration[i] = PMX(survivors[parentA], survivors[parentB], chromosomeLength);

    }

    return newGeneration;
}

//PRZETESTUJ


bool writeResultsToFile(std::string fileName, std::string columnNameOne, std::string columnNameTwo, std::string columnNameThree, std::string columnNameFour)
{
    
    std::ofstream file;
    file.open(fileName, std::ios_base::app);
    file << columnNameOne << "," << columnNameTwo << "," << columnNameThree << std::endl;
    file.close();

    return true;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

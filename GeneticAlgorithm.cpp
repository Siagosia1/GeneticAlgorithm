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

int totalDistance(const std::vector<std::vector<int>>& adjacencyMatrix, int path[], int n);
int** generateRandomPaths(int totalDestinations, int numberOfPaths);
int** chooseSurvivors(const std::vector<std::vector<int>>& adjacencyMatrix, int** oldGeneration, int numberOfPaths, int numberOfCities);
int* orderCrossover(int* parentA, int* parentB, int parentLength);
int** createNewGenerationOrderCrossover(int** survivors, int survivorsAmount, int newGenerationSize, int chromosomeLength);
int** swapMutation(int** generation, int generationLength, int chromosomeLength);
std::vector<std::vector<int>> readAdjacencyMatrix(std::string filename);
void inversionMutation(int* chromosome, int length);
void scrambleMutation(int* chromosome, int length);
int* PMX(int* parentA, int* parentB, int length);
int* CX(int* parentA, int* parentB, int length);

int geneticsAlgorithmOCSWAP(std::vector<std::vector<int>> adjacencyMatrix);
int geneticsAlgorithmPMXSWAP(std::vector<std::vector<int>> adjacencyMatrix);
int geneticsAlgorithmCXSWAP(std::vector<std::vector<int>> adjacencyMatrix);

int geneticsAlgorithmOCSWAP(std::vector<std::vector<int>> adjacencyMatrix);
int geneticsAlgorithmOCINV(std::vector<std::vector<int>> adjacencyMatrix);
int geneticsAlgorithmOCSCR(std::vector<std::vector<int>> adjacencyMatrix);

int geneticsAlgorithmPMXINV(std::vector<std::vector<int>> adjacencyMatrix);
int geneticsAlgorithmCXSCR(std::vector<std::vector<int>> adjacencyMatrix);


int** createNewGenerationPMX(int** survivors, int survivorsAmount, int newGenerationSize, int chromosomeLength);
int** createNewGenerationCX(int** survivors, int survivorsAmount, int newGenerationSize, int chromosomeLength);



int main()
{
    auto begin = std::chrono::high_resolution_clock::now();

    auto adjacencyMatrix = readAdjacencyMatrix("ftv44.xml");

    std::cout << geneticsAlgorithmOCSWAP(adjacencyMatrix);
   
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}



int geneticsAlgorithmOCSWAP(std::vector<std::vector<int>> adjacencyMatrix)
{

    int cities = adjacencyMatrix.size();

    std::cout << "Miast: "
        << cities
        << "\n";

    std::srand(std::time(nullptr));

    int** paths = generateRandomPaths(cities, 7);
    int globalBest = std::numeric_limits<int>::max();

    for (int i = 0; i < 1000; i++)
    {
        int best = totalDistance(adjacencyMatrix, paths[0], cities);

        for (int j = 1; j < 7; j++)
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

        int** survivors = chooseSurvivors(adjacencyMatrix, paths, 7, cities);

        int** newGeneration = createNewGenerationOrderCrossover(survivors, 3, 7, cities);

        int** mutatedPaths = swapMutation(newGeneration, 7, cities);

        for (int i = 0; i < 7; i++)
        {
            delete[] paths[i];
        }
        delete[] paths;


        paths = mutatedPaths;


        for (int i = 0; i < 3; i++)
        {
            delete[] survivors[i];
        }
        delete[] survivors;


        for (int i = 0;i < 7;i++)
        {
            delete[] newGeneration[i];
        }
        delete[] newGeneration;
    }

    for (int i = 0; i < 7; i++)
    {
        delete[] paths[i];
    }
    delete[] paths;

    std::cout << "Best cost = "
        << globalBest
        << "\n";

    return globalBest, cities;

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


std::vector<std::vector<int>> readAdjacencyMatrix(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "File can't be open!\n";
        return {};
    }

    std::vector<std::vector<int>> adjacencyMatrix;
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
            adjacencyMatrix.push_back(row);
            row.clear();
        }
    }

    return adjacencyMatrix;
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
int* orderCrossover(int* parentA, int* parentB, int parentLength)
{
    
    int start = 1 + std::rand() % (parentLength - 1);
    int finish = start + std::rand() % (parentLength - start);

    int fragmentSize = finish - start + 1;
    int* subPathFromA = new int[fragmentSize];

    for (int i = 0; i < fragmentSize; i++)
    {
        subPathFromA[i] = parentA[start + i];
    }

    int* remainingPathFromB = new int[parentLength - fragmentSize];
    int remainingSize = 0;

    for (int i = 0; i < parentLength; i++)
    {
        bool found = false;

        for (int j = 0; j < fragmentSize; j++)
        {
            if (parentB[i] == subPathFromA[j])
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            remainingPathFromB[remainingSize++] = parentB[i];
        }
    }

    int* offspring = new int[parentLength];

    int subIndex = 0;
    int remainingIndex = 0;

    for (int i = 0; i < parentLength; i++)
    {
        if (i >= start && i <= finish)
        {
            offspring[i] = subPathFromA[subIndex++];
        }
        else
        {
            offspring[i] = remainingPathFromB[remainingIndex++];
        }
    }

    delete[] subPathFromA;
    delete[] remainingPathFromB;

    return offspring;
}

int* CX(int* parentA,
    int* parentB,
    int length)
{
    int* child = new int[length];

    bool* visited = new bool[length];

    for (int i = 0; i < length; i++)
    {
        visited[i] = false;
    }

    child[0] = 0;

    int index = 1;

    while (!visited[index])
    {
        visited[index] = true;

        child[index] = parentA[index];

        int value = parentB[index];

        for (int i = 1; i < length; i++)
        {
            if (parentA[i] == value)
            {
                index = i;
                break;
            }
        }
    }

    for (int i = 1; i < length; i++)
    {
        if (!visited[i])
        {
            child[i] = parentB[i];
        }
    }

    delete[] visited;

    return child;
}

int* PMX(int* parentA,
    int* parentB,
    int length)
{
    int* child = new int[length];

    for (int i = 0; i < length; i++)
    {
        child[i] = -1;
    }

    child[0] = 0;

    int start = 1 + std::rand() % (length - 1);
    int end = 1 + std::rand() % (length - 1);

    if (start > end)
    {
        std::swap(start, end);
    }

    for (int i = start; i <= end; i++)
    {
        child[i] = parentA[i];
    }

    for (int i = start; i <= end; i++)
    {
        int gene = parentB[i];

        bool exists = false;

        for (int j = 0; j < length; j++)
        {
            if (child[j] == gene)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            int position = i;

            while (child[position] != -1)
            {
                int mapped = parentA[position];

                for (int k = 0; k < length; k++)
                {
                    if (parentB[k] == mapped)
                    {
                        position = k;
                        break;
                    }
                }
            }

            child[position] = gene;
        }
    }

    for (int i = 1; i < length; i++)
    {
        if (child[i] == -1)
        {
            child[i] = parentB[i];
        }
    }

    return child;
}

int** createNewGenerationOrderCrossover(int** survivors, int survivorsAmount, int newGenerationSize, int chromosomeLength)
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
        
        newGeneration[i] = orderCrossover(survivors[parentA], survivors[parentB], chromosomeLength);

    }

    return newGeneration;
}

int** createNewGenerationCX(int** survivors, int survivorsAmount, int newGenerationSize, int chromosomeLength)
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

        newGeneration[i] = CX(survivors[parentA], survivors[parentB], chromosomeLength);

    }

    return newGeneration;
}

int** createNewGenerationPMX(int** survivors, int survivorsAmount, int newGenerationSize, int chromosomeLength)
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
int** swapMutation(int** generation, int generationLength, int chromosomeLength) 
{
    int** mutatedGeneration = new int* [generationLength];
    

    for (int i = 0; i < generationLength; i++)
    {
        mutatedGeneration[i] = new int[chromosomeLength];

        for (int j = 0; j < chromosomeLength; j++)
        {
            mutatedGeneration[i][j] = generation[i][j];
        }

        if (std::rand() % 100 < 10)
        {
            int index1 = 1 + std::rand() % (chromosomeLength - 1);
            int index2 = 1 + std::rand() % (chromosomeLength - 1);

            std::swap(
                mutatedGeneration[i][index1],
                mutatedGeneration[i][index2]
            );
        }
    }

    return mutatedGeneration;
}


void scrambleMutation(int* chromosome, int length)
{
    int start = 1 + std::rand() % (length - 1);
    int end = 1 + std::rand() % (length - 1);

    if (start > end)
    {
        std::swap(start, end);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(
        chromosome + start,
        chromosome + end + 1,
        gen
    );
}

void inversionMutation(int* chromosome, int length)
{
    int start = 1 + std::rand() % (length - 1);
    int end = 1 + std::rand() % (length - 1);

    if (start > end)
    {
        std::swap(start, end);
    }

    while (start < end)
    {
        std::swap(
            chromosome[start],
            chromosome[end]
        );

        start++;
        end--;
    }
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

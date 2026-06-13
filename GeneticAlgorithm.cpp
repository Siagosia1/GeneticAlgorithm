// GeneticAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

int totalDistance(int adjacencyMatrix[4][4], int path[], int n);
int** generateRandomPaths(int totalDestinations, int numberOfPaths);
int** chooseSurvivors(int adjacencyMatrix[4][4], int** oldGeneration, int numberOfPaths, int numberOfCities);

int main()
{
    std::srand(std::time(nullptr));

    //DODAJ 0 JAKO PIERWSZA POZYCJE W TABLICY !!!!!!!!!!!!!!!!!!!!!!!
    //minimalny koszt = 35 dla tej macierzy
    int adjacencyMatrix[4][4] =
    {   
        {0, 10, 15, 20},
        {9, 0, 5, 10},
        {6, 13, 0, 12 },
        {8, 8, 9, 0}
     };

    int path[] = { 0, 1, 2, 3 };
    int n = 4;

    int total = totalDistance(adjacencyMatrix, path, n);

    int** paths = generateRandomPaths(4, 7);

    std::cout << total;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << paths[i][j] << " ";
        }
        std::cout << "\n";
    }

    int** survivors = chooseSurvivors(adjacencyMatrix, paths, 7, 4);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << survivors[i][j] << " ";
        }
        std::cout << "\n";
    }

    for (int i = 0; i < 7; i++)
    {
        delete[] paths[i];
    }
    delete[] paths;

    for (int i = 0; i < 3; i++)
    {
        delete[] survivors[i];
    }
    delete[] survivors;

    return 0;
}

int totalDistance(int adjacencyMatrix [4][4], int path[], int n) {
    
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

    

    std::mt19937 generator(time(0));

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

int** chooseSurvivors(int adjacencyMatrix[4][4], int** oldGeneration, int numberOfPaths, int numberOfCities) {

    if (numberOfPaths % 2 != 0)
    {
        numberOfPaths--;
    }

    int midway = numberOfPaths / 2;

    int** survivors = new int* [midway];



    std::mt19937 generator(time(0));

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
int* createOffspring(int* parentA, int* parentB, int parentLength)
{
    
    int start = std::rand() % parentLength;
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

//PRZETESTUJ
int** applyMutations(int** generation, int generationLength, int chromosomeLength) 
{
    int** mutatedGeneration = new int* [generationLength];
    int index1, index2;

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


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

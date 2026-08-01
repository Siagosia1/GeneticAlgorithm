#include <random>
#include "Mutation.h"


int** swapMutation(int** generation, int generationLength, int chromosomeLength, double mutationProbability)
{
    int** mutatedGeneration = new int* [generationLength];


    for (int i = 0; i < generationLength; i++)
    {
        mutatedGeneration[i] = new int[chromosomeLength];

        for (int j = 0; j < chromosomeLength; j++)
        {
            mutatedGeneration[i][j] = generation[i][j];
        }

        if ((double)(std::rand() % 100) / 100 < mutationProbability)
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


int** scrambleMutation(
    int** generation,
    int generationLength,
    int chromosomeLength,
    double mutationProbability)
{
    int** mutatedGeneration = new int* [generationLength];

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < generationLength; i++)
    {
        mutatedGeneration[i] = new int[chromosomeLength];

        for (int j = 0; j < chromosomeLength; j++)
        {
            mutatedGeneration[i][j] = generation[i][j];
        }

        if ((double)(std::rand() % 100) / 100 < mutationProbability)
        {
            int start = 1 + std::rand() % (chromosomeLength - 1);
            int end = 1 + std::rand() % (chromosomeLength - 1);

            if (start > end)
            {
                std::swap(start, end);
            }

            std::shuffle(
                mutatedGeneration[i] + start,
                mutatedGeneration[i] + end + 1,
                gen
            );
        }
    }

    return mutatedGeneration;
}

int** inversionMutation(
    int** generation,
    int generationLength,
    int chromosomeLength,
    double mutationProbability)
{
    int** mutatedGeneration = new int* [generationLength];

    for (int i = 0; i < generationLength; i++)
    {
        mutatedGeneration[i] = new int[chromosomeLength];

        for (int j = 0; j < chromosomeLength; j++)
        {
            mutatedGeneration[i][j] = generation[i][j];
        }

        if ((double)(std::rand() % 100) / 100 < mutationProbability)
        {
            int start = 1 + std::rand() % (chromosomeLength - 1);
            int end = 1 + std::rand() % (chromosomeLength - 1);

            if (start > end)
            {
                std::swap(start, end);
            }

            while (start < end)
            {
                std::swap(
                    mutatedGeneration[i][start],
                    mutatedGeneration[i][end]
                );

                start++;
                end--;
            }
        }
    }

    return mutatedGeneration;
}
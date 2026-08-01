#include <random>
#include "Crossover.h"


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

    int index = 0;

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
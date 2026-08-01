#pragma once

enum class MutationType
{
    SWAP,
    INVERSION,
    SCRAMBLE
};

int** swapMutation(
    int** generation,
    int generationLength,
    int chromosomeLength,
    double mutationProbability);

int** inversionMutation(
    int** generation,
    int generationLength,
    int chromosomeLength,
    double mutationProbability);

int** scrambleMutation(
    int** generation,
    int generationLength,
    int chromosomeLength,
    double mutationProbability);

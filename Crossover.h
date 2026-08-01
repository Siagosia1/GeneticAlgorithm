#pragma once

enum class CrossoverType
{
    OX,
    PMX,
    CX
};

int* orderCrossover(
    int* parentA,
    int* parentB,
    int parentLength);

int* PMX(
    int* parentA,
    int* parentB,
    int length);

int* CX(
    int* parentA,
    int* parentB,
    int length);
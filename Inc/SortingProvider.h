#ifndef SORTINGPROVIDER_H_INCLUDED
#define SORTINGPROVIDER_H_INCLUDED

#include<iostream>
#include<vector>

class SortingProvider{

private:

    const int maxSortNum = 12;
    double maximumValue = 0;
    double minimumValue = 0;

    std::string usedSortName;

    std::vector<double> theOriginalData;
    std::vector<double> theActiveData;

    std::vector<int> singleIndexValues;
    std::vector<std::vector<int>> theActiveDataIndexing;

public:

    const int SELECTION_SORT = 0;
    const int BUBBLE_SORT = 1;
    const int INSERTION_SORT = 2;
    const int MERGE_SORT = 3;
    const int HEAP_SORT = 4;
    const int QUICK_SORT = 5;
    const int RADIX_SORT = 6;
    const int BUCKET_SORT = 7;
    const int SHELL_SORT = 8;
    const int COMB_SORT = 9;
    const int PIGEONHOLE_SORT = 10;
    const int CYCLE_SORT = 11;
    const int COCKTAIL_SORT = 12;

    SortingProvider();
    ~SortingProvider();

    void setOriginalData(std::vector<double>&);

    void setupSort();

    void performSelectionSort();
    void performBubbleSort();
    void performInsertionSort();

    void mergeArray(int, int, int);
    void mergeSortStage(int, int);
    void mergeSortIndexStage(int, int);
    void performMergeSort();

    void heapifyFunc(int, int);
    void performHeapSort();

    int partitionFunc(int, int);
    void quickSortStage(int, int);
    void performQuickSort();

    void performRadixSort();
    void performBucketSort();
    void performShellSort();
    void performCombSort();
    void performPigeonholeSort();
    void performCycleSort();
    void performCocktailSort();

    void performSort(int);

    std::vector<double>& getOriginalData();
    std::vector<double>& getSortedData();
    std::vector<std::vector<int>>& getDataIndexing();

    int getMaxSortNum();
    double getMinimumValue();
    double getMaximumValue();

    std::string getSortName();
};


#endif // SORTINGPRESENTER_H_INCLUDED

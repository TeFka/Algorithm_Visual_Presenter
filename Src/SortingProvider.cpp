#include "SortingProvider.h"


SortingProvider::SortingProvider()
{

}
SortingProvider::~SortingProvider()
{


}

void SortingProvider::setOriginalData(std::vector<double>& newData)
{

    this->theOriginalData.clear();
    for(int i = 0; i<newData.size(); i++)
    {
        if(this->maximumValue<newData[i])
        {
            this->maximumValue = newData[i];
        }

        this->theOriginalData.push_back(newData[i]);
    }

    this->minimumValue = this->maximumValue;
    for(int i = 0; i<newData.size(); i++)
    {
        if(this->minimumValue>newData[i])
        {
            this->minimumValue = newData[i];
        }
    }

}

void SortingProvider::setupSort()
{

    this->theActiveDataIndexing.clear();
    this->theActiveData.clear();
    this->singleIndexValues.clear();

    for(int i = 0; i<this->theOriginalData.size(); i++)
    {
        this->singleIndexValues.push_back(i);
    }

    for(int i = 0; i<this->theOriginalData.size(); i++)
    {
        this->theActiveData.push_back(this->theOriginalData[i]);
    }

    this->theActiveDataIndexing.push_back(this->singleIndexValues);
}
void SortingProvider::performSelectionSort()
{

    this->setupSort();

    int min_idx;

    // One by one move boundary of unsorted subarray
    for (int i = 0; i < this->theActiveData.size()-1; i++)
    {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (int j = i+1; j < this->theActiveData.size(); j++)
        {
            if (this->theActiveData[j] < this->theActiveData[min_idx])
            {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first elements
        double temp = this->theActiveData[min_idx];
        this->theActiveData[min_idx] = this->theActiveData[i];
        this->theActiveData[i] = temp;

        //swap indexes
        int tempIndex = this->singleIndexValues[min_idx];
        this->singleIndexValues[min_idx] = this->singleIndexValues[i];
        this->singleIndexValues[i] = tempIndex;

        this->theActiveDataIndexing.push_back(this->singleIndexValues);
    }

}

void SortingProvider::performBubbleSort()
{
    this->setupSort();

    for (int i = 0; i < this->theActiveData.size() - 1; i++)
    {

        // Last i elements are already
        // in place
        for (int j = 0; j < this->theActiveData.size() - i - 1; j++)
        {
            if (this->theActiveData[j] > this->theActiveData[j + 1])
            {

                // Swap the found minimum element with the first elements
                double temp = this->theActiveData[j];
                this->theActiveData[j] = this->theActiveData[j + 1];
                this->theActiveData[j + 1] = temp;

                //swap indexes
                int tempIndex = this->singleIndexValues[j];
                this->singleIndexValues[j] = this->singleIndexValues[j + 1];
                this->singleIndexValues[j + 1] = tempIndex;
            }
        }

        this->theActiveDataIndexing.push_back(this->singleIndexValues);
    }

}

void SortingProvider::performInsertionSort()
{
    this->setupSort();
    double key;
    int  keyIndex, j;
    for (int i = 1; i < this->theActiveData.size(); i++)
    {
        key = this->theActiveData[i];
        keyIndex = this->singleIndexValues[i];
        j = i - 1;

        // current position
        while (j >= 0 && this->theActiveData[j] > key)
        {
            this->theActiveData[j + 1] = this->theActiveData[j];
            this->singleIndexValues[j + 1] = this->singleIndexValues[j];

            j = j - 1;
        }
        this->theActiveData[j + 1] = key;
        this->singleIndexValues[j + 1] = keyIndex;
        this->theActiveDataIndexing.push_back(this->singleIndexValues);
    }
}

void SortingProvider::mergeArray(int left, int mid, int right)
{
    int subArrayOne = mid - left + 1;
    int subArrayTwo = right - mid;
    // Create temp arrays
    auto *leftArray = new double[subArrayOne],
    *rightArray = new double[subArrayTwo];

    // Create temp index arrays
    auto *leftIndexArray = new int[subArrayOne],
    *rightIndexArray = new int[subArrayTwo];
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (int i = 0; i < subArrayOne; i++)
    {
        leftArray[i] = this->theActiveData[left + i];
        leftIndexArray[i] = this->singleIndexValues[left + i];
    }
    for (int j = 0; j < subArrayTwo; j++)
    {
        rightArray[j] = this->theActiveData[mid + 1 + j];
        rightIndexArray[j] = this->singleIndexValues[mid + 1 + j];
    }
    int indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
        {
            this->theActiveData[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            this->singleIndexValues[indexOfMergedArray] = leftIndexArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            this->theActiveData[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            this->singleIndexValues[indexOfMergedArray] = rightIndexArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne)
    {
        this->theActiveData[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        this->singleIndexValues[indexOfMergedArray] = leftIndexArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        this->theActiveData[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        this->singleIndexValues[indexOfMergedArray] = rightIndexArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    this->theActiveDataIndexing.push_back(this->singleIndexValues);
}

void SortingProvider::mergeSortStage(int arrayStart, int arrayEnd)
{
    if (arrayStart >= arrayEnd)
        return;
    int mid = arrayStart + (arrayEnd - arrayStart) / 2;
    this->mergeSortStage(arrayStart, mid);
    this->mergeSortStage(mid + 1, arrayEnd);
    this->mergeArray(arrayStart, mid, arrayEnd);
}

void SortingProvider::performMergeSort()
{
    this->setupSort();
    int mid = (this->theActiveData.size()-1) / 2;
    this->mergeSortStage(0, mid);
    this->mergeSortStage(mid + 1, (this->theActiveData.size()-1));
    this->mergeArray(0, mid, (this->theActiveData.size()-1));
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void SortingProvider::heapifyFunc(int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && this->theActiveData[l] > this->theActiveData[largest])
    {
        largest = l;
    }
    // If right child is larger than largest so far
    if (r < n && this->theActiveData[r] > this->theActiveData[largest])
    {
        largest = r;
    }
    // If largest is not root
    if (largest != i)
    {
        double tempVal = this->theActiveData[i];
        this->theActiveData[i] = this->theActiveData[largest];
        this->theActiveData[largest] = tempVal;

        int tempIndexVal = this->singleIndexValues[i];
        this->singleIndexValues[i] = this->singleIndexValues[largest];
        this->singleIndexValues[largest] = tempIndexVal;

        this->theActiveDataIndexing.push_back(this->singleIndexValues);
        // Recursively heapify the affected sub-tree
        this->heapifyFunc(n, largest);
    }
}

void SortingProvider::performHeapSort()
{
    this->setupSort();
    // Build heap (rearrange array)
    for (int i = this->theActiveData.size() / 2 - 1; i >= 0; i--)
    {
        this->heapifyFunc(this->theActiveData.size(), i);
    }

    // One by one extract an element from heap
    for (int i = this->theActiveData.size() - 1; i > 0; i--)
    {
        // Move current root to end
        double tempVal = this->theActiveData[i];
        this->theActiveData[i] = this->theActiveData[0];
        this->theActiveData[0] = tempVal;

        int tempIndexVal = this->singleIndexValues[i];
        this->singleIndexValues[i] = this->singleIndexValues[0];
        this->singleIndexValues[0] = tempIndexVal;
        this->theActiveDataIndexing.push_back(this->singleIndexValues);
        // call max heapify on the reduced heap
        this->heapifyFunc(i, 0);
    }
}

int SortingProvider::partitionFunc(int low, int high)
{
    int pivot = this->theActiveData[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (this->theActiveData[j] < pivot)
        {
            i++; // increment index of smaller element

            double tempVal = this->theActiveData[i];
            this->theActiveData[i] = this->theActiveData[j];
            this->theActiveData[j] = tempVal;

            int tempIndexVal = this->singleIndexValues[i];
            this->singleIndexValues[i] = this->singleIndexValues[j];
            this->singleIndexValues[j] = tempIndexVal;
            this->theActiveDataIndexing.push_back(this->singleIndexValues);
        }
    }

    double tempVal = this->theActiveData[i + 1];
    this->theActiveData[i + 1] = this->theActiveData[high];
    this->theActiveData[high] = tempVal;

    int tempIndexVal = this->singleIndexValues[i + 1];
    this->singleIndexValues[i + 1] = this->singleIndexValues[high];
    this->singleIndexValues[high] = tempIndexVal;

    this->theActiveDataIndexing.push_back(this->singleIndexValues);

    return (i + 1);
}

void SortingProvider::quickSortStage(int low, int high)
{

    if (low < high)
    {
        /* pi is partitioning index, arr[pi] is now
           at right place */
        int pi = partitionFunc(low, high);

        this->quickSortStage(low, pi - 1);  // Before pi
        this->quickSortStage(pi + 1, high); // After pi
    }

}

void SortingProvider::performQuickSort()
{
    this->setupSort();
    /* pi is partitioning index, arr[pi] is now
       at right place */
    int pi = partitionFunc(0, (this->theActiveData.size()-1));

    this->quickSortStage(0, pi - 1);  // Before pi
    this->quickSortStage(pi + 1, (this->theActiveData.size()-1)); // After pi
}

void SortingProvider::performRadixSort()
{
    this->setupSort();

    std::vector<double> tempOriginalData;

    for (int i = 0; i<this->theActiveData.size(); i++)
    {
        if(this->minimumValue<0)
        {
            this->theActiveData[i]-=this->minimumValue;
        }
        else
        {
            this->theActiveData[i]+=this->minimumValue;
        }
        this->theActiveData[i] *= 1000;
        tempOriginalData.push_back(this->theActiveData[i]);
    }


    double tempMaximumValue = this->theActiveData[0];
    for(int i = 0; i<this->theActiveData.size(); i++)
    {
        if(tempMaximumValue<this->theActiveData[i])
        {
            tempMaximumValue = this->theActiveData[i];
        }

    }

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; tempMaximumValue / exp > 0; exp *= 10)
    {
        double output[this->theActiveData.size()]; // output array
        int numCount[10] = { 0 };

        // Store count of occurrences in count[]
        for (int i = 0; i < this->theActiveData.size(); i++)
        {
            numCount[(int)(this->theActiveData[i] / exp) % 10]++;
        }
        // Change count[i] so that count[i] now contains actual
        //  position of this digit in output[]
        for (int i = 1; i < 10; i++)
        {
            numCount[i] += numCount[i - 1];
        }
        // Build the output array
        for (int i = this->theActiveData.size() - 1; i >= 0; i--)
        {
            output[numCount[(int)(this->theActiveData[i] / exp) % 10] - 1] = this->theActiveData[i];

            numCount[(int)(this->theActiveData[i] / exp) % 10]--;
        }
        // Copy the output array to arr[], so that arr[] now
        // contains sorted numbers according to current digit
        for (int i = 0; i < this->theActiveData.size(); i++)
        {
            this->theActiveData[i] = output[i];
            for(int n=0; n<tempOriginalData.size(); n++)
            {
                if(this->theActiveData[i]==tempOriginalData[n])
                {
                    this->singleIndexValues[i] = n;
                }
            }

        }
        this->theActiveDataIndexing.push_back(this->singleIndexValues);
    }

}
void SortingProvider::performBucketSort()
{
    this->setupSort();

    for (int i = 0; i<this->theActiveData.size(); i++)
    {
        if(this->minimumValue<0)
        {
            this->theActiveData[i]-=this->minimumValue;
        }
        else
        {
            this->theActiveData[i]+=this->minimumValue;
        }
        this->theActiveData[i] *= 1000;
    }

    double tempMaximumValue = this->theActiveData[0];
    for(int i = 0; i<this->theActiveData.size(); i++)
    {
        if(tempMaximumValue<this->theActiveData[i])
        {
            tempMaximumValue = this->theActiveData[i];
        }

    }

    // 1) Create n empty buckets
    std::vector<float> b[this->theActiveData.size()+1];
    std::vector<float> indexB[this->theActiveData.size()+1];
    // 2) Put array elements
    // in different buckets
    for (int i = 0; i < this->theActiveData.size(); i++)
    {
        int bi = this->theActiveData.size() * this->theActiveData[i]/tempMaximumValue; // Index in bucket
        b[bi].push_back(this->theActiveData[i]);
        indexB[bi].push_back(i);
    }
    // 3) Sort individual buckets
    for (int i = 0; i < this->theActiveData.size()+1; i++)
    {
        if(b[i].size()>0)
        {
            //using selection sort for this
            for (int m = 0; m < b[i].size()-1; m++)
            {
                // Find the minimum element in unsorted array
                double min_idx = m;
                for (int n = m+1; n < b[i].size(); n++)
                {
                    if (b[i][n] < b[i][min_idx])
                    {
                        min_idx = n;
                    }
                }
                // Swap the found minimum element with the first elements
                double temp = b[i][min_idx];
                b[i][min_idx] = b[i][m];
                b[i][m] = temp;
                //swap indexes
                int tempIndex = indexB[i][min_idx];
                indexB[i][min_idx] = indexB[i][m];
                indexB[i][m] = tempIndex;
            }
        }
    }
    // 4) Concatenate all buckets into arr[]
    int index1 = 0;
    int index2 = 0;
    for (int i = 0; i < this->theActiveData.size()+1; i++)
    {
        for (int j = 0; j < b[i].size(); j++)
        {
            this->theActiveData[index1++] = b[i][j];
            this->singleIndexValues[index2++] = indexB[i][j];
        }
        this->theActiveDataIndexing.push_back(this->singleIndexValues);
    }

}
void SortingProvider::performShellSort()
{
    this->setupSort();
    // Start with a big gap, then reduce the gap
    for (int gap = this->theActiveData.size()/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < this->theActiveData.size(); i++)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            double temp = this->theActiveData[i];
            int tempIndex = i;

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && this->theActiveData[j - gap] > temp; j -= gap)
            {
                this->theActiveData[j] = this->theActiveData[j - gap];
                this->singleIndexValues[j] = this->singleIndexValues[j - gap];
            }

            //  put temp (the original a[i]) in its correct location
            this->theActiveData[j] = temp;
            this->singleIndexValues[j] = tempIndex;
        }
        this->theActiveDataIndexing.push_back(this->singleIndexValues);
    }

}

void SortingProvider::performCombSort()
{
    this->setupSort();
    // Initialize gap
    int gap = this->theActiveData.size();

    // Initialize swapped as true to make sure that
    // loop runs
    bool swapped = true;

    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap != 1 || swapped == true)
    {
        // Find next gap
        gap = (gap*10)/13;

        if (gap < 1)
        {
            gap = 1;
        }

        // Initialize swapped as false so that we can
        // check if swap happened or not
        swapped = false;

        // Compare all elements with current gap
        for (int i=0; i<this->theActiveData.size()-gap; i++)
        {
            if (this->theActiveData[i] > this->theActiveData[i+gap])
            {
                double tempVal = this->theActiveData[i];
                this->theActiveData[i] = this->theActiveData[i+gap];
                this->theActiveData[i+gap] = tempVal;

                int tempIndexVal = this->singleIndexValues[i];
                this->singleIndexValues[i] = this->singleIndexValues[i+gap];
                this->singleIndexValues[i+gap] = tempIndexVal;

                this->theActiveDataIndexing.push_back(this->singleIndexValues);
                swapped = true;
            }
        }
    }

}
void SortingProvider::performPigeonholeSort()
{
    this->setupSort();

    for (int i = 0; i<this->theActiveData.size(); i++)
    {
        if(this->minimumValue<0)
        {
            this->theActiveData[i]-=this->minimumValue;
        }
        else
        {
            this->theActiveData[i]+=this->minimumValue;
        }
        this->theActiveData[i] *= 1000;
    }

    double tempMaximumValue = this->theActiveData[0];
    double tempMinimumValue = this->theActiveData[0];
    for(int i = 0; i<this->theActiveData.size(); i++)
    {
        if(tempMaximumValue<this->theActiveData[i])
        {
            tempMaximumValue = this->theActiveData[i];
        }
        if(tempMinimumValue>this->theActiveData[i])
        {
            tempMinimumValue = this->theActiveData[i];
        }

    }

    int range = tempMaximumValue - tempMinimumValue + 1; // Find range

    // Create an array of vectors. Size of array
    // range. Each vector represents a hole that
    // is going to contain matching elements.
    std::vector<double> holes[range];
    std::vector<int> holeIndexes[range];
    std::cout<<"step1"<<std::endl;
    // Traverse through input array and put every
    // element in its respective hole
    for (int i = 0; i < this->theActiveData.size(); i++)
    {
        holes[(int)this->theActiveData[i]-(int)tempMinimumValue].push_back(this->theActiveData[i]);
        holeIndexes[(int)this->theActiveData[i]-(int)tempMinimumValue].push_back(i);
    }
    std::cout<<"step2"<<std::endl;
    // Traverse through all holes one by one. For
    // every hole, take its elements and put in
    // array.
    int index1 = 0;  // index in sorted array
    int index2 = 0;  // index in sorted array
    for (int i = 0; i < range; i++)
    {
        std::vector<double>::iterator it;
        for (it = holes[i].begin(); it != holes[i].end(); ++it)
        {
            this->theActiveData[index1++]  = *it;
        }
        std::cout<<"step21"<<std::endl;
        std::vector<int>::iterator indexIt;
        for (indexIt = holeIndexes[i].begin(); indexIt != holeIndexes[i].end(); ++indexIt)
        {
            this->singleIndexValues[index2++]  = *indexIt;
        }
        std::cout<<"step22"<<std::endl;
        this->theActiveDataIndexing.push_back(this->singleIndexValues);
    }

}

void SortingProvider::performCycleSort()
{
    this->setupSort();
    // count number of memory writes
    int writes = 0;

    // traverse array elements and put it to on
    // the right place
    for (int cycle_start = 0; cycle_start <= this->theActiveData.size() - 2; cycle_start++)
    {
        // initialize item as starting point
        double item = this->theActiveData[cycle_start];
        int itemIndex = cycle_start;

        // Find position where we put the item. We basically
        // count all smaller elements on right side of item.
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < this->theActiveData.size(); i++)
            if (this->theActiveData[i] < item)
            {
                pos++;
            }

        // If item is already in correct position
        if (pos == cycle_start)
        {
            continue;
        }

        // ignore all duplicate  elements
        while (item == this->theActiveData[pos])
        {
            pos += 1;
        }

        // put the item to it's right position
        if (pos != cycle_start)
        {
            double tempVal = this->theActiveData[pos];
            this->theActiveData[pos] = item;
            item = tempVal;

            int tempIndexVal = this->singleIndexValues[pos];
            this->singleIndexValues[pos] = itemIndex;
            itemIndex = tempIndexVal;
            writes++;

            this->theActiveDataIndexing.push_back(this->singleIndexValues);
        }

        // Rotate rest of the cycle
        while (pos != cycle_start)
        {
            pos = cycle_start;

            // Find position where we put the element
            for (int i = cycle_start + 1; i < this->theActiveData.size(); i++)
            {
                if (this->theActiveData[i] < item)
                {
                    pos += 1;
                }
            }

            // ignore all duplicate  elements
            while (item == this->theActiveData[pos])
            {
                pos += 1;
            }

            // put the item to it's right position
            if (item != this->theActiveData[pos])
            {
                double tempVal = this->theActiveData[pos];
                this->theActiveData[pos] = item;
                item = tempVal;

                int tempIndexVal = this->singleIndexValues[pos];
                this->singleIndexValues[pos] = itemIndex;
                itemIndex = tempIndexVal;

                writes++;

                this->theActiveDataIndexing.push_back(this->singleIndexValues);
            }

        }
    }

    // Number of memory writes or swaps
    // cout << writes << endl ;

}

void SortingProvider::performCocktailSort()
{
    this->setupSort();
    bool swapped = true;
    int start = 0;
    int arrEnd = this->theActiveData.size() - 1;

    while (swapped)
    {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;

        // loop from left to right same as
        // the bubble sort
        for (int i = start; i < arrEnd; ++i)
        {
            if (this->theActiveData[i] > this->theActiveData[i + 1])
            {
                double tempVal = this->theActiveData[i];
                this->theActiveData[i] = this->theActiveData[i + 1];
                this->theActiveData[i + 1] = tempVal;

                int tempIndexVal = this->singleIndexValues[i];
                this->singleIndexValues[i] = this->singleIndexValues[i + 1];
                this->singleIndexValues[i + 1] = tempIndexVal;
                swapped = true;

                this->theActiveDataIndexing.push_back(this->singleIndexValues);
            }
        }

        // if nothing moved, then array is sorted.
        if (!swapped)
            break;

        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = false;

        // move the end point back by one, because
        // item at the end is in its rightful spot
        --arrEnd;

        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = arrEnd - 1; i >= start; --i)
        {
            if (this->theActiveData[i] > this->theActiveData[i + 1])
            {

                double tempVal = this->theActiveData[i];
                this->theActiveData[i] = this->theActiveData[i + 1];
                this->theActiveData[i + 1] = tempVal;

                int tempIndexVal = this->singleIndexValues[i];
                this->singleIndexValues[i] = this->singleIndexValues[i + 1];
                this->singleIndexValues[i + 1] = tempIndexVal;
                swapped = true;

                this->theActiveDataIndexing.push_back(this->singleIndexValues);
            }
        }

        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }

}

void SortingProvider::performSort(int sortChoice)
{

    if(sortChoice==this->SELECTION_SORT)
    {
        this->usedSortName = "Selection Sort";
        this->performSelectionSort();
    }
    else if(sortChoice==this->BUBBLE_SORT)
    {
        this->usedSortName = "Bubble Sort";
        this->performBubbleSort();
    }
    else if(sortChoice==this->INSERTION_SORT)
    {
        this->usedSortName = "Insertion Sort";
        this->performInsertionSort();
    }
    else if(sortChoice==this->MERGE_SORT)
    {
        this->usedSortName = "Merge Sort";
        this->performMergeSort();
    }
    else if(sortChoice==this->HEAP_SORT)
    {
        this->usedSortName = "Heap Sort";
        this->performHeapSort();
    }
    else if(sortChoice==this->QUICK_SORT)
    {
        this->usedSortName = "Quick Sort";
        this->performQuickSort();
    }
    else if(sortChoice==this->RADIX_SORT)
    {
        this->usedSortName = "Radix Sort";
        this->performRadixSort();
    }
    else if(sortChoice==BUCKET_SORT)
    {
        this->usedSortName = "Bucket Sort";
        this->performBucketSort();
    }
    else if(sortChoice==SHELL_SORT)
    {
        this->usedSortName = "Shell Sort";
        this->performShellSort();
    }
    else if(sortChoice==COMB_SORT)
    {
        this->usedSortName = "Comb Sort";
        this->performCombSort();
    }
    else if(sortChoice==PIGEONHOLE_SORT)
    {
        this->usedSortName = "Pigeonhole Sort";
        this->performPigeonholeSort();
    }
    else if(sortChoice==CYCLE_SORT)
    {
        this->usedSortName = "Cycle Sort";
        this->performCycleSort();
    }
    else if(sortChoice==COCKTAIL_SORT)
    {
        this->usedSortName = "Cocktail Sort";
        this->performCocktailSort();
    }

}

std::vector<double>& SortingProvider::getOriginalData()
{

    return this->theOriginalData;
}

std::vector<double>& SortingProvider::getSortedData()
{

    return this->theActiveData;
}

std::vector<std::vector<int>>& SortingProvider::getDataIndexing()
{

    return this->theActiveDataIndexing;
}

int SortingProvider::getMaxSortNum()
{

    return this->maxSortNum;

}

double SortingProvider::getMinimumValue()
{

    return this->minimumValue;

}
double SortingProvider::getMaximumValue()
{

    return this->maximumValue;

}

std::string SortingProvider::getSortName()
{

    return this->usedSortName;

}

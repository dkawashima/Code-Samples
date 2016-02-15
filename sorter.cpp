/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The bubble sort, quick sort, merge sort, and in-place quicksort
 * algorithms (implementation).
 *
 */
#include "sorter.h"

int main(int argc, char* argv[])
{
    // Set up buffers and data input
    std::vector<int> nums;
    std::string line;
    char *filename;
    int sort_type;

    // Ensure that at most one type of sort and at least a filename are specified.
    if (argc > 3 || argc < 2)
    {
        usage();
    }

    // default sort is bubble sort
    sort_type = BUBBLE_SORT;

    // Figure out which sort to use
    for (int i = 1; i < argc; ++i)
    {
        char *arg = argv[i];
        if (strcmp(arg, "-b") == 0) { sort_type = BUBBLE_SORT; }
        else if (strcmp(arg, "-q") == 0) { sort_type = QUICK_SORT; }
        else if (strcmp(arg, "-m") == 0) { sort_type = MERGE_SORT; }
        else if (strcmp(arg, "-qi") == 0) { sort_type = QUICK_SORT_INPLACE; }
        else { filename = argv[i]; }
    }

    // Read the file and fill our vector of integers
    // THIS FUNCTION IS STUDENT IMPLEMENTED
    readFile(filename, nums);

    switch (sort_type)
    {
        case BUBBLE_SORT:
        print_vector(bubbleSort(nums));
        break;

        case QUICK_SORT:
        print_vector(quickSort(nums));
        break;

        case MERGE_SORT:
        print_vector(mergeSort(nums));
        break;

        case QUICK_SORT_INPLACE:
        quicksort_inplace(nums, 0, nums.size() - 1);
        print_vector(nums);
        break;

        default:
        usage();
        break;
    }
    return 0;
}

/**
 * Usage    Prints out a usage statement and exits.
 */
void usage()
{
    fprintf(stderr, "%s", usage_string);
    exit(1);
}

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to sorter.h if you write a helper function!
 */

/**
 * @brief Runs bubble sort algorithm on vector of integers
 *
 * @param vector of integers
 * 
 * @return sorted vector of integers
 *
 * Outline of Bubble Sort:
 *  WHILE (# of remaining elements > 0)
 *       swapIndex = 0
 *       FOR (i = 0; i < (index of last remaining element - 1); i++)
 *          IF (array[i] > array[i + 1])
 *              swap array[i] and array[i + 1]
 *              remember index of swap (i)
 *          ENDIF
 *      ENDFOR
 *      Set index of last remaining element = last swap index (if there was a swap)
 *  ENDWHILE
 *
 */
std::vector<int> bubbleSort(std::vector<int> &list)
{
    int temp, swapIndex;
    int remaining = list.size() - 1;
    while (remaining > 0){
        swapIndex = 0;
        for (int i = 0; i < (remaining); i++){
            if (list[i] > list[i + 1]){
                temp = list[i];
                list[i] = list[i + 1];
                list[i + 1] = temp;
                swapIndex = i;
            }
        }
        remaining = swapIndex;
    }
    return list;
}

/**
 * @brief Runs quicksort algorithm on vector of integers
 *
 * @param vector of integers
 * 
 * @return sorted vector of integers
 *
 * Outline of Quick Sort:
 *  IF # of elements in vector <= 1
 *      return list
 *  FOR (i = 0; i < # of elements in vector; i++)
 *      IF vector[i] less or equal than vector[pivot]
 *          Add vector[i] to new list lessthan
 *      ELSE
 *          Add vector[i] to new list morethan
 *  quicksort(lessthan)
 *  quicksort(morethan)
 *  return merge(lessthan, morethan) 
 */
std::vector<int> quickSort(std::vector<int> &list)
{
    int size = list.size();
    std::vector<int> lessthan;
    std::vector<int> morethan;
    if (size <= 1){
        return list;
    }
    int pivot = rand() % size;
    for (int i = 0; i < size; i++){
        if (i != pivot){
            if (list[i] <= list[pivot]){
                lessthan.push_back(list[i]);
            } else {
                morethan.push_back(list[i]);
            }
        }
    }
    lessthan = quickSort(lessthan);
    morethan = quickSort(morethan);
    lessthan.push_back(list[pivot]);
    for (size_t i = 0; i < morethan.size(); i++){
        lessthan.push_back(morethan[i]);
    }
    return lessthan;
}

/**
 * @brief Runs merge sort algorithm on vector of integers
 *
 * @param vector of integers
 * 
 * @return sorted vector of integers
 *
 * Outline of Merge Sort:
 *       IF (size of array == 1)
 *          return array
 *       middle = (size of array) / 2
 *       lowindex = 0, highindex = (size of array - 1)
 *       lowarray = mergesort(elements 0 to middle -1 of array)
 *       higharray = mergesort(middle + 1, highindex)
 *       merge(lowarray, higharray)
 *
 */
std::vector<int> mergeSort(std::vector<int> &list)
{
    int size = list.size();
    if (size <= 1){
        return list;
    }
    int middle = (size - 1) / 2;
    std::vector<int> listleft, listright;
    for (int i = 0; i <= middle; i++){
        listleft.push_back(list[i]);
    }
    for (int i = middle + 1; i < size; i++){
        listright.push_back(list[i]);
    }
    std::vector<int> left = mergeSort(listleft);
    std::vector<int> right = mergeSort(listright);
    return merge(left, right);
}

/**
 * @brief Merges two sorted vectors of integers into one sorted 
 * vector of integers
 *
 * @param two vectors of integers
 * 
 * @return sorted vector of integers
 *
 */
std::vector<int> merge(std::vector<int> &left, std::vector<int> &right)
{
    std::vector<int> sorted;
    size_t i = 0;
    size_t j = 0;
    while (i < left.size() && j < right.size()){
        if(left[i] <= right[j]){
            sorted.push_back(left[i]);
            i++;
        } else {
            sorted.push_back(right[j]);
            j++;
        }
    }
    while (i < left.size()){
        sorted.push_back(left[i]);
        i++;
    }
    while (j < right.size()){
        sorted.push_back(right[j]);
        j++;
    }
    return sorted;
}

/*
 * quicksort_inplace:  In-place version of the quicksort algorithm. Requires
 *              O(1) instead of O(N) space, same time complexity. Each call of
 *              the method partitions the list around the pivot (an item taken
 *              from the middle of the array) with items left of the pivot
 *              smaller than it and items to its right larger than it. Then the
 *              method recursively sorts the left and right portions of the list
 *              until it reaches its base case: a list of length 1 is already
 *              sorted.
 *
 * @param list: pointer to integer array to be sorted
 * @returns:    Nothing, the array is sorted IN-PLACE.
 *
 * Outline of Quicksort In-Place:
 *      IF size of interval to be sorted <= 1
 *          return
 *      Pick a random pivot within the interval
 *      Partition the list using the helper function to get a newPivot
 *      quicksort_inplace(list, left, newPivot - 1)
 *      quicksort_inplace(list, newPivot + 1, right)
 *
 */
void quicksort_inplace(std::vector<int> &list, int left, int right)
{
    int newPivot;
    if ((right - left) <= 1){
        return;
    }
    int pivot = (rand() % (right - left)) + left;
    newPivot = partition(list, left, right, pivot);
    quicksort_inplace(list, left, newPivot - 1);
    quicksort_inplace(list, newPivot + 1, right);
    return;
}


/* 
* @brief Partitions vector into 3 parts; the values less than the
* pivot, the pivot, and the values greater than the pivot. 
*
* @param list: pointer to integer array to be sorted
* @param left, right: indices of the list where the list needs to be sorted.
* @param pivot: index of random pivot in list
*
* @return index of newPivot (the middle of the 3 parts)
*/

int partition(std::vector<int> &list, int left, int right, int pivot){
    int recentless = -1;
    int recentmore = -1;
    int temp;

    for (int i = left; i <= right; i++){
    if (i != pivot){
        if (list[i] <= list[pivot]){
            if (recentmore > i){
                temp = list[recentmore];
                list[recentmore] = list[i];
                list[i] = temp;
                recentmore++;
            }
            recentless = i;
            }
        else {
            if (recentmore == -1){
                recentmore = i;
            } 
        }
        }
    }
    if (pivot < recentless){
        temp = list[recentless];
        list[recentless] = list[pivot];
        list[pivot] = temp;
        pivot = recentmore;
    } 
    if (pivot > recentmore){
        temp = list[recentmore];
        list[recentmore] = list[pivot];
        list[pivot] = temp;
        pivot = recentless;
    }
    return pivot;

    }


/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (header file).
 *
 */

#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include "ConvexHullApp.h"
#include "structs.h"

using namespace std;

void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app);
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app);
Tuple* GetNextPoint(std::vector<Tuple*> &points, Tuple* start);
Tuple* GetLeftMostPoint(std::vector<Tuple*> &points);
void sort(vector<Tuple*> &points, vector<double> &angles);
void quicksort_inplace(vector<Tuple*> &points, vector<double> &angles, int left, int right);
int partition(vector<Tuple*> &points, vector<double> &angles, int left, int right, int pivot);
bool CheckIfLeft(Tuple* a, Tuple* b, Tuple* c);
Tuple* GetLowestPoint(std::vector<Tuple*> &points);
void GrahamScanSort(vector<Tuple*> points, Tuple* start);

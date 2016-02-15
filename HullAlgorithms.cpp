/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (implementation).
 *
 */
#include "HullAlgorithms.h"

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to HullAlgorithms.h if you write a helper function!
 *
 * Our reference implementation has four helper functions and the function(s)
 * copied over from angleSort.cpp.
 */
/* 
* @brief Partitions vector into 3 parts; the values less than the
* pivot, the pivot, and the values greater than the pivot. 
*
* @param points: pointer to tuple array, will be partnered with angles array
* @param angles: pointer to double array to be sorted
* @param left, right: indices of the list where the list needs to be sorted.
* @param pivot: index of random pivot in list
*
* @return index of newPivot (the middle of the 3 parts)
*/
int partition(vector<Tuple*> &points, vector<double> &angles, int left, int right, int pivot){
    int recentless = -1;
    int recentmore = -1;
    double tempDou;
    Tuple* tempTup;

    for (int i = left; i <= right; i++){
    if (i != pivot){
        if (angles[i] <= angles[pivot]){
            if (recentmore > i){
                tempDou = angles[recentmore];
                angles[recentmore] = angles[i];
                angles[i] = tempDou;
                tempTup = points[recentmore];
                points[recentmore] = points[i];
                points[i] = tempTup;
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
        tempDou = angles[recentless];
        angles[recentless] = angles[pivot];
        angles[pivot] = tempDou;
        tempTup = points[recentless];
        points[recentless] = points[pivot];
        points[pivot] = tempTup;
        pivot = recentmore;
    } 
    if (pivot > recentmore){
        tempDou = angles[recentmore];
        angles[recentmore] = angles[pivot];
        angles[pivot] = tempDou;
        tempTup = points[recentmore];
        points[recentmore] = points[pivot];
        points[pivot] = tempTup;
        pivot = recentless;
    }
    return pivot;

    }
/*
 * quicksort_inplace:
 *
 * @param points: pointer to tuple array, will be partnered with angles array
 * @param angles: pointer to double array to be sorted
 * @param left, right: indices of the array in between which the array needs to be sorted.
 * @returns:    Nothing, the array is sorted IN-PLACE.
 *
 * Outline of Quicksort In-Place:
 *      IF size of interval to be sorted <= 1
 *          return
 *      Pick a random pivot within the interval
 *      Partition the angles array (attached to points array) using the helper function to get a newPivot
 *      quicksort_inplace(points, angles, left, newPivot - 1)
 *      quicksort_inplace(points, angles, newPivot + 1, right)
 *
 */
void quicksort_inplace(vector<Tuple*> &points, vector<double> &angles, int left, int right)
{
    int newPivot;
    if ((right - left) <= 1){
        return;
    }
    int pivot = (rand() % (right - left)) + left;
    newPivot = partition(points, angles, left, right, pivot);
    quicksort_inplace(points, angles, left, newPivot - 1);
    quicksort_inplace(points, angles, newPivot + 1, right);
    return;
}
/*
* Runs Quicksort in Place algorithm on angles vector.
*/
void sort(vector<Tuple*> &points, vector<double> &angles)
{
    
    quicksort_inplace(points, angles, 0, angles.size() - 1);
    return;
}
/**
 * @brief Uses gift wrap algorithm to build lowest possible convex hull of points
 *
 * @param points: pointer to tuple array of possible points in convex hull
 * @param app: convex hull object
 *
 * Outline:
 *  Add starting (left-most) point to hull
 *      WHILE nextpoint != start
 *          Get next point for which the line connecting next point and current
 *          point has no points to the left of the line
 *      Add start to hull
 */
void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app)
{
    Tuple* start;
    Tuple* currentPoint;
    Tuple* nextPoint1;
    start = GetLeftMostPoint(points);
    app->add_to_hull(start);
    nextPoint1 = points[0];
    currentPoint = start;

    do {
        nextPoint1 = GetNextPoint(points, currentPoint);
        app->add_to_hull(nextPoint1);
        currentPoint = nextPoint1;
        } while (start != currentPoint);
    
    app->add_to_hull(points[0]);
}
/* 
* @brief Gets point with least x-coordinate in given array
*
* @param points: pointer to tuple array, which will be searched least x-value
*
* @return the tuple with lowest x-coordinate
*/
Tuple* GetLeftMostPoint(std::vector<Tuple*> &points){
    std::vector<double> x;
    for (size_t i = 0; i < points.size(); i++){
        x.push_back(points[i]->x);
    }
    sort(points, x);
    return points[0];
}
/* 
* @brief Gets point with least x-coordinate in given array
*
* @param points: pointer to tuple array, which will be searched least x-value
*
* @return the tuple with lowest x-coordinate
*/
Tuple* GetLowestPoint(std::vector<Tuple*> &points){
    std::vector<double> y;
    int lastIndex = points.size() - 1;
    for (size_t i = 0; i < points.size(); i++){
        y.push_back(points[i]->y);
    }
    sort(points, y);
    return points[lastIndex];
}
/* 
* @brief Gets next point in the convex hull
*
* @param points: pointer to tuple array of possible points
* @param start: pointer to tuple that is current point in convex hull
*
* @return the next point in the convex hull
*/
Tuple* GetNextPoint(std::vector<Tuple*> &points, Tuple* start){
    bool NoLeft = true;
    for (size_t i = 0; i < points.size(); i++){
        if (points[i] != start){
            for (size_t j = 0; j < points.size(); j++){
                if (points[j] != start && points[j] != points[i]){
                    if(!(CheckIfLeft(start, points[i], points[j]))){
                        NoLeft = false;
                    }
                } 
            }
            if (NoLeft == true){
                return points[i];
            }
            NoLeft = true;
        }

    }
    return start;
}
/* 
* @brief Check if point is left of a possible line in convex hull.
* Uses cross product formula to do so.
*
* @param a: pointer to tuple already in convex hull
* @param b: pointer to tuple that might be in convex hull
* @param c: pointer to tuple that needs to be right of convex hull line
* for line to be valid. 
*
* @return true if c is left of line a-b, false if not.
*/
bool CheckIfLeft(Tuple* a, Tuple* b, Tuple* c){
    double vector1x = b->x - a->x;
    double vector1y = a->y - b->y;
    double vector2x = c->x - a->x;
    double vector2y = a->y - c->y;
    if (vector1x * vector2y > vector1y * vector2x){
        return true;
    }
    return false;
}
/* 
* @brief Sorts tuple array by angle with respect to start point 
*
* @param points: pointer to tuple array to be sorted
* @param start: point in array to compare angles for sort
*/
void GrahamScanSort(vector<Tuple*> points, Tuple* start){
    vector<double> angles;
    for (unsigned int i = 0; i < points.size(); ++i) {
        angles.push_back(start->angle_wrt_pt(points[i]));
    }
    sort(points, angles);

}
/**
 * @brief Uses Graham Scan algorithm to build lowest possible convex hull of points
 *
 * @param points: pointer to tuple array of possible points in convex hull
 * @param app: convex hull object
 *
 * Outline:
 *  Add starting (lowest) point to hull
 *  Sort all points by angle with horizontal line of lowest point
 *  Add points[1] to hull
 *  FOR all other possible points 
 *      if point does not make a left turn
 *          Add point to hull
 *  Add start to hull
 */
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app)
{
    vector<Tuple*> pointsOnHull;
    Tuple* start = GetLowestPoint(points);
    app->add_to_hull(start);
    pointsOnHull.push_back(start);
    GrahamScanSort(points, start);
    app->add_to_hull(points[1]);
    pointsOnHull.push_back(points[1]);
    for (unsigned int i = 2; i < points.size(); ++i)
    {
        if(!(CheckIfLeft(pointsOnHull[pointsOnHull.size() - 2], 
            pointsOnHull[pointsOnHull.size() - 1], points[i]))){
            app->add_to_hull(points[i]);
        }
    }
    app->add_to_hull(points[0]);
}

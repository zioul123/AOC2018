#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <climits>
#include <vector>

using namespace std;

int NOT_CHECKED = -2;
int TIED_DIST = -1; 
bool testing = false;

class Point 
{
public:
    int x, y;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    int distanceTo(Point p) { return abs(p.x - x) + abs(p.y - y); }
};

class Util
{
public:
    static const int MIN_X = 0, MIN_Y = 1, MAX_X = 2, MAX_Y = 3;
    static int findStat(vector<Point> points, int stat)
    {
        int minOrMax = ((stat == MIN_X) || (stat == MIN_Y)) 
                       ? INT_MAX
                       : INT_MIN;
        for (int i=0; i<points.size(); i++) {
            Point p = points[i];
            if ((stat == MIN_X) || (stat == MIN_Y)) {
                int val = (stat == MIN_X) ? p.x : p.y;
                if (val < minOrMax) 
                    minOrMax = val;
            } else {
                int val = (stat == MAX_X) ? p.x : p.y;
                if (val > minOrMax) 
                    minOrMax = val;
            }
        }
        return minOrMax;
    }
};

int main()
{
    vector<Point> points;

    // Get input
    int scannedX, scannedY;
    while (scanf("%d, %d\n", &scannedX, &scannedY) != EOF)
    {
        points.push_back(Point(scannedX, scannedY));
    }

    if (testing) // Preview points
    for (int i=0; i<points.size(); i++) 
        cout << points[i].x << "," << points[i].y << endl;

    // Get search boundaries
    int minX = Util::findStat(points, Util::MIN_X);
    int maxX = Util::findStat(points, Util::MAX_X);
    int minY = Util::findStat(points, Util::MIN_Y);
    int maxY = Util::findStat(points, Util::MAX_Y);

    // Setup the map
    int map[maxY+1][maxX+1];
    for (int i = 0; i <= maxY; i++) 
        for (int j = 0; j <= maxX; j++) {
            map[i][j] = NOT_CHECKED;
        }

    // Check every point 
    for (int y = 0; y <= maxY; y++) {
        for (int x = 0; x <= maxX; x++) {
            int bestDist = INT_MAX;
            Point bestPoint;
            for (int i = 0; i < points.size(); i++) {
                Point p = points[i];
                int currDist = p.distanceTo(Point(x, y));

                if (currDist < bestDist) {
                    bestDist = currDist;
                    bestPoint = p;
                    map[y][x] = i;
                } else if (currDist == bestDist) {
                    map[y][x] = TIED_DIST;
                }
            }
        }
    }

    // Preview map
    if (testing)
    for (int i = 0; i <= maxY; i++) { 
        for (int j = 0; j <= maxX; j++) 
            cout << (map[i][j] < 0 ? "" : " ") << map[i][j] << " ";
        cout << endl;
    }

    // Count each and pick biggest
    int largestPointId = -1, largestArea = -1;
    for (int i = 0; i < points.size(); i++) {
        int totalArea = 0;
        for (int y = 0; totalArea != -1 && y <= maxY; y++) { 
            for (int x = 0; totalArea != -1 && x <= maxX; x++) {
                if (map[y][x] == i) {
                    // It's infinite
                    if (y == 0 || x == 0 || y == maxY || x == maxX) {
                        totalArea = -1;
                        break;
                    // It's valid
                    } else {
                        totalArea++;
                    }
                }
            }
        }
        if (totalArea > largestArea) {
            largestArea = totalArea;
            largestPointId = i;
        }
    }
    cout << "Largest point id: " << largestPointId << ", " << largestArea << endl;
}

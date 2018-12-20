import java.util.*;

// Encapsulate a point
class Point {
    int x, y; // coordinates
    Point(int x, int y) { this.x = x; this.y = y; }
    
    int distanceTo(Point p) {
        return Math.abs(p.x - x) + Math.abs(p.y - y);
    }
    public String toString() {
        return "<" + x + "," + y + ">";
    }
}

class Util {
    static enum Stat {
        MIN_X, MIN_Y, MAX_X, MAX_Y
    }
    // Find the min_x, min_y, max_x or max_y in an arraylist of points.
    static int findStat(ArrayList<Point> points, Stat stat) {
        int minOrMax = ((stat == Stat.MIN_X) || (stat == Stat.MIN_Y)) 
                       ? Integer.MAX_VALUE
                       : Integer.MIN_VALUE;
        for (Point p : points) {
            if ((stat == Stat.MIN_X) || (stat == Stat.MIN_Y)) {
                int val = stat == Stat.MIN_X ? p.x : p.y;
                if (val < minOrMax) 
                    minOrMax = val;
            } else {
                int val = stat == Stat.MAX_X ? p.x : p.y;
                if (val > minOrMax) 
                    minOrMax = val;
            }
        }
        return minOrMax;
    }
}

public class Day6 {
    private final int NOT_CHECKED = -2;
    private final int TIED_DIST = -1;
    boolean testing = false;

    public void run() {
        ArrayList<Point> points = new ArrayList<>();

        // Get all input points
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            String[] s = sc.nextLine().split(" ");
            points.add(new Point(
                    Integer.parseInt(s[0].substring(0, s[0].length() - 1)),
                    Integer.parseInt(s[1])));
        }
        if (testing)
        for (Point p : points) System.out.println(p); // To preview points

        // Get the boundaries to search
        int minX = Util.findStat(points, Util.Stat.MIN_X);
        int maxX = Util.findStat(points, Util.Stat.MAX_X);
        int minY = Util.findStat(points, Util.Stat.MIN_Y);
        int maxY = Util.findStat(points, Util.Stat.MAX_Y);

        // Setup the map first
        int[][] map = new int[maxY+1][maxX+1]; // Take note that it's y then x
        for (int i = 0; i <= maxY; i++) 
            for (int j = 0; j <= maxX; j++) {
                map[i][j] = NOT_CHECKED;
            }
        // Check every point 
        for (int y = 0; y <= maxY; y++) {
            for (int x = 0; x <= maxX; x++) {
                int bestDist = Integer.MAX_VALUE;
                Point bestPoint = null;
                for (int i = 0; i < points.size(); i++) {
                    Point p = points.get(i);
                    int currDist = p.distanceTo(new Point(x, y));

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
                System.out.print((map[i][j] < 0 ? "" : " ") + map[i][j] + " ");
            System.out.println();
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
        System.out.println("Largest point id: " + largestPointId + ", " + largestArea);
    }

    public static void main(String[] args) {
        Day6 d = new Day6();
        d.run();
    }
}
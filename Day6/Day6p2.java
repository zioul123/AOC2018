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

public class Day6p2 {
    private final int NOT_CHECKED = -2;
    private final int TIED_DIST = -1;
    private final int OFFSET = 100;
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
        int[][] map = new int[maxY+1+OFFSET][maxX+1+OFFSET]; // Take note that it's y then x
        for (int i = 0; i <= maxY+OFFSET; i++) 
            for (int j = 0; j <= maxX+OFFSET; j++) {
                map[i][j] = NOT_CHECKED;
                // belongsTo(new Point(j, i), NOT_CHECKED);
            }

        // Check every point 
        int totalArea = 0;
        for (int y = 0; y <= maxY+OFFSET; y++) {
            for (int x = 0; x <= maxX+OFFSET; x++) {
                int sum = 0;
                for (Point p : points) {
                    sum += p.distanceTo(new Point(x, y));
                }
                map[y][x] = (sum < (testing ? 32 : 10000) ? 1 : 0);
                totalArea += map[y][x];
            }
        }

        // Preview map
        if (testing)
        for (int i = 0; i <= maxY; i++) { 
            for (int j = 0; j <= maxX; j++) 
                System.out.print((map[i][j] < 0 ? "" : " ") + map[i][j] + " ");
            System.out.println();
        }

        System.out.println("Total area: " + totalArea);
    }

    public static void main(String[] args) {
        Day6p2 d = new Day6p2();
        d.run();
    }
}
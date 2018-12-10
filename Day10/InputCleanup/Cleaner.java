import java.util.*;

class Pair {
    public int x; public int y;
    public Pair(int x, int y) {
        this.x = x; this.y = y;
    }
    public String toString() {
        return x + ", " + y;//"[" + x + ", " + y + "]";
    }
}

public class Cleaner {

    void run() {
        Scanner sc = new Scanner(System.in);
        ArrayList<Pair> positions = new ArrayList<>();
        ArrayList<Pair> velocities = new ArrayList<>();
        while (sc.hasNext()) {
            String input = sc.nextLine();
            positions.add(new Pair(Integer.parseInt("" + input.substring(10,16).trim()),
                                   Integer.parseInt("" + input.substring(18,24).trim())));
            velocities.add(new Pair(Integer.parseInt("" + input.substring(36,38).trim()),
                                   Integer.parseInt("" + input.substring(40,42).trim())));
        }

        //System.out.println("[");
        for (Pair p : positions) {
            System.out.println(p);
        }
        //System.out.println("]");

        //System.out.println();

        // System.out.println("[");
        for (Pair p : velocities) {
            System.out.println(p);
        }
        // System.out.println("]");
    }

    public static void main(String[] args) {
        Cleaner c = new Cleaner();
        c.run();
    }
}
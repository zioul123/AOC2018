import java.util.*;

public class Day3p2 {
    public void run() {
        int[][] map = new int[1500][1500];
        Scanner sc = new Scanner(System.in);
        
        ArrayList<String> inputs = new ArrayList<>();

        // Input loop
        while (sc.hasNext()) {
            String s = sc.nextLine();  
            inputs.add(s);
            String[] input = s.split(" ");
            String[] r_c = input[2].split(",");
            String[] dim = input[3].split("x");

            int c = Integer.parseInt(r_c[0]);
            int r = Integer.parseInt(r_c[1].substring(0, r_c[1].length()-1)); // trim comma
            int w = Integer.parseInt(dim[0]);
            int h = Integer.parseInt(dim[1]);

            for (int i = r; i < r + h; i++) {
                for (int j = c; j < c + w; j++) {
                    map[i][j] = map[i][j] + 1;
                }
            }
        }

        // Checking loop
        Iterator<String> iter = inputs.iterator();
        while (iter.hasNext()) {
            String s = iter.next();  
            String[] input = s.split(" ");
            String[] r_c = input[2].split(",");
            String[] dim = input[3].split("x");
            int c = Integer.parseInt(r_c[0]);
            int r = Integer.parseInt(r_c[1].substring(0, r_c[1].length()-1)); // trim comma
            int w = Integer.parseInt(dim[0]);
            int h = Integer.parseInt(dim[1]);

            boolean correct = true;
            for (int i = r; i < r + h && correct; i++) {
                for (int j = c; j < c + w && correct; j++) {
                    if (map[i][j] > 1) correct = false;
                }
            }
            if (correct) {
                System.out.println("Correct: " + input[0]);
                return;
            }
        }
    }

    public static void main(String[] args) {
        Day3p2 d = new Day3p2();
        d.run();
    }
}
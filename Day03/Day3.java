import java.util.*;

public class Day3 {
    public void run() {
        int[][] map = new int[1500][1500];
        Scanner sc = new Scanner(System.in);
        
        while (sc.hasNext()) {
            String s = sc.nextLine();  
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

        int result = 0;
        for (int i = 0; i < 1500; i++) {
            for (int j = 0; j < 1500; j++) {
                if (map[i][j] > 1) {
                    result++;                        
                }
            }
        }
        System.out.println(result);
    }
    
    public static void main(String[] args) {
        Day3 d = new Day3();
        d.run();
    }
}
import java.util.*;

public class Day1p2 {

	HashSet<Integer> visited;
	boolean testing = false;

	public void run() {
		Scanner sc = new Scanner(System.in);
		visited = new HashSet<>();
		ArrayList<Integer> freqs = new ArrayList<>();

		int res = 0;
		visited.add(0);
		//freqs.add(0);	

		while (sc.hasNext()) {
			int curr = sc.nextInt();
			res += curr;
			if (visited.contains(res)) {
				System.out.println(res);
				return;
			}
			visited.add(res);
			freqs.add(curr);
			if (testing) System.out.println(res);
		}

		while (true) {
			for (int i = 0; i < freqs.size(); i++) {
				int curr = freqs.get(i);
				res += curr;
				if (visited.contains(res)) {
					System.out.println("Found: " + res);
					return;
				}
				visited.add(res);
				if (testing) System.out.println(res);
			}
		}

		//System.out.println("No repeats.");
		//return;
	}

	public static void main(String[] args) {
		Day1p2 day1 = new Day1p2();
		day1.run();
	}
}

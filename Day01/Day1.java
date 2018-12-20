import java.util.*;

public class Day1 {

	public void run() {
		Scanner sc = new Scanner(System.in);
		
		int res = 0;
		while (sc.hasNext()) {
			int curr = sc.nextInt();
			res += curr;
		}
		System.out.println(res);
		return;
	}

	public static void main(String[] args) {
		Day1 day1 = new Day1();
		day1.run();
	}
}

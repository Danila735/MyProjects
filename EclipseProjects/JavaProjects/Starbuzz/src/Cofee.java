import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Cofee extends CafeinBeverage {
	
	public void brew() {
		System.out.println("Dripping Coffee throught filter");
	}

	public void addCondiments() {
		System.out.println("Adding Sugar and Milk");
	}
	
	public boolean customerWantsCondiments() {
		String answer = getUserInput();
		
		if(answer.toLowerCase().startsWith("y")) {
			return true;
		} else {
			return false;
		}
	}

	private String getUserInput() {
		String answer = null;
		System.out.println("Do you wanna sugar, motherfacker?!");
		
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		try {
			answer = in.readLine();
		} catch (IOException ioe) {
			System.err.println("IO error trying to read your answeeeeeeeeeeeeeeee....hrhrhrhrzzzzzz");
		}
		if (answer == null)
			return "no";
		
		return answer;
	}
	
}

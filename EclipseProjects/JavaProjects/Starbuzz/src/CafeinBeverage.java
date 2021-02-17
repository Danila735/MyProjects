import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public abstract class CafeinBeverage {
	final void prepareRecipe() {
		boilWater();
		brew();
		pourInCup();
		
		if (customerWantsCondiments()) {
			addCondiments();
		}
	}
	
	private boolean customerWantsCondiments() {
		
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
	

	abstract void brew();
	abstract void addCondiments();
	
	private void boilWater() {
		System.out.println("Boil Water");
	}
	
	private void pourInCup() {
		System.out.println("Pouring Into Cup");		
	}
	
}

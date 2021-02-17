
public class Test {

	public static void main(String[] args) {
		Tea tea = new Tea();
		Cofee coffee = new Cofee();
		
		System.out.println("\nMaking tea...");
		tea.prepareRecipe();
		
		System.out.println("\nMaking coffee...");
		coffee.prepareRecipe();
		
	}

}

import java.util.*;

public class DotComBust {
	private GameHelper helper = new GameHelper();
	private ArrayList<DotCom> dotComsList = new ArrayList<DotCom>();
	private int numberOfGuess = 0;
	
	private void setUpGame() {
		//Создание сайтов и имен для них
		DotCom one = new DotCom();
		one.setName("Pets.com");
		
		DotCom two = new DotCom();
		two.setName("eToys.com");
		
		DotCom three = new DotCom();
		three.setName("Go2.com");
		
		dotComsList.add(one);
		dotComsList.add(two);
		dotComsList.add(three);
		
		System.out.println("Ваша цель - потопить три сайта.");
		System.out.println("Pets.com, eToys.com, Go2.com");
		System.out.println("Попытайтесь потопить их за минимальное число ходов");
		
		for (DotCom dotComToSet : dotComsList) {
			ArrayList<String> newLocation = helper.placeDotCom(3);
			dotComToSet.setLocationCells(newLocation);
		}
	}
	
	private void startPlaying() {
		while(!dotComsList.isEmpty()) {
			String userGuess = helper.getUserInput("Сделайте ход");
			checkUserGuess(userGuess);
		}
		finishGame();
	}
	
	private void checkUserGuess(String userGuess) {
		numberOfGuess++;
		String result = "Мимо";
		
		for (DotCom dotComToTest : dotComsList) {
			result = dotComToTest.checkYourself(userGuess);
			
			if(result.equals("Попал")) {
				break;
			}
			if(result.equals("Потопил")) {
				dotComsList.remove(dotComToTest);
				break;
			}
		}
		System.out.println(result);
	}
	
	private void finishGame() {
		System.out.println("Все сайты ушли ко дну! Ваши акции теперь ничего не стоят :(");
		if (numberOfGuess <= 18) {
			System.out.println("Это заняло у вас всего " + numberOfGuess + " попыток");
			System. out. println ("Вы успели выбраться до того, как ваши вложения утонули.");
		} else {
			System.out.println ("Это заняло у вас довольно много времени. " + numberOfGuess + "попыток.");
			System.out .println ("Рыбы водят хороводы вокруг ваших вложений.");
		}
	}
	
	public static void main (String[] args) {
		DotComBust game = new DotComBust();
		game.setUpGame();
		game.startPlaying();
	}
}













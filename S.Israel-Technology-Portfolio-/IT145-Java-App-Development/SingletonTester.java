package com.gamingroom;

/**
 * Author: Stephen Israel
 * A class to test a singleton's behavior
 * 
 * This class verifies that only one instance of the
 * GameService exists by retrieving the singleton instance
 * and displaying the games that were added in another class.
 * If the same data appears here, it confirms the Singleton
 * pattern is working correctly.
 * 
 * @author coce@snhu.edu
 */
public class SingletonTester {

	/**
	 * Tests the singleton behavior of the GameService.
	 */
	public void testSingleton() {
		
		System.out.println("\nAbout to test the singleton...");
		
		// Obtain local reference to the singleton instance
		GameService service = GameService.getInstance();
		
		// Print all games to confirm shared state
		for (int i = 0; i < service.getGameCount(); i++) {
			System.out.println(service.getGame(i));
		}
	}
}

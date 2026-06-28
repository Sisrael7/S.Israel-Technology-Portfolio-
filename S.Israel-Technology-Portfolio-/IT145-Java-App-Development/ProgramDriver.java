package com.gamingroom;

/**
 * Author: Stephen Israel
 * Application start-up program
 * 
 * This class serves as the entry point for the application.
 * It retrieves the singleton instance of the GameService and
 * initializes game, team, and player data to demonstrate
 * correct behavior.
 * 
 * @author coce@snhu.edu
 */
public class ProgramDriver {
	
	/**
	 * The one-and-only main() method
	 * 
	 * @param args command line arguments
	 */
	public static void main(String[] args) {
		
		// Obtain reference to the singleton instance of GameService
		GameService service = GameService.getInstance();
		
		System.out.println("\nAbout to test initializing game data...");
		
		// Initialize game data
		Game game1 = service.addGame("Game #1");
		System.out.println(game1);
		
		Game game2 = service.addGame("Game #2");
		System.out.println(game2);

		// Add teams to Game #1
		Team team1 = game1.addTeam("Team Alpha");
		System.out.println(team1);

		Team team2 = game1.addTeam("Team Beta");
		System.out.println(team2);

		// Attempt to add duplicate team
		Team duplicateTeam = game1.addTeam("Team Alpha");
		System.out.println("Duplicate team check: " + duplicateTeam);

		// Add players to Team Alpha
		Player player1 = team1.addPlayer("Player One");
		System.out.println(player1);

		Player player2 = team1.addPlayer("Player Two");
		System.out.println(player2);

		// Attempt to add duplicate player
		Player duplicatePlayer = team1.addPlayer("Player One");
		System.out.println("Duplicate player check: " + duplicatePlayer);

		// Prove singleton behavior across classes
		SingletonTester tester = new SingletonTester();
		tester.testSingleton();
	}
}

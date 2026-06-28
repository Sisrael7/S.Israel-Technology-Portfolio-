package com.gamingroom;

import java.util.ArrayList;
import java.util.List;

/**
 * Author: Stephen Israel
 * A singleton service for the game engine
 * 
 * Singleton Pattern:
 * This class implements the Singleton design pattern to ensure
 * that only one instance of GameService exists in memory at any
 * given time. This allows the application to manage all games,
 * teams, and players from a single shared service.
 * 
 * @author coce@snhu.edu
 */
public class GameService {

    /**
     * A list of the active games
     */
    private static List<Game> games = new ArrayList<Game>();

    /**
     * Holds the next identifiers for games, teams, and players
     */
    private static long nextGameId = 1;
    private static long nextTeamId = 1;
    private static long nextPlayerId = 1;

    /**
     * The single instance of the GameService
     */
    private static GameService instance = null;

    /**
     * Private constructor to prevent instantiation
     * from outside the class.
     */
    private GameService() {
    }

    /**
     * Returns the single instance of the GameService.
     * 
     * @return the singleton instance
     */
    public static GameService getInstance() {
        if (instance == null) {
            instance = new GameService();
        }
        return instance;
    }

    /**
     * Construct a new game instance
     * 
     * Iterator Pattern:
     * Iterates through the existing games to ensure
     * the game name is unique before creating a new game.
     * 
     * @param name the unique name of the game
     * @return the game instance (new or existing)
     */
    public Game addGame(String name) {

        for (Game game : games) {
            if (game.getName().equalsIgnoreCase(name)) {
                return game;
            }
        }

        Game game = new Game(nextGameId++, name);
        games.add(game);

        return game;
    }

    /**
     * Returns the game instance at the specified index.
     * 
     * @param index index position in the list
     * @return requested game instance
     */
    Game getGame(int index) {
        return games.get(index);
    }

    /**
     * Returns the game instance with the specified id.
     * 
     * @param id unique identifier of game
     * @return requested game instance or null if not found
     */
    public Game getGame(long id) {

        for (Game game : games) {
            if (game.getId() == id) {
                return game;
            }
        }

        return null;
    }

    /**
     * Returns the game instance with the specified name.
     * 
     * @param name unique name of game
     * @return requested game instance or null if not found
     */
    public Game getGame(String name) {

        for (Game game : games) {
            if (game.getName().equalsIgnoreCase(name)) {
                return game;
            }
        }

        return null;
    }

    /**
     * Returns the number of games currently active
     * 
     * @return the number of games currently active
     */
    public int getGameCount() {
        return games.size();
    }

    /**
     * Returns the next available team identifier
     * 
     * @return next team id
     */
    public long getNextTeamId() {
        return nextTeamId++;
    }

    /**
     * Returns the next available player identifier
     * 
     * @return next player id
     */
    public long getNextPlayerId() {
        return nextPlayerId++;
    }
}
package com.gamingroom;
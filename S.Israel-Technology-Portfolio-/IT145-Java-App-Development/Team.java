package com.gamingroom;

import java.util.ArrayList;
import java.util.List;

/**
 * A class to hold information about a team.
 * 
 * This class extends the Entity base class and
 * contains a collection of players associated
 * with the team.
 * 
 * @author Stephen Israel
 */
public class Team extends Entity {

    /**
     * A list of players on the team
     */
    private List<Player> players = new ArrayList<Player>();

    /**
     * Constructor with an identifier and name
     * 
     * @param id unique team identifier
     * @param name unique team name
     */
    public Team(long id, String name) {
        super(id, name);
    }

    /**
     * Adds a player to the team if the name is unique
     * 
     * Iterator Pattern:
     * Iterates through the player list to ensure
     * no duplicate player names exist.
     * 
     * @param name unique player name
     * @return the new or existing player
     */
    public Player addPlayer(String name) {

        // Check for existing player with same name
        for (Player player : players) {
            if (player.getName().equalsIgnoreCase(name)) {
                return player;
            }
        }

        // Create and add new player
        Player player = new Player(GameService.getInstance().getNextPlayerId(), name);
        players.add(player);

        return player;
    }

    /**
     * Returns a string representation of the team
     */
    @Override
    public String toString() {
        return "Team [id=" + getId() + ", name=" + getName() + "]";
    }
}

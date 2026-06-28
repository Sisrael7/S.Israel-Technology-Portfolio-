package com.gamingroom;

/**
 * A class to hold information about a player.
 * 
 * This class extends the Entity base class and
 * represents an individual player within a team.
 * 
 * @author Stephen Israel
 */
public class Player extends Entity {

    /**
     * Constructor with an identifier and name
     * 
     * @param id unique player identifier
     * @param name unique player name
     */
    public Player(long id, String name) {
        super(id, name);
    }

    /**
     * Returns a string representation of the player
     */
    @Override
    public String toString() {
        return "Player [id=" + getId() + ", name=" + getName() + "]";
    }
}
//      * @return string representation of the entity
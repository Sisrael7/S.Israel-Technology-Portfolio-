package com.gamingroom;

/**
 * A base class for all entities in the game application.
 * 
 * This class holds common attributes and behaviors shared
 * by games, teams, and players.
 * 
 * @author Stephen Israel
 */
public class Entity {

    /**
     * Unique identifier for the entity
     */
    private long id;

    /**
     * Name of the entity
     */
    private String name;

    /**
     * Default constructor
     */
    public Entity() {
    }

    /**
     * Parameterized constructor
     * 
     * @param id unique identifier
     * @param name entity name
     */
    public Entity(long id, String name) {
        this.id = id;
        this.name = name;
    }

    /**
     * Returns the entity ID
     * 
     * @return entity ID
     */
    public long getId() {
        return id;
    }

    /**
     * Returns the entity name
     * 
     * @return entity name
     */
    public String getName() {
        return name;
    }

    /**
     * Returns a string representation of the entity
     */
    @Override
    public String toString() {
        return "Entity [id=" + id + ", name=" + name + "]";
    }
}

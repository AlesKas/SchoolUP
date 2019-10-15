<?php

namespace app\components;

use app\conf\Config;

/**
 * Třída pro menu aplikace
 *
 * @author Admin
 */
class Menu {
    
    /**
     * Pole pro uložení páru klíč => hodnota
     * @var array 
     */
    private $items = [];
    
    /**
     * @var string 
     */
    private $active_item;
    
    
    /**
     * Metoda pro přidání položky menu
     * @param string $controller
     * @param string $title
     */
    public function addItem($controller, $title) 
    {
        $this->items[$controller] = $title;
    }
    
    
    /**
     * Metoda pro nastavení aktivní položky menu
     * @param string $controller
     */
    public function setActiveItem($controller) 
    {
        $this->active_item = $controller;
    }
    
    
    /**
     * Metoda vrátí všechny položky menu
     * @return array
     */
    public function getItems() 
    {
        return $this->items;
    }
    
    
    /**
     * Metoda vrátí aktivní položku menu
     * @return string
     */
    public function getActiveItem() 
    {
        return $this->active_item;
    }
    
    
    /**
     * Metoda vrátí titulek aktivní stránky
     * @return string
     */
    public function getActivePageTitle() 
    {
        return $this->items[$this->getActiveItem()];
    }
    
    
}

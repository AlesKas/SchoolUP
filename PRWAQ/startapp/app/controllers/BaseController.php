<?php

namespace app\controllers;

use app\components\Menu;
use app\conf\Config;
use Exception;
use phpboom\services\Register;


/**
 * Základní třída ze kterou budou dědit všechny ostatní kontrolery
 * Tj. obsahuje funkcioalitu, která bude pro všechny zbývající kontrolery společná
 * Z této třídy nelze vytvořit objekt pomocí operátoru new, protože je deklarována jako abstratní
 */
abstract class BaseController {
    
    /**
     * @var Register
     */
    protected $register;    
    
    /**
     * @var array 
     */
    protected $toTemplate = [];
    
    /**
     *
     * @var Menu
     */
    protected $menu;
    
    
    /**
     * @param Register $register
     */
    public function __construct(Register $register) 
    {
        $this->register = $register;
        $this->setMenu();
    }
    
    
    /**
     * Nastavuje menu aplikace
     */
    private function setMenu() 
    {
        $this->menu = new Menu();
        foreach (Config::$myitems as $fileName => $title) {
            $this->menu->addItem($fileName, $title);
        }
        $this->menu->setActiveItem($this->register->getService('request')->getUrl('controller'));
    }
    
    /**
     * Přidává proměnné, které bude využívat šablona
     * @param string $key
     * @param string $value
     */
    protected function addToTemplate($key, $value) 
    {
        $this->toTemplate[$key] = $value;
    }
    
    /**
     * Nastavení titulku stránky
     * @param string $title
     */
    public function setTitle($title) 
    {
        $this->addToTemplate('title', $title);
    }
    
    
    /**
     * Redirect to other URL
     * @param string $param
     * @return Header new Location
     */
    protected function redirect($param = '', $statusCode = 303) 
    {
        header('Location: ' . Config::BASEURL.$param, true, $statusCode);
        exit();
    }
    
    /**
     * Render view
     * @throws Exception
     */
    protected function render() 
    {
        extract($this->toTemplate); // Vyhledejte si, k čemu se používá tato členská fonce PHP
        $menu = $this->menu;
        
        // BaseUrl
        $baseUrl = Config::BASEURL;
        
        $template = $this->getTemplate();
              
        if (!file_exists($template)) {
            throw new Exception('Chyba aplikace - šablona neexistuje');
        }
        
        require_once './inc/head.html';
        
        require_once $template;
        
        require_once './inc/bottom.html';

    }
    
    /**
     * @return string
     */
    private function getTemplate() 
    {
        // Sablona
        $controller = ucfirst($this->register->getService('request')->getUrl('controller'));
        if (!$controller) {
            $controller = Config::DEFAULTCONTROLLER;
        }
        
        $action = $this->register->getService('request')->getUrl('action');
        if (!$action) {
            $action = Config::DEFAULTACTION;
        }
        
        $template = Config::VIEWSFOOLDER . "/" . $controller . "/" . $action . ".tpl";
        return $template;        
    }
    
}

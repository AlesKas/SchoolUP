<?php

/**
 * Autoloader v návrhovém vzoru Singleton
 * Základní třída, která nám pomůže s vkládáním obsahu PHP tříd
 * Nebudeme muset tak používat otravné volání require() nebo include()
 */
class Autoloader {
    
    
    private static $instance = NULL;
    
    
    
    /**
     * Všiměnte si přístupového modifikátoru private
     * V případě použití u mgické metody __construct to znamená,
     * že objekt této třídy lze vytvořit vně je voláním statické metody getInstance()
     * Označení vzoru: důkladný Singleton
     */
    private function __construct() 
    {
        // registrace speiální funkce, která se bude starat o načístání PHP souborů
        \spl_autoload_register(array($this, 'autoload'));
    }
    
    
    /**
     * Metoda vrátí jednu kopii instance třídy Autoloader
     * @return object
     */
    public static function getInstance() 
    {
        if (self::$instance === NULL) {
            self::$instance = new self();
        }
        return self::$instance;
    }
    
    
    /**
     * @param string $class
     * @throws \Exception
     */
    public function autoload($class) 
    {
        $classfile = dirname(__DIR__) ."/". $class . ".php";
        $classfile = str_replace("\\", "/", $classfile);
        
        if (file_exists($classfile)) {
            require $classfile;
        } else {
            throw new \Exception('Cannot find class: '. $classfile);
        }
    }
}

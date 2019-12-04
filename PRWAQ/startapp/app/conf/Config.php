<?php


namespace app\conf;


/**
 * Konfigurace aplikace
 * Obsahuje statické konfigurační vlastnosti
 * Volají se staticky Config::NAZEV_VLASTNOST
 */
class Config {
    
    CONST
        WEBMAINTITLE = 'PHPBoom';
    
    CONST
        DEFAULTCONTROLLER = 'Default',
        DEFAULTACTION = 'default';
    
    
    CONST
        BASEURL = 'http://localhost/startapp/', // Vychozi URL aplikace
        VIEWSFOOLDER = './app/views'; // Vychozi cesta k souborum šablon
    
    // Připojední k databazi
    CONST
        HOST = 'localhost',
        USER = 'root',
        PASSWORD = '',
        DB = 'test';
    
    
    // Maska URL - pomaha nam prelozit casti URL
    public static $urlmask = ['controller', 'action', 'id'];
    
    
     /**
     * statické pole položek menu
     * @var array 
     */
    public static $myitems = [
        "default" => "Home",
        "user" => "Uživatelé",
        "cars" => "Auta"
    ];
}

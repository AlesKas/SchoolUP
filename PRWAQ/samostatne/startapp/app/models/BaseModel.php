<?php


namespace app\models;

use app\conf\Config;
use phpboom\services\Db;

/**
 * Základní třída, ze které budou dědit modelové třídy
 * Zajišťuje připojení k databázi
 * Obsahuje konstruktorem předanou službu Db, která se připojí k databázi a 
 * obsahue pomocné metody pro obsluhu databázové tabulky(tabulek)
 */
abstract class BaseModel {
    
    /** @var Db */
    protected $db;
    
    
    /**
     * @param Db $db
     */
    public function __construct(Db $db) 
    {
        $this->db = $db;
        $this->db->connection(Config::HOST, Config::USER, Config::PASSWORD, Config::DB);
    }
            
}

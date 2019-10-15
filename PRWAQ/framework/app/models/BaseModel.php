<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of BaseModel
 *
 * @author Honza
 */
abstract class BaseModel {
    
    
    protected $db;
    
    /**
     * Naváže připojení s databází
     * @param Db $db
     */
    public function __construct(Db $db) 
    {
        $this->db = $db;
        $this->db->connection(Configurator::HOST, Configurator::USER, Configurator::PASSWORD, Configurator::DB);
    }
}

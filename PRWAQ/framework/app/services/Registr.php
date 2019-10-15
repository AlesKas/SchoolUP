<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Registr
 *
 * @author Honza
 */
class Registr {
    
    
    private $_services = array();
    
    
    /**
     * @param String $service
     * @return Object
     */
    public function __get($service) 
    {
        if (!$this->_services[$service]) {
            
            require_once FW_PATH.'app/services/'.ucfirst($service).'.php';
            $this->_services[$service] = new $service();
        }
        
        return $this->_services[$service];
    }
    
}

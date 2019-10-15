<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



/**
 * Requester of GET and POST
 *
 * @author 
 */
class Request {
   
    private $url = array();
    private $post = array();
   
    
    public function __construct() 
    {
        $this->setUrl();
        $this->post = filter_input_array(INPUT_POST);
    }
    
    
    public function setUrl() 
    {
        $url = filter_input(INPUT_SERVER, 'REQUEST_URI');
        $urlbits = explode("/", $url);
        $urlcleanbits = array_slice($urlbits, 1);
        
        foreach($urlcleanbits as $key => $bit) {
            $this->url[Configurator::$urlmask[$key]] = $bit;
        }        
    }
    
    /**
     * @param String $mask
     * @return mixed
     */
    public function getUrl($mask)             
    {
        if ($this->url[$mask]) {
            return $this->url[$mask];
        }
        else {
            return false;
        }
    }
    
    /**
     * @param String $index
     * @return mixed
     */
    public function getPost($index = false) 
    {
        if (!$index) {
            
            foreach($this->post as $key => $val) {
                $this->post[$key] = filter_var($val, FILTER_SANITIZE_STRING);
            }
            
            return $this->post;
        }        
        elseif (isset($this->post[$index])) {            
            return filter_var($this->post[$index], FILTER_SANITIZE_STRING);            
        }
        else {
            return false;
        }
    }
}

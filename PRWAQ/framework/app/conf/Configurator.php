<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Configurator
 *
 * @author Honza
 */
class Configurator {
    
    const
        BASEURL = 'http://fw.local',
        DEFAULTCONTROLLER = 'Page';
    
    
    /** DB Connection Parametrs */
    const 
        HOST = 'localhost',
        USER = 'root',
        PASSWORD = '',
        DB = 'test';


    /** @var Array URL Mask */
    public static $urlmask = array("controller", "action", "id");   
        
}

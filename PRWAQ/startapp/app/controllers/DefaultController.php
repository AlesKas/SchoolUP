<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

namespace app\controllers;

use phpboom\services\Register;

/**
 * Výchozí controller, který řídí aplikaci pokud není k dispozci jiný
 */
class DefaultController extends BaseController {
       
       
    
    public function __construct(Register $register) 
    {
        parent::__construct($register);
        $this->setTitle('Aplikace');
        $this->addToTemplate('nadpis', 'Úvodní stránka');
        $this->render();
    }
    
    
    
}

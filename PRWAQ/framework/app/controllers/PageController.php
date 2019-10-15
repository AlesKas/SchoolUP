<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
require_once FW_PATH.'app/controllers/BaseController.php';
/**
 * Description of PageController
 *
 * @author BB
 */
class PageController extends BaseController {

    
    
    public function __construct(Registr $registr) 
    {
        parent::__construct($registr);       
        
        $this->actionDefault();    
    }
    
    
    public function actionDefault() 
    {
        $this->setTitle('Úvodní stránka aplikace správy uživatelů');
        
        $this->renderDefault();
    }
    
    public function renderDefault() 
    {
        require_once FW_PATH.'app/views/Page/default.php';
    }
}

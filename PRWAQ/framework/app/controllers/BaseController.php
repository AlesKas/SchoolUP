<?php

require_once FW_PATH.'app/models/MenuModel.php';

/**
 * Description of BaseController
 *
 * @author Honza
 */
abstract class BaseController {
    
    /** @var Registr of Services */
    protected $registr;
    
    /** @var String Page Title */
    protected $title;
    
    
    protected $menuItems = array();
    
    /**
     * @param Registr $registr
     */
    public function __construct(Registr $registr) 
    {
        $this->registr = $registr;
        $this->createComponentMenu();
    }
    
    /**
     * @param String $title
     */
    public function setTitle($title) 
    {
        $this->title = $title;
    }
    
    public function getTitle() 
    {
        return $this->title;
    }
    
    private function createComponentMenu() 
    {
        $controller = ($this->registr->Request->getUrl('controller') ? : strtolower(Configurator::DEFAULTCONTROLLER));
        $menuModel = new MenuModel($this->registr->Db);
        $this->menuItems = $menuModel->getMenuItems($controller);
    }
    

    /**
     * Redirect to other URL
     * @param String $param
     * @return Header new Location
     */
    public function redirect($param = '', $statusCode = 303) 
    {
        header('Location: ' . Configurator::BASEURL.'/'.$param, true, $statusCode);
        exit();
    }
    
    
}

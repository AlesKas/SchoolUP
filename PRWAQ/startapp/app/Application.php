<?php


namespace app;

use app\conf\Config;



class Application {
    
    
    private $register;
    
    
    private $controller;
    
    
    /**
     * @param \phpboom\services\Register $register
     */
    public function __construct(\phpboom\services\Register $register) 
    {
        $this->register = $register;
        $this->loadController();
    }
    
    /**
     * Metoda nacte soubor správného Controlleru podle URL
     * @throws \Exception
     */
    public function loadController() 
    {
        $request = $this->register->getService('request');
        if ($request->getUrl('controller')) {
            $controller = $request->getUrl('controller');
            $cotrollerPath = __DIR__ . '/controllers/'.ucfirst($controller)."Controller.php";
            
            if (file_exists(str_replace("\\", "/", $cotrollerPath))) {
                $this->controller = $controller;
            } else {
                throw new \Exception('Controller neexistuje: '.$controller);
            }      
        } else {
            $this->controller = Config::DEFAULTCONTROLLER;
        }
    }
    
    
    /**
     * Metoda předá řízení aplikace zvolenému Controlleru
     * @return \app\controller
     */
    public function run() 
    {
        $controller = "app\\controllers\\".ucfirst($this->controller). "Controller";
        return new $controller($this->register);
    }
}

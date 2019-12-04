<?php



namespace phpboom\services;

use app\conf\Config;

/**
 * Request - pro nás v zásadě nejdůležitější služba
 * Poskytuje ná rozhranní pro získání globálních dat, předávaných nejčastěji v URL(GET)
 * nebo metodou (POST) u formulářů
 * Zajišťuje nám základní ošeření těch dat pomocí filtračních funkcí
 */
class Request {
    
    
    /** @var array */
    private $url = [];
    
    /** @var array */
    private $post = array();
   
    
    
    public function __construct() 
    {
        $this->setUrl();
        $this->post = filter_input_array(INPUT_POST);
    }
    
    
    /**
     * Nastaví části URL do pole, podle naší konfigurace
     * např. /user/edit/1
     * přeloží pro nás jako controller => user, action => edit, id => 1
     */
    public function setUrl() 
    {
        $url = filter_input(INPUT_SERVER, 'REQUEST_URI');
        $urlbits = explode("/", $url);
        $slashesCount = strpos(Config::BASEURL, 'localhost') !== false ? 2 : 1;
        $urlcleanbits = array_slice($urlbits, $slashesCount);
        
        foreach($urlcleanbits as $key => $bit) {
            $this->url[Config::$urlmask[$key]] = $bit;
        }        
    }
    
    
    /**
     * Voláme např. getUrl('action')
     * @param string $mask
     * @return mixed
     */
    public function getUrl($mask)             
    {
        if (isset($this->url[$mask])) {
            return $this->url[$mask];
        }
        return false;
    }
    
    
    /**
     * Pro získání dat předaných metodou POST
     * @param string $index
     * @return mixed
     */
    public function getPost($index = false) 
    {
        if (!$index) { 
            foreach($this->post as $key => $val) {
                $this->post[$key] = filter_var($val, FILTER_SANITIZE_STRING);
            }    
            return $this->post;
        } elseif (isset($this->post[$index])) {            
            return filter_var($this->post[$index], FILTER_SANITIZE_STRING);            
        } 
        return false;
    }
    
}

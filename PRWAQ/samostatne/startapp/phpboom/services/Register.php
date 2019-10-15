<?php


namespace phpboom\services;

/**
 * Pomocná třída - vhodná pro jednodušší projekty
 * V rámci velkých projektů se moc nedoporučuje používat
 * Je to vlastně takový kontejner pro naše služby, které si ukládá v jedné kopii 
 * a poskytuje je pro každá volání
 * Např. Mailer, Databáze, Request, Response atd.
 */
class Register {
    
    /** Jmenny prostor tříd služeb */
    const 
        SERVICESNS = "phpboom\\services\\";
    
    
    private $services = [];
    
    
    /**
     * Vraci registrovanou službu
     * @param string $key
     * @return object
     */
    public function getService($key) 
    {
        $class = self::SERVICESNS . \ucfirst($key);
        if (!\array_key_exists($class, $this->services)) {
            // Toto je misto je citlive na chyby
            // Uměli byste jej ošetřit zachycením vyjímky?
            $this->services[$key] = new $class;
        }
        return $this->services[$key];
    }
}

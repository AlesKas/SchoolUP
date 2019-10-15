<?php
// Front Controller

// Konstanta cesty k frameworku
define('FW_PATH', dirname(__DIR__).'/');

// Vložení konfigurátoru
require_once FW_PATH.'app/conf/Configurator.php';

// inicializace registru
require_once FW_PATH.'/app/services/Registr.php';
$registr = new Registr();

// Načteme controller
$controller = ($registr->Request->getUrl('controller') ? : Configurator::DEFAULTCONTROLLER);
$contollerClass = ucfirst($controller).'Controller';

// Vytvoříme objekt Controlleru
if (file_exists(FW_PATH.'app/controllers/'.$contollerClass.'.php')) {
    require_once FW_PATH.'app/controllers/'.$contollerClass.'.php';
    new $contollerClass($registr);
}
else {
    require_once '404.php';
}


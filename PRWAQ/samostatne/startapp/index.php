<?php

// Vložení obsah souboru Autoloader, které se bude dále automaticky starat o načítání našich tříd
require_once './phpboom/Autoloader.php';

// Inicializujeme Autoloader voláním jeho statické metody getInstance
// Autoloader bude v aplikaci tedy vždy pouze v jedné instanci 
$loader = Autoloader::getInstance();

// Vytvoříme objekt třídy Register - bude nám dodávat služby aplikace
$register = new phpboom\services\Register();

// Inicializujeme aplikaci objektem třídy Application
$app = new \app\Application($register);

// Spustíme aplikaci
$app->run();
<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <meta name="description" content="Popis stránky">
        <title><?=$title;?></title>
        
        <!-- Latest compiled and minified CSS -->
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
        <!-- Optional theme -->
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css" integrity="sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp" crossorigin="anonymous">        
    </head>
    <body>
        
    <body>
        
        <nav class="navbar navbar-inverse navbar-fixed-top">
          <div class="container">
            <div class="navbar-header">
              <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
              </button>
                <a class="navbar-brand" href="#"><?=\app\conf\Config::WEBMAINTITLE;?></a>
            </div>
            <div id="navbar" class="collapse navbar-collapse">
              <ul class="nav navbar-nav">
                  
                <?php
                // Výpis položek menu
                    foreach ($menu->getItems() as $controller => $title):
                        $active = "";
                        if ($controller === $menu->getActiveItem()) {
                            $active = "class='active'";
                        }
                ?>
                        <li <?=$active;?>>
                            <a href="<?=\app\conf\Config::BASEURL;?><?=$controller;?>">
                                <?=$title;?>
                            </a>
                        </li>
                <?php
                    endforeach;
                ?>
                  
              </ul>
            </div><!--/.nav-collapse -->
          </div>
        </nav>        
        
        <!-- Otevření obalu - končí v souboru bottom.inc -->
        <div class="container">
            <br><br><br>
            

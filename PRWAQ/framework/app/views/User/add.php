<?php
    require_once FW_PATH.'app/views/inc/head.php';
?>

<div class="container">
    <h1>
        Přidat uživatele
    </h1> 
    
    
<?php
    require_once FW_PATH.'app/views/User/userform.php';
?>
    

    <hr>
    <p><a href="<?=Configurator::BASEURL;?>" class="btn btn-primary" title="Back"> Zpět </a></p>
</div>


<?php
    require_once FW_PATH.'app/views/inc/bottom.php';


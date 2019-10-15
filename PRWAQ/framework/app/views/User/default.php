<?php
    require_once FW_PATH.'app/views/inc/head.php';
?>

<div class="container">
    <h1>
        Seznam uživatelů
    </h1> 
    
    <table class="table">
        <thead>
            <tr>
                <th>ID</th>
                <th>Jméno</th>
                <th>Příjmení</th>
                <th>Vytvořen</th> 
                <th>Akce</th>
            </tr>
        </thead>
        
        <tbody>
            <?php
                foreach ($users as $user): 
            ?>
            <tr>
                <td><?=$user['id'];?></td>
                <td><?=$user['firstname'];?></td>
                <td><?=$user['lastname'];?></td>
                <td><?=$user['created'];?></td>
                <td>
                    <a href="<?=Configurator::BASEURL;?>/user/edit/<?=$user['id'];?>" class="btn btn-warning">
                        <span class="glyphicon glyphicon-pencil"></span>
                    </a>
                    <a href="<?=Configurator::BASEURL;?>/user/delete/<?=$user['id'];?>" class="btn btn-danger">
                        <span class="glyphicon glyphicon-trash"></span>
                    </a>                    
                </td>
            </tr>
            <?php
                endforeach;
            ?>
        </tbody>
        
    </table>
    
    <p><a href="<?=Configurator::BASEURL;?>/user/add" class="btn btn-primary" title="Přidat uživatele">Přidat uživatele</a></p>
</div>


<?php
    require_once FW_PATH.'app/views/inc/bottom.php';

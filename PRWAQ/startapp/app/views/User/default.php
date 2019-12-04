
<p>
    <a href='<?=$baseUrl;?>user/add' class='btn btn-primary'>Nový uživatel</a>
</p>

<table class='table table-hover'>
    <thead>
        <tr>
            <th>ID</th>
            <th>Jméno</th>
            <th>Přijmení</th>
            <th>Datum narození</th>
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
            <td><?=$user['birthday'];?></td>
            <td>
                <a href="<?=$baseUrl;?>user/edit/<?=$user['id'];?>" class="btn btn-warning">
                    <span class="glyphicon glyphicon-pencil"></span>
                </a>
                <a href="<?=$baseUrl;?>user/delete/<?=$user['id'];?>" class="btn btn-danger">
                    <span class="glyphicon glyphicon-trash"></span>
                </a> 
            </td>
        </tr>
        <?php
            endforeach;
        ?>
    </tbody>
</table>


<p>
    <a href='<?=$baseUrl;?>cars/add' class='btn btn-primary'>Nové auto</a>
</p>

<table class='table table-hover'>
    <thead>
        <tr>
            <th>ID</th>
            <th>Jméno</th>
            <th>Jméno výrobce</th>
            <th>Datum výroby</th>
            <th>Akce</th>
        </tr>
    </thead>
    
    <tbody>
        <?php
            foreach ($cars as $car):
        ?>
        <tr>
            <td><?=$car['id'];?></td>
            <td><?=$car['carName'];?></td>
            <td><?=$car['manufacturerName'];?></td>
            <td><?=$car['constructionDate'];?></td>
            <td>
                <a href="<?=$baseUrl;?>cars/edit/<?=$car['id'];?>" class="btn btn-warning">
                    <span class="glyphicon glyphicon-pencil"></span>
                </a>
                <a href="<?=$baseUrl;?>cars/delete/<?=$car['id'];?>" class="btn btn-danger">
                    <span class="glyphicon glyphicon-trash"></span>
                </a> 
            </td>
        </tr>
        <?php
            endforeach;
        ?>
    </tbody>
</table>

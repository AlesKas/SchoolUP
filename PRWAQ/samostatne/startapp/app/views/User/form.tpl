<form method="post" action="">
  <div class="form-group">
      Jméno:
      <input type="text" name="firstname" required class="form-control" value="<?=$data['firstname'];?>" placeholder="Křestní jméno">
  </div>
    
  <div class="form-group">
      Příjmení:
      <input type="text" name="lastname" required class="form-control" value="<?=$data['lastname'];?>" placeholder="Příjmení">
  </div>
    
<div class="form-group">
    Datum narození:
      <input type="text" name="birthday" required class="form-control" value="<?=$data['birthday'];?>" placeholder="YYYY-mm-dd">
  </div>
    

  <button type="submit" name="action" class="btn btn-default" value="1"><?=$actionRender;?></button>
</form>
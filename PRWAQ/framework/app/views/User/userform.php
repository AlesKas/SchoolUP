<form method="post" action="">
  <div class="form-group">
      <input type="text" name="firstname" required class="form-control" value="<?=$userData['firstname'];?>" placeholder="Křestní jméno">
  </div>
    
  <div class="form-group">
      <input type="text" name="lastname" required class="form-control" value="<?=$userData['lastname'];?>" placeholder="Příjmení">
  </div>
    

  <button type="submit" name="useraction" class="btn btn-default" value="1"><?=$actionRender;?></button>
</form>


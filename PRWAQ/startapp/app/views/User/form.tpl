<form method="post" action="">
  <div class="form-group">
      Jméno:
      <?php if (isset($data)): ?>
        <input type="text" name="firstname" required class="form-control" value="<?=$data['firstname'];?>" placeholder="Křestní jméno">
      <?php else: ?>
        <input type="text" name="firstname" required class="form-control" value="" placeholder="Křestní jméno">
      <?php endif?>
      
  </div>
    
  <div class="form-group">
      Příjmení:
      <?php if (isset($data)): ?>
      <input type="text" name="lastname" required class="form-control" value="<?=$data['lastname'];?>" placeholder="Příjmení">
      <?php else: ?>
      <input type="text" name="lastname" required class="form-control" value="" placeholder="Příjmení">
      <?php endif?>
  </div>
    
<div class="form-group">
    Datum narození:
    <?php if (isset($data)): ?>
      <input type="text" name="birthday" required class="form-control" value="<?=$data['birthday'];?>" placeholder="YYYY-mm-dd">
      <?php else: ?>
      <input type="text" name="birthday" required class="form-control" value="" placeholder="YYYY-mm-dd">
      <?php endif?>
  </div>
    

  <button type="submit" name="action" class="btn btn-default" value="1"><?=$actionRender;?></button>
</form>
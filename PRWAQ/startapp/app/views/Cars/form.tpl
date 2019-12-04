<form method="post" action="">
  <div class="form-group">
      Jméno:
      <?php if (isset($data)): ?>
      <input type="text" name="carName" required class="form-control" value="<?=$data['carName'];?>" placeholder="Jméno auta">
      <?php else: ?>
      <input type="text" name="carName" required class="form-control" value="" placeholder="Jméno auta">
      <?php endif?>
  </div>
    
  <div class="form-group">
      Jméno výrobce:
      <?php if (isset($data)): ?>
      <input type="text" name="manufacturerName" required class="form-control" value="<?=$data['manufacturerName'];?>" placeholder="Značka">
      <?php else: ?>
      <input type="text" name="manufacturerName" required class="form-control" value="" placeholder="Značka">
      <?php endif?>
  </div>
    
<div class="form-group">
    Datum výroby:
      <?php if (isset($data)): ?>
      <input type="text" name="constructionDate" required class="form-control" value="<?=$data['constructionDate'];?>" placeholder="YYYY-mm-dd">
      <?php else: ?>
      <input type="text" name="constructionDate" required class="form-control" value="" placeholder="YYYY-mm-dd">
      <?php endif?>
  </div>
    

  <button type="submit" name="action" class="btn btn-default" value="1"><?=$actionRender;?></button>
</form>
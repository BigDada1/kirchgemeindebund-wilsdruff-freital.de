<div class="container" id="pagecontainer">
<?
if($page != $home) {
  echo "<h1>{$page->get('title_long|title')}</h1>";
}
?>
  <? echo $page->body ?>
</div>

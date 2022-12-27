<?
$parishList = $pages->findOne("template=parish-list, include=hidden");
$width = 700;
$height = 440;
$parishId = str_replace("/", "", $parishList->url);
?>
<section id="<? echo $parishId ?>">
<?
if ($parishList->id != $page->id)
{
  echo "<h2 class=\"section-heading text-uppercase\">{$parishList->title}</h2>";
  echo $parishList->body;
}
?>
  <div class="tiles">
<?
$index = 1;
foreach ($parishList->children as $item)
{
  $imageUrl = "/assets/img/churches/default.png";
  if(count($item->image))
  {
    $imageUrl = $item->image->first()->size($width, $height)->HTTPURL;
  }
  echo "<article class=\"style$index\">";
  $index += 1;
  if($index > 6) {
    $index = 1;
  }
  echo "<span class=\"image\">";
  echo "<img src=\"$imageUrl\" alt=\"{$item->title}\">";
  echo "</span>";
  echo "<a href=\"{$item->url}\">";
  echo "<h2>{$item->title}</h2>";
  echo "<div class=\"content\">";
  echo "<p>{$item->title_long}</p>";
  echo "</div>";
  echo "</a>";
  echo "</article>";
}
?>
  </div>
</section>
<hr>

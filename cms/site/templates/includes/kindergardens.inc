<?
$kindergardensList = $pages->findOne("template=kindergarden-list, include=hidden");
$width = 700;
$height = 440;
$kindergardensId = str_replace("/", "", $kindergardensList->url);
?>
<section id="<? echo $kindergardensId ?>">
<?
if ($kindergardensList->id != $page->id)
{
  echo "<h2 class=\"section-heading text-uppercase\">{$kindergardensList->title}</h2>";
  echo $kindergardensList->body;
}
?>
  <div class="tiles two-column">
<?
$index = 1;
foreach ($kindergardensList->children as $item)
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

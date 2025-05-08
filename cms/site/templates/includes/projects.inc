<?
$projectList = $pages->findOne("template=project-list");
if ($page->template == "project-list") {
  $projectList = $pages->findOne("template=project-list,include=hidden");
}
$width = 700;
$height = 440;

if(!$projectList instanceof NullPage)
{
  $projectId = str_replace("/", "", $projectList->url);
  echo "<section id={$projectId}>";
  
  if ($projectList->id != $page->id)
  {
    echo "<h2 class=\"section-heading text-uppercase\">{$projectList->title}</h2>";
    echo $projectList->body;
  }
  
  echo "<div class=\"tiles\">";
  
  $index = 1;
  foreach ($projectList->children as $item)
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
  
  echo "</div>";
  echo "</section>";
  echo "<hr>";
}
?>

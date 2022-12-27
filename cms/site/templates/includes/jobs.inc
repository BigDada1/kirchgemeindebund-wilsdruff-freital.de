<?
$jobs = $pages->findOne("template=jobs");
if (!$jobs instanceof NullPage)
{
  $jobsId = str_replace("/", "", $jobs->url);
  echo "<section id=\"$jobsId\">";
  if ($jobs->id != $page->id)
  {
    echo "<h2 class=\"section-heading text-uppercase\">{$jobs->title}</h2>";
    echo $jobs->body;
  }
  echo "</section>";
  echo "<hr>";
}
?>

<header id="header">
  <div class="inner">
    <a href="/" class="logo"><? echo $siteLogo ?></a>
    <nav>
      <ul>
        <li><a href="#menu">Menu</a></li>
      </ul>
    </nav>
  </div>
</header>

<nav id="menu">
  <h2>Menu</h2>
  <ul>
<?
$homeRef = "/";
if ($home->id == $page->id)
{
  $homeRef = "#header";
}
echo "<li><a href=\"$homeRef\">Startseite</a></li>";
foreach ($home->children() as $child)
{
  $listItemClass = "";
  if ($child->id == $page->rootParent->id) {
    // this $child page is currently being viewed (or one of it's children/descendents)
    // so we highlight it as the current page in the navigation
    $listItemClass = " class=\"active\"";
  }
  $url = $child->url;
  if ($child->template != "basic-page")
  {
    $url = str_replace("/", "", $url);
    if ($home->id == $page->id)
    {
      $url = "#$url";
    }
    else
    {
      $url = "/#$url";
    }
  }
  echo "<li$listItemClass><a href=\"$url\">{$child->title}</a></li>";
}
if ($page->editable())
{
  echo "<li><a href=\"{$page->editUrl}\" title=\"Seite '$page->title' bearbeiten\">✎ Seite bearbeiten</a></li>";
}
?>
  </ul>
</nav>
<div class="main">
  <div class="inner">

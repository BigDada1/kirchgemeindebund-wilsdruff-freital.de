<?
$parishList = $pages->findOne("template=parish_list, include=hidden");
$contact = $pages->findOne("template=contact, include=hidden");
$navbarAnchorTarget = "#page-top";
$navbarInlineStyle = "";
if($page != $home) {
  $navbarAnchorTarget = $home->url;
  $navbarInlineStyle = " style='background-color: #212529'";
}
?>
<nav class="navbar navbar-expand-lg navbar-dark fixed-top"<? echo $navbarInlineStyle ?> id="mainNav">
   <div class="container">
       <a class="navbar-brand js-scroll-trigger" href="<? echo $navbarAnchorTarget ?>"><? echo $siteTitle ?></a>
       <button class="navbar-toggler navbar-toggler-right" type="button" data-toggle="collapse" data-target="#navbarResponsive" aria-controls="navbarResponsive" aria-expanded="false" aria-label="Navigation öffnen/schließen">Menü <i class="fas fa-bars"></i></button>
       <div class="collapse navbar-collapse" id="navbarResponsive">
           <ul class="navbar-nav text-uppercase ml-auto">
<?
foreach ($home->header_sites as $item) {
  echo "<li class='nav-item'><a class='nav-link js-scroll-trigger' href='/#{$item->name}'>{$item->title}</a></li>\n";
}
if ($page->editable()) {
  echo "<li class='nav-item'><a class='nav-link js-scroll-trigger' href='{$page->editUrl}' title='\"{$page->title}\" bearbeiten'>✎</a></li>\n";
}
?>
           </ul>
       </div>
   </div>
</nav>

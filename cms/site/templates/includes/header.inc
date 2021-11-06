<?
$explodedTitle = explode(" ", $siteTitle);
$introLeadIn = $siteTitle;
$introHeading = "";
if(sizeof($explodedTitle) > 1) {
  $introLeadIn = $explodedTitle[0];
  $introHeading = $explodedTitle[1];
}
$parishList = $pages->findOne("template=parish_list, include=hidden");

$headerParish = $page->intro_parish;
$imageUrl = "/assets/img/churches/default.png";
if($headerParish) {
   if(count($headerParish->image)) {
      $width = 1400;
      $height = 880;
      $imageUrl = $headerParish->image->first()->size($width, $height)->HTTPURL;
   }
}
$mastheadInlineStyle = " style=\"background-image: url('" . $imageUrl . "')\"";
?>
<header class="masthead"<? echo $mastheadInlineStyle ?>>
   <div class="container">
       <div class="intro-text">
           <div class="intro-lead-in">
               <p><? echo $introLeadIn ?></p>
           </div>
           <div class="intro-heading text-uppercase">
               <p><? echo $introHeading ?></p>
           </div>
           <a class='btn btn-primary btn-xl text-uppercase js-scroll-trigger' href='#<? echo $parishList->name ?>'><? echo $home->intro_link_title ?></a>
       </div>
   </div>
</header>

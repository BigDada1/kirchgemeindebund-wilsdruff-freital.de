<?
$parishList = $pages->findOne("template=parish-list, include=hidden");
$width = 700;
$height = 440;
?>
<section class="bg-light page-section grid" id="<? echo $parishList->name ?>">
   <div class="container">
      <div class="row">
          <div class="col-lg-12 text-center">
              <h2 class="section-heading text-uppercase"><?
echo $parishList->title;
if ($parishList->editable()) {
  echo " <a href='{$parishList->editUrl}' title='\"{$parishList->title}\" bearbeiten'>✎</a>";
}
              ?></h2>
              <h3 class="section-subheading text-muted"><? echo $parishList->subtitle ?></h3>
          </div>
      </div>
      <div class="row">
<?
foreach ($parishList->children as $item) {
   $imageUrl = "/assets/img/churches/default.png";
   if(count($item->image)) {
      $imageUrl = $item->image->first()->size($width, $height)->HTTPURL;
   }
   echo "<div class='col-md-4 col-sm-6 churches-item'>";
      echo "<a class='churches-link' data-toggle='modal' href='#{$item->name}'>";
         echo "<div class='churches-hover'>";
            echo "<div class='churches-hover-content'><i class='fas fa-expand fa-3x'></i></div>";
         echo "</div>";
         echo "<img class='img-fluid' src='{$imageUrl}' alt='{$item->title}' />";
      echo "</a>";
      echo "<div class='churches-caption'>";
         echo "<h4>{$item->title}";
if ($item->editable()) {
   echo " <a href='{$item->editUrl}' title='\"{$item->title}\" bearbeiten'>✎</a>";
}
         echo "</h4>";
         echo "<p class='text-muted'></p>";
      echo "</div>";
   echo "</div>";
}
?>
      </div>
   </div>
</section>
<?
foreach ($parishList->children as $item) {
   $imageUrl = "/assets/img/churches/default.png";
   if(count($item->image)) {
      $imageUrl = $item->image->first()->size($width, $height)->HTTPURL;
   }
   echo "<div class='churches-modal modal fade' id='{$item->name}' tabindex='-1' role='dialog' aria-hidden='true'>";
      echo "<div class='modal-dialog'>";
         echo "<div class='modal-content'>";
            echo "<div class='close-modal' data-dismiss='modal'><div class='lr'><div class='rl'></div></div></div>";
            echo "<div class='container'>";
               echo "<div class='row'>";
                  echo "<div class='col-lg-8 mx-auto'>";
                     echo "<div class='modal-body'>";
                        echo "<h2 class='text-uppercase'>{$item->title}";
if ($item->editable()) {
  echo " <a href='{$item->editUrl}' title='\"{$item->title}\" bearbeiten'>✎</a>";
}
                        echo "</h2>";
                        echo "<p class='text-intro text-muted'>{$item->title_long}</p>";
                        echo "<img class='img-fluid d-block mx-auto' src='{$imageUrl}' alt='{$item->title}' />";
                        echo $item->body;
                        echo "<h3 class='text-muted'>Kontakt</h3>";
                        echo "<ul class='list-inline'>";

$address = $item->address;
$phone = $item->phone;
$fax = $item->fax;
$email = $item->email;
$externalUrl = $item->external_url;
echo "<li>{$item->title_long}</li>";
if($address) {
  echo "<li>{$address}</li>";  
}
if($phone) {
  $internationalNumber = $phone;
  if(substr($internationalNumber, 0, 1) === "0") {
    $internationalNumber = substr_replace($internationalNumber, "+49", 0, 1);
    $internationalNumber = str_replace(' ', '', $internationalNumber);
  }
  echo "<li>Telefon: <a href='tel:{$internationalNumber}'>{$phone}</a>";
  if($fax) {
    echo " · Fax: {$phone}";
  }
  echo "</li>";  
}
if($email) {
  echo "<li><a href='mailto:{$email}'>{$email}</a></li>";  
}
if($externalUrl) {
   // in case scheme relative URI is passed, e.g., //www.google.com/
   $input = trim($externalUrl, '/');
   
   // If scheme not included, prepend it
   if (!preg_match('#^http(s)?://#', $input)) {
       $input = 'http://' . $input;
   }
   
   $urlParts = parse_url($input);
   
   // remove www
   $domain = preg_replace('/^www\./', '', $urlParts['host']);
   echo "<li><a href='{$externalUrl}' target='_blank'>{$domain}</a></li>";  
}

                        echo "</ul>";
                        echo "<button class='btn btn-primary' data-dismiss='modal' type='button'><i class='fas fa-times'></i> Schließen</button>";
                     echo "</div>";
                  echo "</div>";
               echo "</div>";
            echo "</div>";
         echo "</div>";
      echo "</div>";
   echo "</div>";
}
?>

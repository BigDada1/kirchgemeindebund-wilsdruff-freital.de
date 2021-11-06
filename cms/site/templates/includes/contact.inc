<?
$contact = $pages->findOne("template=contact, include=hidden");
?>
<section class="page-section" id="<? echo $contact->name ?>">
   <div class="container">
       <div class="row">
           <div class="col-lg-12 text-center">
               <h2 class="section-heading text-uppercase"><?

echo $contact->title;

if ($contact->editable()) {
  echo " <a href='{$contact->editUrl}' title='\"{$contact->title}\" bearbeiten'>✎</a>";
}

?></h2>
               <h3 class="section-subheading text-muted"><? echo $contact->subtitle ?></h3>
               <ul class="list-inline text-muted">
<?

$address = $contact->address;
$phone = $contact->phone;
$fax = $contact->fax;
$email = $contact->email;
echo "<li>{$siteTitleLong}</li>";
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

?>

               </ul>
           </div>
       </div>
   </div>
</section>
<?
$events = $pages->findOne("template=event-list, include=hidden");
?>
<section class="page-section" id="<? echo $events->name ?>">
   <div class="container">
       <div class="row">
           <div class="col-lg-12 text-center">
               <h2 class="section-heading text-uppercase"><?

echo $events->title;

if ($events->editable()) {
  echo " <a href='{$events->editUrl}' title='\"{$events->title}\" bearbeiten'>✎</a>";
}

?></h2>
               <h3 class="section-subheading text-muted"><? echo $events->subtitle ?></h3>
<?
$currentDate = strtotime(date("d M Y")); // compare with today's date with time '00:00'
foreach ($events->children as $item) {
  $date = $item->date;
  if (!$item->isUnpublished() && $date < $currentDate) {
    $item->addStatus(Page::statusUnpublished);
    $item->save();
  }
}
?>
              <div class="table-responsive">
                 <table class="table table-striped">
                   <thead>
                     <tr>
                       <th scope="col">Datum</th>
                       <th scope="col">Veranstaltung</th>
                       <th scope="col">Ort</th>
                     </tr>
                   </thead>
                   <tbody>
<?foreach ($events->children as $item) {
  $date = $item->date;
  $today = date('Ymd');
  $date_Ymd = date('Ymd', $date);
  $formattedDate = strftime("%a %e. %B %Y", $date);
  if ($today == $date_Ymd) {
    $formattedDate = "Heute";
  } elseif (date('Ymd', strtotime('+1 day')) == $date_Ymd) {
    $formattedDate = "Morgen";
  }
  $time = $item->time;
  if ($time) {
    $formattedDate .= ", " . strftime("%k.%M Uhr", $time);
  }

  $trClass = "";
  if($item->cancelled) {
    $trClass = " class='table-danger cancelled'";
  }
  echo "<tr{$trClass}>";
  if($item->cancelled) {
    $formattedDate = "<del>{$formattedDate}</del>";
  }
  echo "<td>{$formattedDate}</td>";
  $titleText = $item->title;
  if($item->external_url) {
    $titleText = " <a href='{$item->external_url}' target='_blank' title='Weitere Informationen zur Veranstaltung »{$item->title}« öffnen'>{$titleText} <i class='fas fa-external-link-alt'></i></a>";
  }
  $titleText = "<strong>{$titleText}</strong>";
  if($item->cancelled) {
    $titleText = "<del>{$titleText}</del> <span class='badge badge-secondary'>Fällt aus</span>";
  }
  if ($item->editable()) {
    $titleText .= " <a href='{$item->editUrl}' title='\"{$item->title}\" bearbeiten'>✎</a>";
  }
  echo "<td>{$titleText}</td>";
  $location = $item->location;
  if($item->cancelled) {
    $location = "<del>{$location}</del>";
  }
  echo "<td>{$location}</td>";
  echo "</tr>";
}
?>
              </tbody>
            </table>
          </div>
         </div>
       </div>
   </div>
</section>
<?
$events = $pages->findOne("template=event-list, include=hidden");
$eventsId = str_replace("/", "", $events->url);
?>
<section id="<? echo $eventsId ?>">
<?
if ($events->id != $page->id)
{
  echo "<h2 class=\"section-heading text-uppercase\">{$events->title}</h2>";
  echo $events->body;
}

$currentDate = strtotime(date("d M Y")); // compare with today's date with time '00:00'
foreach ($events->children as $item) {
  $date = $item->date;
  if (!$item->isUnpublished() && $date < $currentDate) {
    $item->addStatus(Page::statusUnpublished);
    $item->save();
  }
}
?>
  <div class="table-wrapper">
     <table>
       <thead>
         <tr>
           <th>Datum</th>
           <th>Veranstaltung</th>
           <th>Ort</th>
         </tr>
       </thead>
       <tbody>
<?
$children = $events->children->sort("date, time");
foreach ($children as $item) {
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

  echo "<tr>";
  echo "<td>$formattedDate</td>";
  $titleText = $item->title;
  if($item->external_url) {
    $titleText = " <a href=\"{$item->external_url}\" target=\"_blank\” title=\"Weitere Informationen zur Veranstaltung »{$item->title}« öffnen\">$titleText <i class=\"fas fa-external-link-alt\"></i></a>";
  }
  $titleText = "<strong>$titleText</strong>";
  if($item->cancelled) {
    $titleText = "<del>$titleText</del> <em>(Fällt aus)</em>";
  }
  if ($item->editable()) {
    $titleText .= " <a href=\"{$item->editUrl}\" title='\"{$item->title}\" bearbeiten'>✎</a>";
  }
  echo "<td>$titleText</td>";
  echo "<td>{$item->location}</td>";
  echo "</tr>";
}
?>
      </tbody>
    </table>
  </div>
</section>
<hr>

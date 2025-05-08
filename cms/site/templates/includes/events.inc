<?
$events = $pages->findOne("template=event-list, include=hidden");
$eventsId = str_replace("/", "", $events->url);
$limit = $page->event_limit;
?>
<section id="<? echo $eventsId ?>">
<?
if ($events->id != $page->id)
{
  echo "<h2 class=\"section-heading text-uppercase\">{$events->title}</h2>";
  echo "<p>Weitere Veranstaltungen in unserer Region finden Sie in der <a href=\"{$events->url}\">Veranstaltungs-Übersicht</a>.</p>";
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
$churchDeskApiVersion = $events->churchdesk_api_version;
$partnerToken = $events->churchdesk_api_key;
$organizationId = $events->churchdesk_organization_id;
$categoryFilterName = $events->churchdesk_category_name;
$http = new WireHttp();

$mergedEvents = [];
$counter = 0;
for($pageMarker = 0; $pageMarker < 10; $pageMarker++)
{
  $response = $http->getJSON("https://api2.churchdesk.com/api/$churchDeskApiVersion/events?partnerToken=$partnerToken&organizationId=$organizationId&itemsNumber=100&pageMarker=$pageMarker");
  if($response !== false)
  {
    if(sizeof($response) == 0)
    {
      break;
    }
    foreach ($response as $event)
    {
      if(hasCategory($event, $categoryFilterName))
      {
        if ($counter < $limit)
        {
          array_push($mergedEvents, $event);
          $counter++;
        }
        else
        {
          break;
        }
      }
    }
  }
}

$eventListIsEmpty = true;
foreach ($mergedEvents as $event)
{
  $eventListIsEmpty = false;

  $now = new \DateTimeImmutable("now");
  $tomorrow = new \DateTime("now");
  $tomorrow->modify('+1 day');
  $startDate = new \DateTimeImmutable($event["startDate"]);
  $endDate = new \DateTimeImmutable($event["endDate"]);
  $dateFormatter = new \IntlDateFormatter('de_DE', \IntlDateFormatter::SHORT, \IntlDateFormatter::SHORT);
  $dateFormatter->setPattern('E d. MMMM');

  $monthFormatter = new \IntlDateFormatter('de_DE', \IntlDateFormatter::SHORT, \IntlDateFormatter::SHORT);
  $monthFormatter->setPattern('M');
  $monthNumber = $monthFormatter->format($startDate);

  $formattedStartDate = $dateFormatter->format($startDate);
  $formattedEndDate = $dateFormatter->format($endDate);
  $formattedNow = $dateFormatter->format($now);
  $formattedTomorrow = $dateFormatter->format($tomorrow);

  $date = relativeDate($formattedStartDate, $formattedNow, $formattedTomorrow);
  if ($formattedStartDate != $formattedEndDate)
  {
    $date .= " – " . relativeDate($formattedEndDate, $formattedNow, $formattedTomorrow);
  }

  echo "<tr class=\"month-" . $monthNumber . "\">";
  $now = new \DateTimeImmutable("now");
  $tomorrow = new \DateTime("now");
  $tomorrow->modify('+1 day');
  $startDate = new \DateTimeImmutable($event["startDate"]);
  $endDate = new \DateTimeImmutable($event["endDate"]);
  $dateFormatter = new \IntlDateFormatter('de_DE', \IntlDateFormatter::SHORT, \IntlDateFormatter::SHORT);
  $dateFormatter->setPattern('E d. MMMM');
  $timeFormatter = new \IntlDateFormatter('de_DE', \IntlDateFormatter::SHORT, \IntlDateFormatter::SHORT);
  $timeFormatter->setPattern('H.mm');
  $isAllDay = $event["allDay"];
  $showEndTime = $event["showEndtime"];

  $formattedStartDate = $dateFormatter->format($startDate);
  $formattedEndDate = $dateFormatter->format($endDate);
  $formattedNow = $dateFormatter->format($now);
  $formattedTomorrow = $dateFormatter->format($tomorrow);

  $resultDate = $date;
  if (!$isAllDay)
  {
    if ($showEndTime)
    {
      $resultDate .= ", " . $timeFormatter->format($startDate) . " – " . $timeFormatter->format($endDate) . "&nbsp;Uhr";
    }
    else
    {
      $resultDate .= ", " . $timeFormatter->format($startDate) . "&nbsp;Uhr";
    }
  }
  echo "<td>$resultDate</td>";

  echo "<td>";
  echo "<strong>" . polish($event["title"]) . "</strong>";
  $summary = $event["summary"];
  if ($summary)
  {
    echo "<br>" . $summary;
  }
  $contributor = $event["contributor"];
  if ($contributor)
  {
    echo "<br>Mitwirkende: " . $contributor;
  }
  $externalLink = extractExternalLink($event["description"]);
  if($externalLink)
  {
    echo "<br>" . $externalLink;
  }
  echo "</td>";

  echo "<td>{$event["location"]}</td>";
  echo "</tr>";
}
if ($eventListIsEmpty)
{
  echo "<tr><td/><td>Im Moment sind keine Veranstaltungen verfügbar</td><td/></tr>";
}
?>
      </tbody>
    </table>
  </div>
</section>
<hr>

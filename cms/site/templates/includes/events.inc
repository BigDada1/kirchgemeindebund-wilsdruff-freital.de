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
$churchDeskApiVersion = $events->churchdesk_api_version;
$partnerToken = $events->churchdesk_api_key;
$organizationId = $events->churchdesk_organization_id;
$categoryFilterName = $events->churchdesk_category_name;
$http = new WireHttp();
$response = $http->getJSON("https://api2.churchdesk.com/api/$churchDeskApiVersion/events?partnerToken=$partnerToken&organizationId=$organizationId&itemsNumber=100");

$eventListIsEmpty = true;
if($response !== false)
{
  foreach ($response as $event)
  {
    if(!hasCategory($event, $categoryFilterName))
    {
      continue;
    }
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
    $externalLink = extractExternalLink($event["description"]);
    if($externalLink)
    {
      echo "<br>" . $externalLink;
    }
    echo "</td>";

    echo "<td>{$event["location"]}</td>";
    echo "</tr>";
  }
}
else
{
  echo "<tr><td/><td>HTTP request failed: " . $http->getError() . "</td><td/></tr>";
}
if ($eventListIsEmpty)
{
  echo "<tr><td/><td>Im Moment sind keine Veranstaltungen verfügbar</td><td/></tr>";
}

function relativeDate($date, $now, $tomorrow)
{
  if ($date == $now)
  {
    return "Heute";
  }
  elseif ($date == $tomorrow)
  {
    return "Morgen";
  }
  else
  {
    return $date;
  }
}

function getCity($event)
{
  $locationObj = $event["locationObj"];
  if ($locationObj)
  {
    return $locationObj["city"];
  }
  return "";
}

function extractExternalLink($description)
{
  $startPattern = "<p><a";
  $endPattern = "</a></p>";
  $parts = explode($startPattern, $description);
  if (sizeof($parts) > 1)
  {
    return "<a" . explode($endPattern, $parts[1])[0] . "</a>";
  }
  return "";
}

function hasCategory($event, $categoryTitle)
{
  $categories = $event["categories"];
  if ($categories)
  {
    foreach ($categories as $category)
    {
      if ($category["title"] == $categoryTitle)
      {
        return true;
      }
    }
  }
  return false;
}

function polish($input)
{
  // replace minus char by ndash
  $output = str_replace(" - ", " – ", $input);

  // replace ugly quotations {\" „ ”} by {» «}
  $output = str_replace(" \"", " »", $output);
  $output = str_replace("\" ", "« ", $output);
  $output = str_replace("„", "»", $output);
  $output = str_replace("”", "«", $output);

  // replace starting quotations
  if(strpos($output, "\"")===0) {
    $output = "»" . substr($output, 1);
  }
  // replace leading quotations
  if(strripos($output, "\"")===(strlen($output)-1)) {
    $output = substr($output, 0, -1) . "«";
  }

  return $output;
}
?>
      </tbody>
    </table>
  </div>
</section>
<hr>

<?
$events = $pages->findOne("template=event-list, include=hidden");
$mailFrom = $page->mail_from;
$mailTo = $page->mail_to;

$churchDeskApiVersion = $events->churchdesk_api_version;
$partnerToken = $events->churchdesk_api_key;
$organizationId = $events->churchdesk_organization_id;
$categoryFilterName = $events->churchdesk_category_name;
$http = new WireHttp();
$response = $http->getJSON("https://api2.churchdesk.com/api/$churchDeskApiVersion/events?partnerToken=$partnerToken&organizationId=$organizationId&itemsNumber=100");

if($response !== false)
{
  $summarizedMail = "<h1>$siteTitle</h1>";
  foreach ($response as $event)
  {
    if(!hasCategory($event, $categoryFilterName))
    {
      continue;
    }

    $startDate = new \DateTimeImmutable($event["startDate"]);
    $dateFormatter = new \IntlDateFormatter('de_DE', \IntlDateFormatter::SHORT, \IntlDateFormatter::SHORT);
    $dateFormatter->setPattern('E d. MMMM');

    $timeFormatter = new \IntlDateFormatter('de_DE', \IntlDateFormatter::SHORT, \IntlDateFormatter::SHORT);
    $timeFormatter->setPattern('H.mm');
    $isAllDay = $event["allDay"];

    $date = $dateFormatter->format($startDate);
    if (!$isAllDay)
    {
      $date .= ", " . $timeFormatter->format($startDate) . "&nbsp;Uhr";
    }

    $title = polish($event["title"]);
    $summary = $event["summary"];
    $contributor = $event["contributor"];
    $locationName = $event["locationName"];
    $location = $event["locationObj"];

    $result = "<h3>$date</h3>";
    $result .= "<ul>";
    $result .= "<li><strong>$title</strong></li>";
    if($contributor)
    {
      $result .= "<li>Mitwirkende: $contributor</li>";
    }
    if($summary)
    {
      $result .= "<li>$summary</li>";
    }
    $result .= "<li>$locationName: {$location["address"]}, {$location["zipcode"]} {$location["city"]}</li>";
    $result .= "</ul>";

    $summarizedMail .= $result;
  }

  $summarizedMail .= "<p> </p>";
  $summarizedMail .= "<hr>";
  $summarizedMail .= "<p> </p>";
  $summarizedMail .= $page->body;

  $mail->subject($siteTitle . ' (Beta-Version)')
  ->to($mailTo)
  ->from($mailFrom)
  ->body('Das ist leider eine HTML-Nachricht.')
  ->bodyHTML($summarizedMail)
  ->send();

  echo "<section><p><span class=\"icon fa-check-circle\">&nbsp; E-Mail erfolgreich an $mailTo gesendet</span></p></section>";
  echo "<hr>";
}
else
{
  echo "<p><code>HTTP request failed: " . $http->getError() . "</code></p>";
}
?>

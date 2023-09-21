<?
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

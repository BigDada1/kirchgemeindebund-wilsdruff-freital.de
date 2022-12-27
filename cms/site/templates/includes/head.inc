<?php
// Set variables
$home = $pages->get("/");
$siteTitle = $home->title;
$siteTitleLong = $home->title_long;

$siteTitleWithBreaks = str_replace(" ", "\n", $siteTitle);
$siteTitleWithBreaks = str_replace("-", "\n", $siteTitleWithBreaks);
$siteLogo = "";
// $siteLogo .= "<svg viewBox=\"0 0 48 48\" xmlns=\"http://www.w3.org/2000/svg\">
//   <path d=\"M41.1,6.9C40.5,6.3,39.8,6,39,6H9C8.2,6,7.5,6.3,6.9,6.9S6,8.2,6,9v30c0,0.8,0.3,1.5,0.9,2.1S8.2,42,9,42h30 c0.8,0,1.5-0.3,2.1-0.9S42,39.8,42,39V9C42,8.2,41.7,7.5,41.1,6.9z M9,9h19.7v13.5H9V9z M16.4,39H9V25.5h7.4V39z M39,39H19.3V25.5 H39V39z M39,22.5h-7.4V9H39V22.5z\" /></svg>";
$siteLogo .= "<span>$siteTitleWithBreaks</span>";
?>

<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="utf-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no"/>
    <meta name="description" content=""/>
    <title><? echo $siteTitle ?></title>
    <meta name="description" content="Der Ev.-Luth. Kirchengemeindebund Wilsdruff-Freital wurde zum 1. Januar 2021 gegründet. Er ist eine Verbindung von acht Kirchengemeinden. Zunächst ist der Kirchgemeindebund eine Verwaltungsgemeinschaft. Daneben beginnen wir, in der Verkündigung Synergien zu nutzen. Wir arbeiten daran, dass dieses Zusammenwirken wächst und wünschen, dass ein Gemeinschaftsgefühl entsteht.">
    <meta property="og:title" content="<?php echo $siteTitle ?>">
    <meta property="og:description" content="Der Ev.-Luth. Kirchengemeindebund Wilsdruff-Freital wurde zum 1. Januar 2021 gegründet. Er ist eine Verbindung von acht Kirchengemeinden. Zunächst ist der Kirchgemeindebund eine Verwaltungsgemeinschaft. Daneben beginnen wir, in der Verkündigung Synergien zu nutzen. Wir arbeiten daran, dass dieses Zusammenwirken wächst und wünschen, dass ein Gemeinschaftsgefühl entsteht.">
    <meta property="og:image" content="<?php echo $home->httpUrl() ?>assets/KGB.png">
    <link rel="stylesheet" href="/assets/css/main.css">
    <noscript>
      <link rel="stylesheet" href="/assets/css/noscript.css">
    </noscript>
    <meta name="google-site-verification" content="TvUyDDIB758IKtWR0t3cS3S89ivZ8V034szemF2l69g"/>
</head>
<body class="is-preload">
  <div id="wrapper">


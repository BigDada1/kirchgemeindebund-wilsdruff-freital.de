<?php
// Set variables
$home = $pages->get("/");
$siteTitle = $home->title;
$siteTitleLong = $home->title_long;
?>

<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="utf-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no"/>
    <meta name="description" content=""/>
    <title><? echo $siteTitle ?></title>
    <link href="/assets/css/bootstrap.min.css" rel="stylesheet"/>
    <link href="/assets/css/all.min.css" rel="stylesheet" type="text/css"/>
    <link href="/assets/css/agency.css" rel="stylesheet"/>
    <meta name="google-site-verification" content="TvUyDDIB758IKtWR0t3cS3S89ivZ8V034szemF2l69g"/>
<?
if($page != $home || $home->body) {
    echo "<style>
      #pagecontainer {
        padding-top: 150px;
      }
      @media only screen and (max-width: 991px) {
        #pagecontainer {
          padding-top: 100px;
        }
      }
    </style>";
}
?>
</head>
<body id="page-top">

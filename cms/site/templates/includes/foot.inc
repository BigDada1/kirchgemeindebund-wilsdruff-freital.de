<?
if ($page->id != $home->id)
{
  echo "<section>";
  echo "<p><a href=\"{$page->parent->url}\" class=\"button icon solid fa-arrow-left\">{$page->parent->title}</a></p>";
  echo "</section>";
}
?>
  </div>
</div>
<?
$contact = $pages->findOne("template=contact, include=hidden");
$address = $contact->address;
$phone = $contact->phone;
$fax = $contact->fax;
$email = $contact->email;
$internationalNumber = $phone;
if(substr($internationalNumber, 0, 1) === "0") {
  $internationalNumber = substr_replace($internationalNumber, "+49", 0, 1);
  $internationalNumber = str_replace(' ', '', $internationalNumber);
}
$contactId = str_replace("/", "", $contact->url);
?>
<footer id="footer">
  <div class="inner">
    <section id="<? echo $contactId ?>">
      <h2><?
echo $contact->title;
if ($contact->editable())
{
  echo " <a href='{$contact->editUrl}' title='\"{$contact->title}\" bearbeiten'>✎</a>";
}
?></h2>
      <p><? echo $contact->subtitle ?></p>
      <p class="logo"><? echo $siteLogo ?></p>
      <p>
        <strong><? echo $siteTitle ?></strong>
      </p>
      <p>
        <? echo $address ?><br />
        Telefon: <a href="tel:<? echo $internationalNumber ?>"><? echo $phone ?></a><br />
        Fax: <? echo $fax ?><br />
        <a href="mailto:<? echo $email ?>"><? echo $email ?></a>
      </p>
    </section>
    <ul class="copyright">
      <li>Copyright © <? echo date("Y") ?> <? echo $siteTitleLong ?></li>
<?
foreach ($home->footer_sites as $item) {
  echo "<li><a href=\"{$item->url}\">{$item->get("title")}</a></li>";
}
if ($user->isLoggedin()) {
  echo "<li><a href=\"{$config->urls->admin}login/logout/\">Logout ({$user->name})</a></li>";
}
?>
    </ul>
  </div>
</footer>

</div>
<? include("./js.inc") ?>
</body>

</html>

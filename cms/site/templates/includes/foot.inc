<footer class="footer" id="footer" style="background-color: white">
  <div class="container">
      <div class="row align-items-center">
          <div class="col-md-6">
              <span class="copyright">Copyright &copy; <? echo date("Y") ?> <? echo $siteTitleLong ?></span>
          </div>
          <div class="col-md-6">
              <ul class="list-inline quicklinks">
<?
foreach ($home->footer_sites as $item) {
  echo "<li class='list-inline-item'><a href='{$item->url}'>" . $item->get("title") . "</a></li>";
}
if ($user->isLoggedin()) {
  echo "<li class='list-inline-item'><a href='{$config->urls->admin}login/logout/'>Logout ({$user->name})</a></li>";
}
?>
              </ul>
          </div>
      </div>
  </div>
</footer>
<?php include("./js.inc") ?>
</body>
</html>
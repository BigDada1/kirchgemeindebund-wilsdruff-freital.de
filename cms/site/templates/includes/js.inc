<?
if($page != $home) {
    echo "<script>
    fixPageShort();
    function fixPageShort() {
      if (window.innerHeight > document.body.offsetHeight) {
        document.getElementById('footer').style.position = 'fixed';
        document.getElementById('footer').style.bottom = 0;
        document.getElementById('footer').style.right = 0;
        document.getElementById('footer').style.left = 0;
        document.getElementById('footer').style.width = '100%';
      }
    }
  </script>";
}
?>
<script src="/assets/js/jquery.min.js"></script>
<script src="/assets/js/bootstrap.bundle.min.js"></script>
<script src="/assets/js/jquery.easing.min.js"></script>
<script src="/assets/js/agency.min.js"></script>

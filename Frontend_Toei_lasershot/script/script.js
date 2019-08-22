var $circle = document.querySelector('.r-progress-bar > .bar');
var $wrapper = document.querySelector('.some-wrapper');
var $text = document.querySelector('.some-wrapper > .inner-wrapper > .text');
var $btn = document.querySelector('.some-wrapper > .inner-wrappers > .increment-btn');

$btn.addEventListener('click', function(evt) {
  var val = incrementProgress(
    $wrapper.getAttribute('data-percentage')
  );
  var r = $circle.getAttribute('r');
  var c = Math.PI * (r * 2);
  var pct = ((100 - val) / 100) * c;
  
  $circle.style.strokeDashoffset = pct;
  $text.innerText = val + '%';
  $wrapper.setAttribute('data-percentage', val);
});

function incrementProgress(val) {
  val = parseInt(val, 10);
  var min = 2;
  var max = 25;
  var incremented;
  
  return (incremented = val + random(min, max)) >= 100
    ? 0
    : incremented;
}

function random(min, max) {
  return Math.floor(Math.random() * (max - min) + min);
}
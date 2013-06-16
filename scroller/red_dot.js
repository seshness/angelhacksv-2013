$('body').append('<div id="eyeTrackingDot"></div>');
$('#eyeTrackingDot').css({
    'border-radius': '40px',
    width: '50px',
    height: '50px',
    'background-color': 'red',
    'box-shadow': '0 0 15px 10px #ccc'
  });

chrome.runtime.onMessage.addListener(
  function(request, sender, sendResponse) {
    console.log('getting a message:', request, sender);
    $('#eyeTrackingDot').css({
      position: 'fixed',
      top: request.smoothPosition,
      left: window.innerWidth/2,
      zIndex: 999999
    });
  });

$('body').append('<div id="eyeTrackingDot"></div>');
$('#eyeTrackingDot').css({
    'border-radius': '20px',
    width: '30px',
    height: '30px',
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

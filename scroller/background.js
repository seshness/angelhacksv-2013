chrome.browserAction.onClicked.addListener(automaticScroller);

var currentX = 200
var currentY = 200

function automaticScroller(tab) {
    console.log('Scrolling ' + tab.url + '!');
    chrome.tabs.executeScript({
        // code: 'document.body.style.backgroundColor="green"'
        code: 'window.scrollTo(0, 0)'
    });
  }

function scrollToAPosition(x, y) {
    // add logic for whether to scroll or not
    document.body.style.backgroundColor="red";
    console.log("received x to be " + x + " and y to be " + y);
    // var run = "window.scrollTo(" + String(x) + "," + String(y) + ")";
    var run = "window.scrollTo(" + String(currentX - 100) + "," + String(currentY - 100) + ")";
    currentX = currentX - 100
    currentY = currentY - 100
    console.log(run);
    chrome.tabs.executeScript({
        code: run
    });
};

function onMessage(evt) {
    console.log('received message ' + evt.data)
    var obj = JSON.parse(evt.data)
    var x = obj.x
    var y = obj.y
    console.log('received obj ' + obj)
    console.log('received message x ' + x)
    console.log('received message y ' + y)
    scrollToAPosition(100, 100)
  }

websocket = new WebSocket("ws://localhost:8081");
websocket.onmessage = function(evt) { onMessage(evt); };

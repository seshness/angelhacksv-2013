// Called when the user clicks on the browser action.
// chrome.browserAction.onClicked.addListener(automaticScroller);
chrome.browserAction.onClicked.addListener(onMessage);

function automaticScroller(tab) {
    console.log('Scrolling ' + tab.url + '!');
    chrome.tabs.executeScript({
        code: 'document.body.style.backgroundColor="green"'
        // code: 'window.scrollTo(0, 0)'
    });
}


function onMessage(evt) {
    console.log('received message ' + evt.data)
  }

websocket = new WebSocket("ws://localhost:8081");
websocket.onmessage = function(evt) { onMessage(evt); };

// Called when the user clicks on the browser action.
chrome.browserAction.onClicked.addListener(automaticScroller);

function automaticScroller(tab) {
    console.log('Scrolling ' + tab.url + '!');
    chrome.tabs.executeScript({
        // code: 'document.body.style.backgroundColor="read"'
        code: 'window.scrollTo(0, 0)'
    });
}


// function onMessage(evt) {
//     console.log('received message ' + evt.data)
//     con = document.getElementById("console");
//     con.innerHTML += evt.data;
//     con.innerHTML += '<br />';
//   }

// websocket = new WebSocket("ws://localhost:8081");
// websocket.onmessage = function(evt) { onMessage(evt); };

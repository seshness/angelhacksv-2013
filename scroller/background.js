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

function scrollToAPosition(x, y) {
    document.body.style.backgroundColor="red";
    //console.log("received x to be" + x + " and y to be " + y);
    var run = "window.scrollTo(" + String(x) + "," + String(y) + ")";
    console.log(run);
    chrome.tabs.executeScript({
	    code: run
	});                                                                                                                                      
};

function automaticScroller(tab) {
    console.log('Turning ' + tab.url + ' red!');
    chrome.tabs.executeScript({                                                                                                                                             
    // code: 'document.body.style.backgroundColor="read"'                                                                                                                   
            code: 'window.scrollTo(200, 200)'                                                                                                                                 
	    //  code: 'this.scrollToAPosition(0,0)'                                                                                                                                   
      });                                                                                                                                                                   
    
    //for (var k = 0; k < 500; k= k+100){
    //scrollToAPosition(k, 0);
    //}
    //scrollToAPosition(200, 200);
};


function onMessage(evt) {
    console.log('received message ' + evt.data)
  }

websocket = new WebSocket("ws://localhost:8081");
websocket.onmessage = function(evt) { onMessage(evt); };

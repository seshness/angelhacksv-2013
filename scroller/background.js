chrome.browserAction.onClicked.addListener(automaticScroller);

var kScalarScrollAmount = window.screen.height * 0.2,
    kTopFraction = 0.4,
    kBottomFraction = 0.3,
    kSmoothingAlpha = 0.4,
    kLastNValues = 70;

var LastNThings = function(N) {
  this._stuff = [];
  this.eventHandlers = [];
  this.addThing = function(thing) {
    if (this._stuff.length > N) {
      this._stuff.shift();
    }
    this._stuff.push(thing);
    this.eventHandlers.map(function(eH) {
      eH.call(this);
    }.bind(this));
  };
  this.getStuff = function() {
    return this._stuff;
  };
  this.register = function(fn) {
    this.eventHandlers.push(fn);
  };
  return this;
};

function automaticScroller(tab) {
  console.log('Scrolling ' + tab.url + '!');
  chrome.tabs.executeScript({
        // code: 'document.body.style.backgroundColor="green"'
        code: 'window.scrollTo(0, 0)'
      });
  }

function scrollByTheAmount(x, y) {
    // add logic for whether to scroll or not
    var run = "window.scrollBy(" + String(x) + "," + String(y) + ")";
    console.log(run);
    chrome.tabs.executeScript({
        code: run
    });
}

function showCurrentLocation(x, y) {
  var run = "var obj = {left :" + x + ", top: " + y + "};";
  chrome.tabs.executeScript({
    code: run
  });
}

var ScrollingEngine = function(
    recentEyeLocations, smoothingAlpha, topFraction, bottomFraction) {
  var self = this;
  /**
   * @return integer -1 scroll up, 0 no scroll, 1 scroll down
   */
  this.toScrollOrNotToScrollThatIsTheQuestion = function(stuff) {
    // Exponential moving avg.
    var smoothPosition = stuff.map(function(position) {
      // We're not yet interested in x-scrolling.
      return position.y;
    }).reduce(function(memo, next) {
      return (1 - smoothingAlpha) * memo + smoothingAlpha * next;
    });

    // It's reversed?!?!?!?!
    smoothPosition = window.screen.height - smoothPosition;

    console.log('Smooth position', smoothPosition);
    pubsub.publish('smoothPosition', [smoothPosition]);

    /**
     * Top and bottom fractions of the screen trigger scrolling.
     */
    if (smoothPosition > (1 - bottomFraction) * window.screen.height) {
      return 1;
    } else if (smoothPosition < topFraction * window.screen.height) {
      return -1;
    } else {
      return 0;
    }
  };
  this.processNewEvent = function() {
    // this will refer to the LastNThings object
    var scrollDirection = self.toScrollOrNotToScrollThatIsTheQuestion(this.getStuff()),
        scrollAmount = scrollDirection * kScalarScrollAmount;
    if (scrollAmount !== 0) {
      scrollByTheAmount(0, scrollAmount);
    }
  };
  recentEyeLocations.register(this.processNewEvent);
  return this;
};

var recentEyeLocations = new LastNThings(kLastNValues),
    engine = new ScrollingEngine(recentEyeLocations, kSmoothingAlpha, kTopFraction, kBottomFraction);

function onMessage(evt) {
  var obj = JSON.parse(evt.data);
  console.log('received location:',  obj);

  recentEyeLocations.addThing(obj);
}

pubsub.subscribe('smoothPosition', function(smoothPosition) {
  chrome.tabs.getSelected(null, function(tab) {
    chrome.tabs.sendMessage(tab.id, {smoothPosition: smoothPosition});
    console.log('message sent:', smoothPosition);
  });
});

var startWebSocket = function() {
  websocket = new WebSocket("ws://localhost:8081");
  websocket.onmessage = onMessage;
  websocket.onerror = websocket.onclose = startWebSocket;
};

startWebSocket();

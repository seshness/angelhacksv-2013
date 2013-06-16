require 'redis'
require 'em-websocket'

SOCKETS = []
@redis = Redis.new(:host => '127.0.0.1', :post => 6379)

# Creating a thread for the EM event loop
Thread.new do
  EventMachine.run do
    # Creates a websocket listener
    EventMachine::WebSocket.start(:host => 'localhost', :port => 8081) do |ws|
      ws.onopen do
        # When someone connects I want to add that socket to the SOCKETS array that
        # I instantiated above
        puts 'creating socket'
        SOCKETS << ws
      end

      ws.onclose do
        # Upon the close of the connection I remove it from my list of running sockets
        puts 'closing socket'
        SOCKETS.delete ws
      end
    end
  end
end

# Creating a thread for the redis subscribe block
Thread.new do
  @redis.subscribe('location') do |on|
    puts "new location update"
    # When a message is published to 'location'
    on.message do |chan, msg|
      puts "sending message: #{msg}"
     # Send out the message on each open socket
      SOCKETS.each {|s| s.send msg}
    end
  end
end

sleep

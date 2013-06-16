require 'redis'
@redis = Redis.new(:host => '127.0.0.1', :post => 6379)

# http://stackoverflow.com/questions/4154262/how-to-get-screen-resolution-in-ruby
screen_x, screen_y = `xrandr`.scan(/current (\d+) x (\d+)/).flatten.map { |i| i.to_f }

while true
  x, y = rand(0..screen_x), rand(0..screen_y)
  @redis.publish('location', %|{"x":#{x},"y":#{y}}|)
  sleep 0.75
end

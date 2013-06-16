require 'redis'
@redis = Redis.new(:host => '127.0.0.1', :post => 6379)

# http://stackoverflow.com/questions/4154262/how-to-get-screen-resolution-in-ruby
screen_x, screen_y = `xrandr`.scan(/current (\d+) x (\d+)/).flatten.map { |i| i.to_f }

x = 10000
y = (screen_y / 2.0)

scroll_amount = screen_y / 10.0

while true
  while y < screen_y do
    @redis.publish('location', %|{"x":#{x},"y":#{y}}|)
    y += scroll_amount
    sleep 0.75
  while y > 0 do
    @redis.publish('location', %|{"x":#{x},"y":#{y}}|)
    y -= scroll_amount
    sleep 0.75
end

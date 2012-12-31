require_relative 'player_a'
require_relative 'uno_game'
us = UnoGame.new
puts us.to_s + "\n"
while us.next_turn == :keep_playing
  puts us.to_s + "\n"*2
end

p "GAME OVER!"

#test commit i enjoy pie
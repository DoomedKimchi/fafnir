require_relative 'player'
require_relative 'uno_game'
require 'benchmark'

turn_total = 0
iterations = 1
wins = {:player_one_turn => 0, :player_two_turn=>0}
iterations.times do
  us = UnoGame.new(PlayerA,PlayerB,:random)
  
  game_status = us.run(iterations<=1)
  
  wins[game_status] +=1
end

puts "#{wins[:player_one_turn]} vs #{wins[:player_two_turn]}"

#test commit i enjoy pie
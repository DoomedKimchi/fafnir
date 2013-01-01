require_relative 'player_a'
require_relative 'uno_game'
require 'benchmark'

turn_total = 0
iterations = 60000
wins = {:player_one_turn => 0, :player_two_turn=>0}
p Benchmark.measure {
  iterations.times do
    us = UnoGame.new(PlayerA,PlayerA,:player_one_turn)
    
    game_status = us.run(iterations<=1)
    
    wins[game_status] +=1
  end
}

p "#{wins[:player_one_turn]} vs #{wins[:player_two_turn]}"

#test commit i enjoy pie
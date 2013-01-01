require_relative 'player_a'
require_relative 'uno_game'

turn_total = 0
iterations = 1000
wins = {:player_one_turn => 0, :player_two_turn=>0}

iterations.times do
  us = UnoGame.new
  turn_count = 0
  
  puts us.to_s + "\n" if iterations<=1
  
  game_status = :keep_playing
  while game_status == :keep_playing
    game_status = us.next_turn
    
    puts us.to_s + "\n"*2 if iterations<=1
    
    turn_count +=1
  end
  wins[game_status] +=1
  
  #p "GAME OVER! Turns = #{turn_count}"
  turn_total+=turn_count
end
p "avg turns = #{turn_total/iterations.to_f}"
p "#{wins[:player_one_turn]} vs #{wins[:player_two_turn]}"

#test commit i enjoy pie
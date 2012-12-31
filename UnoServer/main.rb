require_relative 'player_a'
require_relative 'uno_game'
turn_total = 0

1.times do
  us = UnoGame.new
  turn_count = 0
  
  puts us.to_s + "\n"
  while us.next_turn == :keep_playing
    puts us.to_s + "\n"*2
    turn_count +=1
  end
  
  #p "GAME OVER! Turns = #{turn_count}"
  turn_total+=turn_count
end
#test commit i enjoy pie
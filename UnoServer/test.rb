require_relative 'uno_game'
require_relative 'player'
require_relative 'base_player'
require_relative 'deck'
require_relative 'card'

us = UnoGame.new
puts us.check Card.new(7,:spades), Card.new(1,:hearts)

require_relative 'card'
require_relative 'base_player'
class  PlayerA < BasePlayer
  def initialize
    super
  end

  def play_card
    top_card = @game_state[:top_card]
    matching_ranks = @hand.find_all {|card| card.rank==top_card.rank}
    if !matching_ranks.empty?
      c = matching_ranks[0]
      @hand.delete_if {|card| card == c}
      return c
    end
    
    matching_suits = @hand.find_all {|card| card.suit==top_card.suit}
    if !matching_suits.empty?
      c = matching_suits[0]
      @hand.delete_if {|card| card == c}
      return c
    end
    
    #play a card based off hand and gameState
    #needs to request a card from the game server if he's out
    #meat of the program
  end
end

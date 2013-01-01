require_relative 'card'
require_relative 'base_player'
class  PlayerA < BasePlayer
  def initialize
    super
  end

  def play_card
    top_card = @game_state[:top_card]
    
    c = @hand.find {|card| card.rank==top_card.rank}
    unless c.nil?
      @hand.delete_if {|card| card == c}
      return c 
    end
    
    c = @hand.find {|card| card.suit==top_card.suit}
    unless c.nil?
      @hand.delete_if {|card| card == c}
      return c 
    end
  end
end

class  PlayerB < BasePlayer
  def initialize
    super
  end

  def play_card
    top_card = @game_state[:top_card]
    
    c = @hand.find {|card| card.suit==top_card.suit}
    unless c.nil?
      @hand.delete_if {|card| card == c}
      return c 
    end
    
    c = @hand.find {|card| card.rank==top_card.rank}
    unless c.nil?
      @hand.delete_if {|card| card == c}
      return c 
    end
  end
end



